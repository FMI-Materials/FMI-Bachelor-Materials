import collections
import gym
import numpy as np
import tensorflow as tf
import tqdm
from tensorflow.keras.models import load_model

from IPython import display as ipythondisplay
from PIL import Image
from pyvirtualdisplay import Display

from matplotlib import pyplot as plt
from tensorflow.keras import layers
from typing import Any, List, Sequence, Tuple
import datetime
from enum import Enum, IntEnum
import Utils_replay
eps = np.finfo(np.float32).eps.item()

TRAINING_MODE = True

# Some parameters for training and model
num_hidden_units = 128
num_actions = None # env decision
MAX_NUM_EPISODES = 3000
MAX_STEPS_PER_EPISODE = 200
STANDARDIZE_RETURNS = True # If returns should be standardized or not

# Considered solved when the average reward is >= 195 over 100 frames
REWARD_THRESHOLD = 195
GAMMA = 0.99


# BIG PERFORMANCE WARNING !!!!!
tf.config.run_functions_eagerly(True)

class MethodToUse(IntEnum):
    DQN_BASE = 2
    DQN_TARGET_NETWORK = 3
    DQN_TARGET_NETWORK_AND_EXPERIENCE_REPLAY = 4
    DDQN_AND_ALL = 5

class DQNModel(tf.keras.Model):
    def __init__(self, input_shape, num_actions):
        super(DQNModel, self).__init__()
        # Add an input layer of a given input shape
        self.input_layer = tf.keras.layers.InputLayer(input_shape=input_shape)

        # Add a few hidden layers
        self.hidden_layers = []
        self.hidden_layers.append(tf.keras.layers.Dense(64, activation='relu'))
        self.hidden_layers.append(tf.keras.layers.Dense(32, activation='relu'))
        self.output_layer = tf.keras.layers.Dense(units=num_actions, activation='linear')

    @tf.function
    def call(self, inputs): # batch_size x input_shape
        # Go through the input layer to ensure that inputs is of N x input_shape
        z = self.input_layer(inputs)

        # go over the hidden layers
        for l in self.hidden_layers:
            z = l(z)

        # results / state-action values are in the output layer
        q_values = self.output_layer(z)
        return q_values

