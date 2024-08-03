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
from enum import Enum
eps = np.finfo(np.float32).eps.item()


# Some parameters for training and model
num_hidden_units = 128
num_actions = None # env decision
MAX_NUM_EPISODES = 10000
MAX_STEPS_PER_EPISODE = 1000
STANDARDIZE_RETURNS = True # If returns should be standardized or not

TRAINING_MODE = True


# Considered solved when the average reward is >= 195 over 100 frames
REWARD_THRESHOLD = 195
GAMMA = 0.99


# BIG PERFORMANCE WARNING !!!!!
tf.config.run_functions_eagerly(True)

class MethodToUse(Enum):
    ACTOR_CRITIC = 1

class ActorCriticModel(tf.keras.Model):
    def __init__(self,
                 num_actions:int,
                 num_hidden_units: int):
        super().__init__()

        self.common = layers.Dense(num_hidden_units, activation="relu")
        self.actor = layers.Dense(num_actions)
        self.critic = layers.Dense(1)

    def call(self, inputs: tf.Tensor) -> Tuple[tf.Tensor, tf.Tensor]:
        x = self.common(inputs)
        return self.actor(x), self.critic(x)

class EnvInteraction():
    def __init__(self, env, model, seed = None):
        self.model = model
        self.env = env


        self.huber_loss = tf.keras.losses.Huber(reduction=tf.keras.losses.Reduction.SUM)

        # Optimizer setup
        self.optimizer = tf.keras.optimizers.Adam(learning_rate=0.01)

        # Have deterministic output at each run for easy debugging
        if seed is not None:
            self.env.seed(seed)
            tf.random.set_seed(seed)
            np.random.seed(seed)

        obs = self.env.reset()
        newobs, reward, done, inf = self.env.step(0)
        num_actions = self.env.action_space.n

    # Receive action returns a state, reward, done
    # We wrap-up this to be compatible in a tf graph op
    def env_step(self, action : np.ndarray) -> Tuple[np.ndarray, np.ndarray, np.ndarray]:
        state, reward, done, _ = self.env.step(action)
        return (state.astype(np.float32),
                np.array(reward, np.int32),
                np.array(done, np.int32))

    def tf_env_step(self, action:tf.Tensor) -> List[tf.Tensor]:
        return tf.numpy_function(self.env_step, [action], [tf.float32, tf.int32, tf.int32])

    # Runs a single episode to collect training data
    # List of 3 tensors: action_probs, values, rewards
    def run_episode(self, max_steps:int) -> List[tf.Tensor]:
        initial_state = tf.constant(self.env.reset(), tf.float32)

        action_probs = tf.TensorArray(dtype=tf.float32, size=0, dynamic_size=True)
        values = tf.TensorArray(dtype=tf.float32, size=0, dynamic_size=True)
        rewards = tf.TensorArray(dtype=tf.int32, size=0, dynamic_size=True)

        initial_state_shape=initial_state.shape
        state = initial_state

        for t in tf.range(max_steps): # what if range ?
            # convert to a batch 1 tensor the state
            state = tf.expand_dims(state, 0)

            # run model, get action probs and critic value
            action_logits_t, value = self.model(state)

            # sample next action and store the log prob of the action taken
            action = tf.random.categorical(action_logits_t, 1)
            action = action[0,0]
            action_logits_t = tf.nn.softmax(action_logits_t)
            action_probs = action_probs.write(t, action_logits_t[0, action])

            # store critic value
            values = values.write(t, tf.squeeze(value))

            # apply action get next step and reward
            state, reward, done = self.tf_env_step(action)
            state.set_shape(initial_state_shape)

            # store reward
            rewards = rewards.write(t, reward)

            if tf.cast(done, tf.bool): # what if bool ?
                break

        action_probs = action_probs.stack()
        values = values.stack()
        rewards = rewards.stack()

        return action_probs, values, rewards

    def policyGradient_compute_loss(self, action_probs : tf.Tensor, values : tf.Tensor, returns : tf.Tensor) -> tf.Tensor:
        advantage = returns - values
        action_log_probs = tf.math.log(action_probs)
        actor_loss = -tf.math.reduce_sum(action_log_probs * advantage)
        critic_loss = self.huber_loss(values, returns)
        return actor_loss + critic_loss


    def policyGradient_get_expected_returns(self, rewards : tf.Tensor, gamma, standardize: bool = True)->tf.Tensor:
        # expected return per timestep
        n = tf.shape(rewards)[0] # num items
        returns = tf.TensorArray(dtype=tf.float32, size=n)

        rewards = tf.cast(rewards[::-1], tf.float32)
        discounted_sum = tf.constant(0.0)
        discounted_sum_shape = tf.shape(discounted_sum)
        for i in tf.range(n):
            reward = rewards[i]
            discounted_sum = reward + gamma * discounted_sum
            discounted_sum.set_shape(discounted_sum_shape)
            returns = returns.write(i, discounted_sum)
        returns = returns.stack()[::-1]

        if standardize:
            returns = ((returns - tf.math.reduce_mean(returns)) / (tf.math.reduce_std(returns) + eps))

        return returns

    # Runs a train episode and returns the reward
    def policyGradient_train_step(self, max_steps_per_episode, gamma, standardize=STANDARDIZE_RETURNS) -> tf.Tensor:
        with tf.GradientTape() as tape:
            # Run model for one episode and collect training data
            action_probs, values, rewards = self.run_episode(max_steps=max_steps_per_episode)

            # Compute the expected returns
            returns = self.policyGradient_get_expected_returns(rewards, gamma)

            # Convert to the batch shapes
            action_probs, values, returns = [tf.expand_dims(x, 1) for x in [action_probs, values, returns]]

            # Compute loss values
            loss = self.policyGradient_compute_loss(action_probs, values, returns)

        # Compute the gradients from the loss
        grads = tape.gradient(loss, model.trainable_variables)
        self.optimizer.apply_gradients(zip(grads, model.trainable_variables))

        episode_reward = tf.math.reduce_sum(rewards)
        return episode_reward

    def train(self, max_episodes, reward_threshold, max_steps_per_episode,
              method : MethodToUse = MethodToUse.ACTOR_CRITIC):

        current_time = datetime.datetime.now().strftime("%Y%m%d-%H%M%S")
        train_log_dir = 'logs/train/' + str(method) + '/' + current_time
        train_summary_writer = tf.summary.create_file_writer(train_log_dir)

        running_reward = 0

        with tqdm.trange(max_episodes) as t:
            for i in t:
                initial_state = tf.constant(self.env.reset(), dtype=tf.float32)

                rewardObtained = None
                if method == MethodToUse.ACTOR_CRITIC:
                    rewardObtained = self.policyGradient_train_step(max_steps_per_episode=max_steps_per_episode, gamma=GAMMA)

                episode_reward = int(rewardObtained)
                running_reward = episode_reward*0.01 + running_reward*0.99

                t.set_description(f'Episode {i}')
                t.set_postfix(episode_reward=episode_reward, running_reward=running_reward)
                if i % 10 == 0:
                    print(f'Episode {i}: average reward: {running_reward}')

                with train_summary_writer.as_default():
                    tf.summary.scalar('episode_reward', episode_reward, step=i)
                    tf.summary.scalar('running_reward', running_reward, step=i)

                if running_reward > reward_threshold:
                    break

        print(f"\nSolved at episode{i}: average rewards {running_reward:.2f}!")

    def renderEpisode(self):
        # This is for X server
        #display = Display(visible=0, size=(400, 300))
        #display.start()

        def render_episode(env: gym.Env, model: tf.keras.Model, max_steps: int):
            screen = env.render(mode='rgb_array')
            im = Image.fromarray(screen)

            images = [im]

            state = tf.constant(env.reset(), dtype=tf.float32)
            for i in range(1, max_steps + 1):
                state = tf.expand_dims(state, 0)
                action_probs, _ = model(state)
                action = np.argmax(np.squeeze(action_probs))

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
        images = render_episode(env, model, MAX_STEPS_PER_EPISODE)
        image_file = 'cartpole-v0.gif'
        # loop=0: loop forever, duration=1: play each frame for 1ms
        images[0].save(
            image_file, save_all=True, append_images=images[1:], loop=0, duration=10)

if __name__ == "__main__":
    env = gym.make("CartPole-v0")
    num_actions = env.action_space.n

    methodToUse : MethodToUse = MethodToUse.ACTOR_CRITIC

    seed = None # 42 # Put here a fixed number for determinism !

    if TRAINING_MODE:
        model = ActorCriticModel(num_actions, num_hidden_units)
        envWrapper = EnvInteraction(env, model, seed=seed)
        envWrapper.train(max_episodes=MAX_NUM_EPISODES,
                         reward_threshold=REWARD_THRESHOLD,
                         max_steps_per_episode=MAX_STEPS_PER_EPISODE)
        model.save(str(methodToUse))
    else:
        model = tf.keras.models.load_model(str(methodToUse))
        envWrapper = EnvInteraction(env, model, seed=seed)

    envWrapper.renderEpisode()

# TODO: try without standardize,
# save model
# render model fix
# DQN
