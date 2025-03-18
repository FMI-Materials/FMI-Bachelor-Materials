import numpy as np
from collections import defaultdict
import sys
import random
from tqdm import trange

import gym
import numpy as np
from collections import defaultdict
import matplotlib.pyplot as plt
import pickle
from tqdm import trange
import seaborn as sns
import pandas as pd
from random import random
import abc
import warnings
warnings.filterwarnings("ignore")

class BJAgent:
    def __init__(self, env, gamma=1.0,
                 start_epsilon=1.0, end_epsilon=0.05, epsilon_decay=0.99999):
        self.env = env
        self.n_action = self.env.action_space.n
        self.policy = defaultdict(lambda: 0)  # always stay as default init policy
        self.v = defaultdict(lambda: 0)  # state value initiated as 0
        self.gamma = gamma

        # action values
        # Q(St, At)
        self.q = defaultdict(lambda: np.zeros(self.n_action))  # action value

        # N(St, At)
        self.n_q = defaultdict(lambda: np.zeros(self.n_action))  # number of actions by type performed in each state

        # epsilon greedy parameters
        self.start_epsilon = start_epsilon
        self.end_epsilon = end_epsilon
        self.epsilon_decay = epsilon_decay

    # get the best action in the current state according to the internal policy
    def getAction(self, state):
        if state not in self.policy:
            return self.env.action_space.sample()
        return self.policy[state]


class MonteCarlo_BJAgent(BJAgent):
    def __init__(self, env, gamma=1.0,
                 start_epsilon=1.0, end_epsilon=0.05, epsilon_decay=0.99999):
        super().__init__(env, gamma, start_epsilon, end_epsilon, epsilon_decay)

        self.env = env
        self.n_action = self.env.action_space.n
        self.policy = defaultdict(lambda: 0)  # always stay as default init policy
        self.v = defaultdict(lambda: 0)  # state value initiated as 0
        self.gamma = gamma

        # action values
        # Q(St, At)
        self.q = defaultdict(lambda: np.zeros(self.n_action))  # action value

        # N(St, At)
        self.n_q = defaultdict(lambda: np.zeros(self.n_action))  # number of actions by type performed in each state

        # epsilon greedy parameters
        self.start_epsilon = start_epsilon
        self.end_epsilon = end_epsilon
        self.epsilon_decay = epsilon_decay

    # mc control GLIE
    # Params:
    # The number of episodes to run
    # If it should be first visit or each visit method
    # On how many episodes should it update the policy again. By default, on each episode
    def mc_control_glie(self, n_episode=500000, firstVisit=True, update_policy_every=1):
        # Do you code inside this function, feel free to add other class members as well
        pass


    # get state value from action value
    def q_to_v(self):
        for state, values in self.q.items():
            self.v[state] = np.max(values)


# Just for testing purposes, no need to play but it is usefull for debugging purposes
if __name__ == "__main__":
    def run_single_episode(agent):
        result = []
        state = env.reset()
        while True:
            action = agent.getAction(state)
            next_state, reward, done, info = env.step(action)
            result.append((state, action, reward, next_state, done))
            if done:
                break
            state = next_state
        return (result)  # must return a list of tuples (state,action,reward,next_state,done)

    env = gym.make('Blackjack-v1')

    # Random eval
    agent_random = BJAgent(env)
    res = run_single_episode(agent_random)
    print(res)

    """
    # MC eval
    a = MonteCarlo_BJAgent(env)
    a.mc_control_glie(n_episode=10000, firstVisit=False)
    """