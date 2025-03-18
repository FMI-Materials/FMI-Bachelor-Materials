import numpy as np
import gym
import time
import math

env = gym.make("CartPole-v1")
print("Actions space:" + str(env.action_space.n))

LEARNING_RATE = 0.1

DISCOUNT = 0.95
EPISODES = 60000
total = 0
total_reward = 0
prior_reward = 0

Observation = [30, 30, 50, 50]
np_array_win_size = np.array([0.25, 0.25, 0.01, 0.1])

epsilon = 1

epsilon_decay_value = 0.99995

q_table = np.random.uniform(low=0, high=1, size=(Observation + [env.action_space.n]))
print(q_table.shape)


def get_discrete_state(state):
    discrete_state = state / np_array_win_size + np.array([15, 10, 1, 10])
    return tuple(discrete_state.astype(int))


for episode in range(EPISODES + 1):  # go through the episodes
    t0 = time.time()  # set the initial time
    discrete_state = get_discrete_state(env.reset())  # get the discrete start for the restarted environment
    done = False
    episode_reward = 0  # reward starts as 0 for each episode

    if episode % 2000 == 0:
        print("Episode: " + str(episode))

    while not done:

        if np.random.random() > epsilon:
            action = np.argmax(q_table[discrete_state])  # take best action
        else:
            action = np.random.randint(0, env.action_space.n)  # do a random action

        new_state, reward, done, _ = env.step(action)  # step action to get new states, reward, and the "done" status.
        episode_reward += reward  # add the reward
        new_discrete_state = get_discrete_state(new_state)

        if episode % 2000 == 0:  # render
            env.render()

        if not done:  # update q-table
            max_future_q = np.max(q_table[new_discrete_state])
            current_q = q_table[discrete_state + (action,)]
            new_q = (1 - LEARNING_RATE) * current_q + LEARNING_RATE * (reward + DISCOUNT * max_future_q)
            q_table[discrete_state + (action,)] = new_q

        discrete_state = new_discrete_state

    if epsilon > 0.05:  # epsilon modification
        if episode_reward > prior_reward and episode > 10000:
            epsilon = math.pow(epsilon_decay_value, episode - 10000)

            if episode % 500 == 0:
                print("Epsilon: " + str(epsilon))

    t1 = time.time()  # episode has finished
    episode_total = t1 - t0  # episode total time

    total = total + episode_total
    total_reward += episode_reward  # episode total reward
    prior_reward = episode_reward

    if episode % 1000 == 0:  # every 1000 episodes print the average time and the average reward
        mean = total / 1000
        print("Time Average: " + str(mean))
        total = 0

        mean_reward = total_reward / 1000
        print("Mean Reward: " + str(mean_reward))
        total_reward = 0
