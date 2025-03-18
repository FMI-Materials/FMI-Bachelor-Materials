import numpy as np
from collections import defaultdict
import sys
import random
from tqdm import trange
import datetime
import gym
import numpy as np
from collections import defaultdict
import matplotlib.pyplot as plt
import pickle
from tqdm import trange
import seaborn as sns
import pandas as pd
from random import random
from datetime import datetime

# Inputs:
"""
the taxi agent
the number of piesodes to run on
if it should plot statistics or not in the end
"""
# Returns for each episode in this order:
"""
- A list of scores per episode
- A list of moving averag scores over the last 100 episodes at each time t
- A list of number of actions performed per episode
- A list of num illegal moves on each episode
- A list of ilegal drops / pickups actions on each episode
"""


def TrainTaxiAgent(env, taxiAgent, numEpisodes=200, plotStats=True, storeFramesDescription=True):
    moving_nb = 100
    solved_score = 8.5

    scores = []
    ts = []
    illegal_moves = []
    illegal_others = []
    moving_scores = []
    frames = []  # Description per frame of actions stored for the last episode
    start_time = datetime.now()

    for episodeIndex in trange(numEpisodes):
        frames = []

        # for the record
        score = 0
        t = 0
        illegal_move = 0
        illegal_other = 0

        # initiate state
        state = env.reset()
        while True:

            # get action
            epsAtEpisode = taxiAgent.get_epsilon(episodeIndex)
            action = taxiAgent.select_action(state, epsilon=epsAtEpisode)

            # step environment
            next_state, reward, done, info = env.step(action)

            # update agent
            taxiAgent.updateExperience(state, action, reward, next_state, episodeIndex)

            # records
            score += reward
            t += 1
            if state == next_state:
                illegal_move += 1

            if reward == -10:
                illegal_other += 1

            # move to next state
            state = next_state

            # Store the frame description
            if storeFramesDescription:
                if episodeIndex == numEpisodes - 1:  # Store only for the last episode..
                    frames.append({
                        'frame': env.render(mode='ansi'),
                        'state': state,
                        'action': action,
                        'reward': reward,
                        'cumulative_reward': score,
                        'illegal_moves': illegal_move,
                        'illegal_others': illegal_other
                    })

            # end if drop off at destination
            if reward == 20:
                break

        # record
        scores.append(score)
        ts.append(t)
        illegal_moves.append(illegal_move)
        illegal_others.append(illegal_other)

        if episodeIndex > moving_nb:
            moving_score = np.mean(scores[episodeIndex - moving_nb:episodeIndex])
            moving_scores.append(moving_score)
        else:
            moving_scores.append(0)

        # break if solved
        if moving_scores[-1] > solved_score:
            print(f'Solved at Play {episodeIndex}: {datetime.now() - start_time} Moving average: {moving_scores[-1]}')
            break

    if plotStats:
        plt.title("Scores per episode and moving scores")
        plt.plot(scores)
        plt.plot(moving_scores)
        plt.show()
        print(f'Last 100-episode average score at the end of simulation: {moving_scores[-1]}')

        plt.title("Number of actions performed per episode")
        plt.plot(ts)
        plt.show()
        print(f'Last 100-episode average number of actions performed: {np.mean(ts[:-100])}')

        plt.title("The number of illegal moves performed")
        plt.plot(illegal_moves)
        plt.plot(illegal_others)
        plt.legend()
        print(
            f'Illegal moves in the last episode: {illegal_moves[-1]}; Illegal drop-offs/pickups in the last episode: {illegal_others[-1]}')

    # print(taxiAgent.q)
    return frames


class TaxiAgent:
    def __init__(self, env, gamma=0.8, alpha=1e-1,
                 start_epsilon=1, end_epsilon=1e-2, epsilon_decay=0.999):

        self.env = env
        self.n_action = self.env.action_space.n
        self.gamma = gamma
        self.alpha = alpha

        # action values
        self.q = defaultdict(lambda: np.zeros(self.n_action))  # action value

        # epsilon greedy parameters
        self.start_epsilon = start_epsilon
        self.end_epsilon = end_epsilon
        self.epsilon_decay = epsilon_decay

    # get epsilon
    def get_epsilon(self, n_episode):
        epsilon = max(self.start_epsilon * (self.epsilon_decay ** n_episode), self.end_epsilon)
        return (epsilon)

    # select action based on epsilon greedy
    def select_action(self, state, epsilon):
        # implicit policy; if we have action values for that state, choose the largest one, else random
        best_action = np.argmax(self.q[state]) if state in self.q else self.env.action_space.sample()
        if np.random.rand() > epsilon:
            action = best_action
        else:
            action = self.env.action_space.sample()
        return (action)

    # Given (state, action, reward, next_state) pair after a transition made in the e nvironment and the episode index
    def updateExperience(self, state, action, reward, next_state, n_episode):
        pass # No update in this random agent

class SARSA_TaxiAgent(TaxiAgent):
    def __init__(self, env, gamma=0.8, alpha=1e-1,
                 start_epsilon=1, end_epsilon=1e-2, epsilon_decay=0.999):
        super().__init__(env, gamma, alpha, start_epsilon, end_epsilon, epsilon_decay)

    def updateExperience(self, state, action, reward, next_state, n_episode):
        pass


class ExpectedSARSA_TaxiAgent(TaxiAgent):
    def __init__(self, env, gamma=0.8, alpha=1e-1,
                 start_epsilon=1, end_epsilon=1e-2, epsilon_decay=0.999):
        super().__init__(env, gamma, alpha, start_epsilon, end_epsilon, epsilon_decay)

    def updateExperience(self, state, action, reward, next_state, n_episode):
        pass


class QLearning_TaxiAgent(TaxiAgent):
    def __init__(self, env, gamma=0.8, alpha=1e-1,
                 start_epsilon=1, end_epsilon=1e-2, epsilon_decay=0.999):
        super().__init__(env, gamma, alpha, start_epsilon, end_epsilon, epsilon_decay)

    # Given (state, action, reward, next_state) pair after a transition made in the e nvironment and the episode index
    def updateExperience(self, state, action, reward, next_state, n_episode):
        pass

# Just a dummy debug thing for your work if you want
if __name__ == "__main__":
    env = gym.make('Taxi-v3')
    if True:
        sarsaAgent = ExpectedSARSA_TaxiAgent(env, gamma=0.8, alpha=1e-1,
                      start_epsilon=1, end_epsilon=1e-2, epsilon_decay=0.999)

        TrainTaxiAgent(env, taxiAgent=sarsaAgent, numEpisodes=100000, plotStats=True, storeFramesDescription=False)

    else:
        qlearningAgent = QLearning_TaxiAgent(env, gamma=0.8, alpha=1e-1,
                      start_epsilon=1, end_epsilon=1e-2, epsilon_decay=0.999)

        TrainTaxiAgent(env, taxiAgent=qlearningAgent, numEpisodes=100000, plotStats=True, storeFramesDescription=False)