class Agent_DQN():
    def __init__(self, env, seed = None,
                 replayBufferSize = 32000,
                 gamma = 0.9, # the discount factor
                 batch_size = 1024,
                 lr = 0.001, # learning rate (alpha)
                 steps_until_sync=20,  # At how many steps should we update the target network weights
                 choose_action_frequency=1,
                 # At how many steps should we take an action decision (think about pong game: you need to keep the same action for x frames ideally...)
                 pre_train_steps=1,  # Steps to run before starting the training process,
                 train_frequency=1,
                 # At how many steps should I update the training. You could gather more data and do the training in batches more..
                 epsScheduler=Utils_replay.LinearScheduleEpsilon(),  # How to update epsilon ?
                 method: MethodToUse = MethodToUse.DQN_TARGET_NETWORK):  # The method to use behind

        self.env = env
        self.method = method

        # Create and build the deep models used for function approximation methods
        obsSpaceShape = list(env.observation_space.shape)
        self.dqn = DQNModel(input_shape=obsSpaceShape, num_actions=env.action_space.n)

        # Input is BatchSize (unknown, that's why it is None) X input_shape of the environment
        inputShape = [None]
        inputShape.extend(obsSpaceShape)
        self.dqn.build(tf.TensorShape(inputShape))  # [Num items in a batch X observation input space]

        if self.method > MethodToUse.DQN_BASE:
            self.dqn_target = DQNModel(input_shape=obsSpaceShape, num_actions=env.action_space.n)
            self.dqn_target.build(tf.TensorShape(inputShape))

        # Create the replay buffer
        self.replayBuffer = Utils_replay.ReplayBuffer(buffer_size=replayBufferSize)

        # All other parameters
        self.batch_size = batch_size
        self.gamma = gamma
        self.steps_until_sync = steps_until_sync
        self.choose_action_frequency = choose_action_frequency
        self.pre_train_steps = pre_train_steps
        self.train_frequency = train_frequency
        self.epsScheduler = epsScheduler
        self.method = method

        # Loss function setup
        self.loss_function = tf.keras.losses.MSE # tf.keras.losses.Huber(reduction=tf.keras.losses.Reduction.SUM)

        # Optimizer setup
        self.optimizer = tf.optimizers.Adam(learning_rate=lr)

        # Have deterministic output at each run for easy debugging
        if seed is not None:
            self.env.seed(seed)
            tf.random.set_seed(seed)
            np.random.seed(seed)

        # Total steps of the running algorithm
        self.total_steps = 0

        #obs = self.env.reset()
        #newobs, reward, done, inf = self.env.step(0)
        self.num_actions = self.env.action_space.n

    # Receive action returns a state, reward, done
    # We wrap-up this to be compatible in a tf graph op
    def env_step(self, action : np.ndarray) -> Tuple[np.ndarray, np.ndarray, np.ndarray]:
        state, reward, done, _ = self.env.step(action)
        return (state.astype(np.float32),
                np.array(reward, np.float32),
                np.array(done, np.float32))

    # This is under a tensorflow wrapper to be able to use it inside tensorflow graphs (not necessarly but MIGHT speed up things)
    def tf_env_step(self, action:tf.Tensor) -> List[tf.Tensor]:
        return tf.numpy_function(self.env_step, [action], [tf.float32, tf.float32, tf.float32])

    # Gets an action based on epsilon and the DQN model
    # Note: The input states is a batch x input_shape !
    def get_action(self, states, epsilon):
        sampled_value = np.random.rand()

        # Get a random action choice when: in the pre-training phase or we still wait to fill some data in the buffer, sampled value is less than epsilon,
        if self.total_steps <= self.pre_train_steps or \
            sampled_value < epsilon or \
            len(self.replayBuffer) < self.batch_size: \

            return np.random.choice(self.num_actions, size=[len(states), ])
        else:
            # Run the network and get the action to do for each of the states in the batch
            predict_q = self.dqn(states)

            # Get the argmax on the columns
            actions = np.argmax(predict_q, axis=1)

            return actions

    # Runs a single episode to collect training data
    # Returns the reward from this episode, the average loss and epsilon, avg magnitude of grads for each layer
    def run_episode(self) -> Tuple[float, float, float, tf.Tensor]:
        # Grab the initial state and convert it to a tensorflow type tensor
        initial_state = self.env.reset()
        initial_state = tf.constant(initial_state, dtype=tf.float32)

        initial_state_shape = initial_state.shape
        currentState = initial_state
        currentAction = None
        episode_reward = tf.constant(0.0, dtype=tf.float32)

        total_loss = 0.0
        # Accumulate the total gradient magnitude on each trainable variable
        total_grads_magnitude = tf.constant(0.0, shape=[len(self.dqn.trainable_variables),])
        num_losses_computed = 0
        epsilon = 1.0

        for episode_step in tf.range(self.max_steps_per_episode):
            # Get epsilon for this step
            epsilon = self.epsScheduler.getValue(step=self.total_steps) # Note that we use the total steps in this entire training process, not the local episode step

            # convert to a batch 1  tensor the state
            currentState_batched = tf.expand_dims(currentState, 0)

            # Should we keep the same action as before or sample a new one ?
            if episode_step % self.choose_action_frequency == 0:
                actions = self.get_action(currentState_batched, epsilon)
                currentAction = tf.constant(actions[0]) # Get the first action in the batch (corresponding to the currentState)

            # apply action get next step and reward
            newState, reward, done = self.tf_env_step(currentAction)
            newState.set_shape(initial_state_shape)
            episode_reward += reward

            # Add the experience to the replay buffer
            self.replayBuffer.add(state=currentState, action=currentAction, reward=reward, next_state=newState, done=done)

            # Check if we should do a training step: did we past the pre train phase and does the replay buffer contain a certain replay buffer size ?
            if (self.total_steps > self.pre_train_steps and len(self.replayBuffer) >= self.batch_size)\
                    and (self.total_steps % self.train_frequency == 0):
                loss, grads_magnitude = self.train_step()
                total_loss += loss
                total_grads_magnitude += grads_magnitude
                num_losses_computed += 1

            # Check if we should update the target network weights
            if self.method > MethodToUse.DQN_BASE and self.total_steps % self.steps_until_sync == 0:
                self.dqn_target.set_weights(self.dqn.get_weights())

            # Do final episode stuff: Update the current state, total episodes, etc.
            currentState = newState
            self.total_steps += 1

            # Episode ended ?
            if done == 1.0:
                break

        avgLoss = (total_loss/num_losses_computed if num_losses_computed > 0 else 0)
        avgGradsMagitude = (total_grads_magnitude/num_losses_computed if num_losses_computed > 0 else 0)
        return episode_reward, avgLoss, epsilon, avgGradsMagitude

    # Runs a train step using the current replay buffer
    # Returns the loss and gradients magnitude for updating the model
    def train_step(self):
        # Sample a batch from replay memory
        train_batch = self.replayBuffer.sample(batch_size=self.batch_size)

        # Get separate tensors for states, actions, rewards, nextstates, dones
        # I.e., from tuples to arrays, like zip function in python but in tensorflow now
        b_states = tf.stack([x[0] for x in train_batch], axis=0)
        b_actions = tf.stack([x[1] for x in train_batch], axis=0)
        b_rewards = tf.stack([x[2] for x in train_batch], axis=0)
        b_nextStates = tf.stack([x[3] for x in train_batch], axis=0)
        b_dones = tf.stack([x[4] for x in train_batch], axis=0)

        # REMEMBER THE THEORY:
        # 1. We have a current DQN model (self.dqn) that approximates the state-action value function: Q(state, action ; parameters of DQN model)
        # 2. But now we performed one step further from state, (state, action, reward, nextState, done), so we have an estimation that
        #           Q(state, action) SHOULD be closer to:
        #               (a) targetQ = (reward + Q(nextState, next best action from nextState; parameters of the TARGET DQN model)) if done is 0
        #               (b) targetQ = reward if done is 1 (it means that there is no next state and the reward obtained is the final one
        #    Intiuitively, why is this true ? Well, because from state we run a new step, got a reward and a next state. If we estimate the next state and take
        #               into account the new reward obtained, it should be closer to our goal estimation.
        #
        # 3. So the loss function can be simple Mean Squared Error (MSE) or hubber loss, etc between Q(state, action)  and targetQ, summed for each item in the batch
        # 4. Computing the gradient of parameters (of the model estimation network) respective to this loss will update them to be closer at each run
        # 5. Note: we can use a TARGET DQN model, fixed for a number of iterations to avoid running after a modifying target (get back to the course if you don't remember)

        # Now perform the loss computations under an automatic gradient computation scope
        with tf.GradientTape() as tape:
            # Get the list of trainable variables and make them watchable by the gradient tape
            dqn_variables = self.dqn.trainable_variables
            tape.watch(dqn_variables)

            # Step 1: Compute the targetQ value, i.e., the one that our estimation using DQN model should ideally return
            #===========================================================================
            # The code looks ugly a bit because it is vectorized.

            # Compute the estimated values from nextStates batch Q(nextState, a) for all a - use the target network now
            Q_nextState = self.dqn(b_nextStates) if self.method <= MethodToUse.DQN_BASE \
                                                else self.dqn_target(b_nextStates)   # This has shape batch_size x num_actions

            # Compute the next best action to select from Q_nextState (reduce on the columns axis in the batch)
            nextBestActions = tf.argmax(Q_nextState, axis=1) # This has shape batch_size x 1 (index of the best action from each nextState)

            # Compute the Q(nextState, next best action from best state). This will have dimension batch_size x 1
            # Well we should do Q_nextState[batchIndex, nextBestActions] but to vectorize it we have to:
            #       (a) transform the nextBestActions into a one_hot encoding,
            #               e.g., if best action index in a given index i is 2 out of 4 possible actions => [0 0 1 0]
            #       (b) multiply this with the Q_nextState (direct product on each row and column in both matrices)
            #               e.g., if Q_nextState for a given index i in the batch is: [12 429 998 1]
            #                       then multiplication will get  [0 0 998 0]
            #           doing this for all elements in the batch will give a shape of batch_size x num_actions (4 in the e.g. above)
            #       (c) reduce by columns to have a single item on each row: [0 0 998 0] => 998. Now we have the Q(nextState, best action from next state ) !

            b_nextBestActions_onehotEncoding = tf.one_hot(indices=nextBestActions, depth=self.num_actions) # (a)
            targetQ = b_nextBestActions_onehotEncoding * Q_nextState # (b)
            targetQ = tf.reduce_sum(targetQ, axis=1) # (c) ; Now it is batch_size x 1

            # (d) for each element in the batch: if done is true, then the reward is considered final ; if not, then add the estimation from next state too
            # Note: b_dones is batch_size x 1, 1 - b_dones is the same because of broadcast operator ! Search brodcast numpy if you are not sure about it
            targetQ = b_rewards + (1.0 - b_dones) * self.gamma * targetQ  # Output is batch_size x 1 finally !!

            # Step 2: compute the predictedQ, i.e., Q(state, action) for each state,action pair in the training batch sampled using the DQN model
            #===========================================================================

            # Get the estimates for each state in the batch
            Q_states = self.dqn(b_states)

            # Do the same trick for vectorization as above:
            #  (a) get the actions in one hot encoding
            #  (b) multiply the one hot with Q_states row by row
            #  (c) reduce to get the final estimation

            b_actions_onehotEncoding = tf.one_hot(indices=b_actions, depth=self.num_actions) # (a)
            predictedQ = b_actions_onehotEncoding * Q_states
            predictedQ = tf.reduce_sum(predictedQ, axis=1)


            # Step 3: finally apply the loss function
            # NOTE: the gradient tape will watch the variables and put back info to be able to apply gradients on each one respective to the loss function !
            loss = self.loss_function(y_true=targetQ, y_pred=predictedQ)


        # Step 4: Backpropagation: Compute the gradients from the loss and apply them using the optimizer
        # After this, our model should be better in terms of predictions...
        grads = tape.gradient(loss, dqn_variables)
        self.optimizer.apply_gradients(zip(grads, dqn_variables))

        # For debugging, just compute the gradients magnitude to be sure that we are still able to learn something...
        grads_magnitude = tf.convert_to_tensor([tf.norm(layer) for layer in grads])

        return loss, grads_magnitude

    def train(self, max_episodes,
                    max_steps_per_episode,
                    reward_threshold): # The threshold when we consider the env finished

        current_time = datetime.datetime.now().strftime("%Y%m%d-%H%M%S")
        train_log_dir = 'logs/train/' + str(self.method) + '/' + current_time
        train_summary_writer = tf.summary.create_file_writer(train_log_dir)

        episode_reward_history = []
        last_hundred_rewards = collections.deque(maxlen=100)

        self.max_episodes = max_episodes
        self.max_steps_per_episode = max_steps_per_episode

        with tqdm.trange(self.max_episodes) as t:
            for episode in t:
                # Run a full episode and get the reward from it
                episode_reward, avgLoss, epsilonUsed, gradsMagnitude = self.run_episode()

                # Update statistics from this episode
                episode_reward_history.append(episode_reward)
                last_hundred_rewards.append(episode_reward)
                mean_episode_reward = np.mean(last_hundred_rewards)

                t.set_description(f'Episode {episode}')
                t.set_postfix(episode_reward=episode_reward, running_reward=mean_episode_reward)
                if episode % 50 == 0:
                    print(f'\nEpisode {episode} (total step) {self.total_steps}: average reward: {mean_episode_reward}. avg loss: {avgLoss} epsilon used: {epsilonUsed} grads mag: {gradsMagnitude}')
                    with train_summary_writer.as_default():
                        tf.summary.scalar('episode_reward', episode_reward, step=episode)
                        tf.summary.scalar('running_reward', mean_episode_reward, step=episode)
                        tf.summary.scalar('avg loss', avgLoss, step=episode)
                        tf.summary.scalar('epsilon', epsilonUsed, step=episode)
                        #tf.summary.('grads magnitude', episo)

                if mean_episode_reward > reward_threshold:
                    break

        print(f"\nSolved at episode{episode}: average rewards {mean_episode_reward:.2f}!")

    def renderEpisode(self):
        # This is for X server
        #display = Display(visible=0, size=(400, 300))
        #display.start()

        env.reset()

        def render_episode(env: gym.Env, model: tf.keras.Model, max_steps: int):
            state = tf.constant(env.reset(), dtype=tf.float32)
            screen = env.render(mode='rgb_array')
            im = Image.fromarray(screen)

            images = [im]


            for i in range(1, max_steps + 1):
                state = tf.expand_dims(state, 0)
                qvalues = model(state)
                action = np.argmax(np.squeeze(qvalues))

                state, _, done, _ = env.step(action)
                state = tf.constant(state, dtype=tf.float32)

                # Render screen every 10 steps if you put % 10 there
                if i % 1 == 0:
                    screen = env.render(mode='rgb_array')
                    images.append(Image.fromarray(screen))

                if done:
                    break

            return images

        # Save GIF image
        images = render_episode(env, self.dqn, MAX_STEPS_PER_EPISODE)
        image_file = 'cartpole-v0.gif'
        # loop=0: loop forever, duration=1: play each frame for 1ms
        images[0].save(
            image_file, save_all=True, append_images=images[1:], loop=0, duration=10)

    def saveModel(self, modelName):
        self.dqn.save_weights(modelName)

    def loadModel(self, modelName):
        self.dqn.load_weights(modelName)
        self.dqn_target.set_weights(self.dqn.get_weights())

if __name__ == "__main__":
    env = gym.make("CartPole-v0")

    methodToUse : MethodToUse = MethodToUse.DQN_TARGET_NETWORK #MethodToUse.DQN_BASE

    seed = None # 42 # Put here a fixed number for determinism !

    agent = Agent_DQN(env, seed=seed, gamma=0.99, batch_size=64, lr=0.0007,
                           steps_until_sync=200, choose_action_frequency=1,
                           train_frequency=1, replayBufferSize=32000, pre_train_steps=100,
                           epsScheduler=Utils_replay.LinearScheduleEpsilon(start_eps=1, final_eps=0.1,
                                                                           pre_train_steps=100, final_eps_step=10000),
                           method=methodToUse)

    if TRAINING_MODE:
        agent.train(max_episodes=MAX_NUM_EPISODES,
                         reward_threshold=REWARD_THRESHOLD,
                         max_steps_per_episode=MAX_STEPS_PER_EPISODE)

        agent.saveModel(str(methodToUse))
    else:
        agent.loadModel(str(methodToUse))

    agent.renderEpisode()

# TODO: try without standardize,
# save model
# render model fix
# DQN
