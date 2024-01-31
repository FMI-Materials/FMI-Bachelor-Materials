import os.path
import random
import time
import copy
import pygame
import sys

JMAX = 1
JMIN = 2


def min_max(state, estimate_function="computer_1"):
    # daca sunt la o frunza in arborele minimax sau la o state finala
    if state.depth == 0 or state.game_table.final():
        state.estimate = state.game_table.estimate_score(state.depth, estimate_function)
        state.nodes = 1
        return state

    # calculez toate mutarile posibile din starea curenta
    state.possible_moves = state.moves()

    # aplic algoritmul minimax pe toate mutarile posibile (calculand astfel subarborii lor)
    # expandez(constr subarb) fiecare nod x din moves posibile
    moves_with_estimate = [min_max(x, estimate_function) for x in state.possible_moves]
    state.nodes += sum([x.nodes for x in moves_with_estimate])

    if state.j_curent == JMAX:
        # daca jucatorul e JMAX aleg starea-fiica cu estimarea maxima
        state.chosen_state = max(moves_with_estimate, key=lambda x: x.estimate)
        # def f(x): return x.estimate -----> key=f
    else:
        # daca jucatorul e JMIN aleg starea-fiica cu estimarea minima
        state.chosen_state = min(moves_with_estimate, key=lambda x: x.estimate)

    state.estimate = state.chosen_state.estimate
    return state


""" Algoritmul Alpha Beta """


def alpha_beta(alpha, beta, state, estimate_function="computer_1"):
    if state.depth == 0 or state.game_table.final():
        state.estimate = state.game_table.estimate_score(state.depth, estimate_function)
        state.nodes = 1
        return state

    if alpha > beta:
        return state  # este intr-un interval invalid deci nu o mai procesez

    state.possible_moves = state.moves()

    if state.j_curent == JMAX:
        current_estimation = float('-inf')  # in aceasta variabila calculam maximul

        # Ordonarea succesorilor înainte de expandare (bazat pe estimare)
        state.possible_moves.sort(key=lambda x: x.game_table.estimate_score(state.depth, estimate_function),
                                  reverse=True)

        for move in state.possible_moves:
            # calculează estimarea pentru starea nouă, realizând subarborele
            # aici construim subarborele pentru new_state
            new_state = alpha_beta(alpha, beta, move, estimate_function)
            state.nodes += new_state.nodes
            if current_estimation < new_state.estimate:
                state.chosen_state = new_state
                current_estimation = new_state.estimate
            if alpha < new_state.estimate:
                alpha = new_state.estimate
                if alpha >= beta:
                    break

    elif state.j_curent == JMIN:
        current_estimation = float('inf')

        # Ordonarea succesorilor înainte de expandare (bazat pe estimare)
        state.possible_moves.sort(key=lambda x: x.game_table.estimate_score(state.depth, estimate_function))

        for move in state.possible_moves:
            # calculează estimarea
            # aici construim subarborele pentru new_state
            new_state = alpha_beta(alpha, beta, move, estimate_function)
            state.nodes += new_state.nodes
            if current_estimation > new_state.estimate:
                state.chosen_state = new_state
                current_estimation = new_state.estimate
            if beta > new_state.estimate:
                beta = new_state.estimate
                if alpha >= beta:
                    break

    state.estimate = state.chosen_state.estimate

    return state


if __name__ == "__main__":
    print("hello")
