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
        if state[0] not in self.policy:
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

    # get epsilon to use for each episode
    def get_epsilon(self, n_episode):
        epsilon = max(self.start_epsilon * (self.epsilon_decay ** n_episode), self.end_epsilon)
        return (epsilon)

    # select action based on epsilon greedy
    def select_action(self, state, epsilon):
        if epsilon != None and np.random.rand() < epsilon:
            action = self.env.action_space.sample()
        else:
            if state[0] in self.q:
                action = self.policy[state[0]]
            else:
                action = self.env.action_space.sample()
        return action

    # run episode with current policy
    def run_episode(self, eps=None):
        result = []
        state = self.env.reset()
        while True:
            action = self.select_action(state, eps)
            next_state, reward, done, info, _ = self.env.step(action)
            result.append((state, action, reward, next_state, done))
            state = next_state
            if done:
                break
        return result

    # update policy to reflect q values, basically select in each state:
    # pi(state) = argmax action from Q(state, action)
    def update_policy_q(self, eps=None):
        for state, values in self.q.items():
            if eps != None: # e-Greedy policy updates ?
                if np.random.rand() < eps:
                    self.policy[state] = self.env.action_space.sample() # sample a random action
                else:
                    self.policy[state] = np.argmax(values)

            else: # Greedy policy updates
                self.policy[state] = np.argmax(values)

    # mc control GLIE
    # Params:
    # The number of episodes to run
    # If it should be first visit or each visit method
    # On how many episodes should it update the policy again. By default, on each episode
    def mc_control_glie(self, n_episode=500000, firstVisit=True, update_policy_every=1):
        for t in trange(n_episode):
            traversed = []
            # Get an epsilon for this episode - used in e-greedy policy update
            eps = self.get_epsilon(t)

            # Generate an episode following current policy
            transitions = self.run_episode(eps=None)

            # zip operation will convert transitions to list of states, list of actions, rewards etc.
            states, actions, rewards, next_states, dones = zip(*transitions)

            # If firstVisit version is used, create a table stateAction_firstVisitTime that stores
            # when the pair (State, action) was seen first in this episode
            if firstVisit == True:
                stateAction_firstVisitTime = {}
                for t, state in enumerate(states):
                    stateAction_t = (state, actions[t])
                    if stateAction_t not in stateAction_firstVisitTime:
                        stateAction_firstVisitTime[stateAction_t] = t

            # Iterate over episode steps in reversed order, T-1, T-2, ....0
            G = 0 # return output
            for t in range(len(transitions)-1, -1, -1):
                St = states[t][0]
                At = actions[t]

                if firstVisit == True:
                    # Is t first time when we see the (state, action) pair ?
                    if stateAction_firstVisitTime[(St, At)] < t:
                        continue

                G = self.gamma * G + rewards[t]

                self.n_q[St][At] += 1
                alpha = (1.0 / self.n_q[St][At]) # Remember that with this formula all episodes experiences have equal importance, if you want to forget older episode put a bigger probability
                self.q[St][At] = self.q[St][At] + alpha*(G - self.q[St][At])

            if t % update_policy_every == 0:
                self.update_policy_q(eps)

        # final policy update at the end
        self.update_policy_q(eps)


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
            next_state, reward, done, info, _ = env.step(action)
            result.append((state, action, reward, next_state, done))
            if done:
                break
            state = next_state
        dealer_sum = sum(env.dealer)
        return (result, dealer_sum)  # must return a list of tuples (state,action,reward,next_state,done)

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