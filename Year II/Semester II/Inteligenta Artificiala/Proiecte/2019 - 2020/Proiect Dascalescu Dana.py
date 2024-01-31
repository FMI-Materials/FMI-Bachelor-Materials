# import pygame
from copy import deepcopy
import time
import sys


""" Variables defined for initializing game """
INFINITY = 2 ** 32 - 1

default_table = [
    ['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'],
    ['#', '1', ' ', ' ', ' ', 'p', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', '#', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', '#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#'],
    ['#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', ' ', 'p', ' ', '#', ' ', ' ', 'p', ' ', ' ', '#', ' ', ' ', '#', '#', '#', ' ', '#', '#'],
    ['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', '#', '#', '#', ' ', ' ', ' ', ' ', '#', '#'],
    ['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'p', ' ', ' ', ' ', ' ', ' ', 'p', '#'],
    ['#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', '#', 'p', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
    ['#', ' ', '#', '#', '#', '#', ' ', ' ', '#', ' ', ' ', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', ' ', '#'],
    ['#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '2', '#'],
    ['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'],
]

player1_position = [1, 1]
player2_position = [11, 20]
items_positions = [[4, 5], [4, 10], [7, 14], [9, 13], [1, 5]]
no_moves = 0



def manhattan_distance(pos_1, pos_2):
    return abs(pos_1[0] - pos_2[0]) + abs(pos_1[1] - pos_2[1])



class Player:
    def __init__(self, position, player_symbol, bomb_activate = False, bomb_position = [-1, -1], no_protections = 0):
        self.position = position
        self.player_symbol = player_symbol
        self.bomb_activate = bomb_activate
        self.bomb_position = bomb_position
        self.no_protections = no_protections
    
    def has_died(self, opponent, game_map):
        if self.bomb_activate == True:
            # bomb belongs to player and is active => we will check if the bomb is on the same line or column as the player, viz. check if the
            # explosion will affect the player: player will survive if there is an obstacle between him and the bomb otherwise, he will survive
            # only if it he/she has at least a protection
            if self.position[0] == self.bomb_position[0]:
                # a bomb is placed on the same line as the player
                start = self.position[1] if self.position[1] < self.bomb_position[1] else self.bomb_position[1]
                finish = self.position[1] if start == self.bomb_position[1] else self.bomb_position[1]
                for j in range(start + 1, finish):
                    if game_map[self.position[0]][j] == '#':
                        self.bomb_activate = False
                        game_map[self.bomb_position[0]][self.bomb_position[1]] = ' '
                        self.bomb_position = [-1, -1]
                        return False # player is alive
                
                if self.no_protections > 0:
                    self.no_protections -= 1
                    self.bomb_activate = False
                    game_map[self.bomb_position[0]][self.bomb_position[1]] = ' '
                    self.bomb_position = [-1, -1]
                    return False
               
                return True

            elif self.position[1] == self.bomb_position[1]:
                # a bomb is placed on the same column as the player
                start = self.position[0] if self.position[0] < self.bomb_position[0] else self.bomb_position[0]
                finish = self.position[0] if start == self.bomb_position[0] else self.bomb_position[0]

                for i in range(start + 1, finish):
                    if game_map[i][self.position[1]] == '#':
                        self.bomb_activate = False
                        game_map[self.bomb_position[0]][self.bomb_position[1]] = ' '
                        self.bomb_position = [-1, -1]
                        return False

                if self.no_protections > 0:
                    self.no_protections -= 1
                    self.bomb_activate = False
                    game_map[self.bomb_position[0]][self.bomb_position[1]] = ' '
                    self.bomb_position = [-1, -1]
                    return False

                return True

        if opponent.bomb_activate == True:
            # opponent activated his bomb => check if the player will be in the range of the explosion
            if self.position[0] == opponent.bomb_position[0]:
                start = self.position[1] if self.position[1] < opponent.bomb_position[1] else opponent.bomb_position[1]
                finish = self.position[1] if start == opponent.bomb_position[1] else opponent.bomb_position[1]

                for j in range(start + 1, finish):
                    if game_map[self.position[0]][j] == '#':
                        opponent.bomb_activate = False
                        game_map[opponent.bomb_position[0]][opponent.bomb_position[1]] = ' '
                        opponent.bomb_position = [-1, -1]
                        return False

                if self.no_protections > 0:
                    self.no_protections -= 1
                    opponent.bomb_activate = False
                    game_map[opponent.bomb_position[0]][opponent.bomb_position[1]] = ' '
                    opponent.bomb_position = [-1, -1]
                    return False

                return True

            elif self.position[1] == opponent.bomb_position[1]:
                start = self.position[0] if self.position[0] < opponent.bomb_position[0] else opponent.bomb_position[0]
                finish = self.position[0] if start == opponent.bomb_position[0] else opponent.bomb_position[0]

                for i in range(start + 1, finish):
                    if game_map[i][self.position[1]] == '#':
                        opponent.bomb_activate = False
                        game_map[opponent.bomb_position[0]][opponent.bomb_position[1]] = ' '
                        opponent.bomb_position = [-1, -1]
                        return False

                if self.no_protections > 0:
                    self.no_protections -= 1
                    opponent.bomb_activate = False
                    game_map[opponent.bomb_position[0]][opponent.bomb_position[1]] = ' '
                    opponent.bomb_position = [-1, -1]
                    return False

                return True

        return False


    def __eq__(self, other):
        if isinstance(other, Player):
            return other.player_symbol == self.player_symbol
        elif other == self.player_symbol:
            return True

        return False
        

class GameConfiguration:
    """
    Refers to a game configuration (a node in the game graph). The attributes of the GameConfiguration class do NOT change at all 
    during the entire game, but they can be changed from one game to another.
    """

    NO_ROWS = 13
    NO_COLUMNS = 22
    PMIN = None
    PMAX = None
    EMPTY = ' '

    """
        The attributes of an object in the Game Configuration class are those that can be changed from one game configuration to the next,
        following the execution of a valid game move.
    """ 

    def __init__(self, player1, player2, game_map = None):
        self.game_map = game_map or [[GameConfiguration.EMPTY for j in range(GameConfiguration.NO_COLUMNS)] for i in range(GameConfiguration.NO_ROWS)]
        self.player1 = player1  # object of type Player
        self.player2 = player2  # object of type Player


    # Returns a list of GameConfiguration objects, representing all valid game configurations as successors
    def game_moves(self, player_s):
        bomb_was_placed = False
        directions = [[-1,0], [0,1], [1,0], [0,-1]]
        moves = []

        if self.player1 == player_s:
            player = deepcopy(self.player1)
            opponent = deepcopy(self.player2)
        else:
            player = deepcopy(self.player2)
            opponent = deepcopy(self.player1)

        if player.bomb_activate == True:
            # bomb was activated in a previous round => it exploded but did not affect any player
            self.game_map[player.bomb_position[0]][player.bomb_position[1]] = ' '
            player.bomb_position = [-1, -1]
            player.bomb_activate = False


        # if the opponent gets too close, PMAX should put a bomb
        if manhattan_distance(player.position, opponent.position) <= 5 and player.bomb_position == [-1, -1]:
            # PMAX doesn't have other bomb placed before, so he can put one now
            player.bomb_position = player.position
            bomb_was_placed = True
        elif manhattan_distance(player.position, opponent.position) <= 5:
            # PMAX already placed a bomb and need to detonate it first
            if player.position[0] != player.bomb_position[0] and player.position[1] != player.bomb_position:
                player.bomb_activate = True


        for direction in directions:
            new_move = [player.position[0] + direction[0], player.position[1] + direction[1]]
            if self.game_map[new_move[0]][new_move[1]] == ' ' or self.game_map[new_move[0]][new_move[1]] == 'p':
                # is a valid configuration
                new_game_map = deepcopy(self.game_map)

                if bomb_was_placed:
                    new_game_map[player.position[0]][player.position[1]] = 'b'
                else:
                    new_game_map[player.position[0]][player.position[1]] = ' '

                if self.game_map[new_move[0]][new_move[1]] == 'p':
                    player.no_protections += 1

                new_game_map[new_move[0]][new_move[1]] = str(player.player_symbol)


                if bomb_was_placed == False and player.bomb_activate == False:    # check if the bomb was placed in a previous turn
                    if player.bomb_position[0] == opponent.position[0] or player.bomb_position[1] == opponent.position[1]:
                        if player.bomb_position[0] != player.position[0] and player.bomb_position[1] != player.position[1]:
                            player.bomb_activate = True
                        else:
                            # even if the bomb can afect also the player, we will check if this move is in his favor:
                            # first we check if there is a wall between the bomb and the opponent
                            if opponent.position[0] == player.bomb_position[0]:
                                player.bomb_activate = True

                                start = opponent.position[1] if opponent.position[1] < player.bomb_position[1] else player.bomb_position[1]
                                finish = opponent.position[1] if start == player.bomb_position[1] else player.bomb_position[1]

                                for j in range(start + 1, finish):
                                    if new_game_map[opponent.position[0]][j] == '#':
                                        player.bomb_activate = False

                            elif opponent.position[1] == player.bomb_position[1]:
                                player.bomb_activate = True

                                start = opponent.position[0] if opponent.position[0] < player.bomb_position[0] else player.bomb_position[0]
                                finish = opponent.position[0] if start == player.bomb_position[0] else player.bomb_position[0]

                                for i in range(start + 1, finish):
                                    if new_game_map[i][opponent.position[1]] == '#':
                                        player.bomb_activate = False

                            # now we check if it is needless to put the bomb(if the bomb wasn't activate it means there is a wall between
                            # the opponent and the bomb) and if there is a wall between the bomb and the player
                            # if there is none(player is in range of explosion) we check if the player have more protections than the opponent
                            if player.bomb_activate == True:
                                if player.position[0] == player.bomb_position[0]:
                                    in_range = True

                                    start = player.position[1] if player.position[1] < player.bomb_position[1] else player.bomb_position[1]
                                    finish = player.bomb_position[1] if start == player.position[1] else player.position[1]

                                    for j in range(start + 1, finish):
                                        if new_game_map[player.position[0]][j] == '#':
                                            in_range = False

                                    if in_range and player.no_protections < opponent.no_protections:
                                        player.bomb_activate = False


                                elif player.position[1] == player.bomb_position[1]:
                                    in_range = True

                                    start = player.position[0] if player.position[0] < player.bomb_position[0] else player.bomb_position[0]
                                    finish = player.bomb_position[0] if start == player.position[0] else player.position[0]

                                    for i in range(start + 1, finish):
                                        if new_game_map[i][player.position[1]] == '#':
                                            in_range = False

                                    if in_range and player.no_protections < opponent.no_protections:
                                        player.bomb_activate = False
                
                if player == self.player1:
                    new_player = Player(new_move, player_s, player.bomb_activate, player.bomb_position, player.no_protections)
                    moves.append(GameConfiguration(new_player, self.player2, new_game_map))
                else:
                    new_player = Player(new_move, player_s, player.bomb_activate, player.bomb_position, player.no_protections)
                    moves.append(GameConfiguration(self.player1, new_player, new_game_map))
                
        return moves

    
    def opposite_player(self, player):
        if player == self.player1.player_symbol:
            return self.player2.player_symbol
        else:
            return self.player1.player_symbol
                

    def final(self):
        if self.player1.has_died(self.player2, self.game_map) and self.player2.has_died(self.player1, self.game_map):
            return 'Remiza'
        elif self.player1.has_died(self.player2, self.game_map):
            return self.player2.player_symbol
        elif self.player2.has_died(self.player1, self.game_map):
            return self.player1.player_symbol
        else:
            return False


    def heuristic(self, player_sym):
        player = self.player1 if self.player1 == player_sym else self.player2
        opponent = self.player1 if self.player2 == player else self.player1
        
        if opponent.bomb_position[0] == player.position[0]:
            start = opponent.bomb_position[1] if opponent.bomb_position[1] < player.position[1] else player.position[1]
            finish = opponent.bomb_position[1] if start == player.position[1] else player.position[1]

            for j in range(start + 1, finish):
                if self.game_map[player.position[0]][j] == '#':
                    return manhattan_distance(player.position, [player.position[0], j]) # player is not in the range of the explosion
       
            return (-2) * manhattan_distance(player.position, opponent.bomb_position) # player is in the range of the explosion

        elif opponent.bomb_position[1] == player.position[1]:
            start = opponent.bomb_position[0] if opponent.bomb_position[0] < player.position[0] else player.position[0]
            finish = opponent.bomb_position[0] if start == player.position[0] else player.position[0]

            for i in range(start + 1, finish):
                if self.game_map[i][player.position[1]] == '#':
                    return manhattan_distance(player.position, [i, player.position[1]])

            return (-2) * manhattan_distance(player.position, opponent.bomb_position)

        elif player.bomb_position[0] == player.position[0]:
            start = player.bomb_position[1] if player.bomb_position[1] < player.position[1] else player.position[1]
            finish = player.bomb_position[1] if start == player.position[1] else player.position[1]

            for j in range(start + 1, finish):
                if self.game_map[player.position[0]][j] == '#':
                    return manhattan_distance(player.position, [player.position[0], j]) # player is not in the range of the explosion
       
            return (-2) * manhattan_distance(player.position, player.bomb_position) # player is in the range of the explosion

        elif player.bomb_position[1] == player.position[1]:
            start = player.bomb_position[0] if player.bomb_position[0] < player.position[0] else player.position[0]
            finish = player.bomb_position[0] if start == player.position[0] else player.position[0]

            for i in range(start + 1, finish):
                if self.game_map[i][player.position[1]] == '#':
                    return manhattan_distance(player.position, [i, player.position[1]])

            return (-2) * manhattan_distance(player.position, player.bomb_position)

        else:
            # if there isn't a bomb placed, for the heuristic we will take into consideration two factors:
            #   - the need to get closer to opponent for placing a bomb or put him in a DANGEROUS ZONE
            #   - the need to collect protections as they can be an advantage over the opponent
            #  min(Manhattan_Distance(PMAX_pos, PMIN_pos), Manhattan_Distance(closest_protection_pos, PMAX_pos))
            dist_opponent = manhattan_distance(player.position, opponent.position)

            dist_item = INFINITY
            for item_pos in items_positions:
                dist_item = min(manhattan_distance(player.position, item_pos), dist_item)

            return min(0.1 * dist_opponent, 0.9 * dist_item)


    def heuristic_2(self, player_sym):
        player = self.player1 if self.player1 == player_sym else self.player2
        opponent = self.player1 if self.player2 == player else self.player1

        # if there is a bomb placed on the same row or column as the player we might be exposed:
        # -if is the opponent's bomb we will return a negative number, as the bomb can be detonated by the opponent after our turn
        # -if is the player's bomb will return a negative number; we are not in a situation as dangerous as the previous one because
        # the player can choose not to detonate the bomb if it isn't in its advantage
        if player.position[0] == opponent.bomb_position[0] or player.position[1] == opponent.bomb_position[1]:
            return (-3) * manhattan_distance(player.position, opponent.bomb_position)
        elif player.position[0] == player.bomb_position[0] or player.position[1] == player.bomb_position[1]:
            return (-1) * manhattan_distance(player.position, player.bomb_position)
        else:
            # if there isn't a bomb placed, for the heuristic we will take into consideration two factors:
            #   - the need to get closer to opponent for placing a bomb or put him in a DANGEROUS ZONE
            #   - the need to collect protections as they can be an advantage over the opponent
            #  min(Manhattan_Distance(PMAX_pos, PMIN_pos), Manhattan_Distance(closest_protection_pos, PMAX_pos))
            dist_opponent = manhattan_distance(player.position, opponent.position)

            dist_item = INFINITY
            for item_pos in items_positions:
                dist_item = min(manhattan_distance(player.position, item_pos), dist_item)

            return min(0.1 * dist_opponent, 0.9 * dist_item)



    def estimate_score(self, depth):
        game_winner = self.final()
        if game_winner == GameConfiguration.PMAX:
            return (99 + depth)
        elif game_winner == GameConfiguration.PMIN:
            return (-99 - depth)
        elif game_winner == 'Remiza':
            return 0
        else:
            # calculate the difference between MAX's chances of winning and MIN's chances of winning
            return self.heuristic(GameConfiguration.PMAX) - self.heuristic(GameConfiguration.PMIN)


    def __str__(self):
        return 'Player1: ' + str(self.player1.no_protections) + '\n' + 'Player2: ' + str(self.player2.no_protections) + '\n' + '\n'.join([' '.join(['{:}'.format(elem) for elem in row]) for row in self.game_map])
        


class State:
    """ The class that refers to a node in the search tree of the algorithm. 
        The attributes of the State class are those that do NOT change during the application of the algorithm.
    """
    MAX_DEPTH = None    # Represents the maximum level for which the algorithm is allowed to extend the search tree

    def __init__(self, game_configuration, current_player, depth, parent = None, score = -INFINITY):
        self.game_configuration = game_configuration
        self.current_player = current_player    # symbol of the current player
        self.depth = depth  # depth in the state tree (decreases by one unit from "father" to "son")

        # state score (if it is a final state, i.e the leaf of the tree will be calculated according to the rules established in the 
        # "estimate_score" method) or best "son" state score (for current player = (chances of winning for JMAX) - (chances of winning for JMIN))
        self.score = score

        # list of possible moves from the current state
        self.possible_moves = []

        # the best move from the list of possible moves for the current player
        self.chosen_state = None


    # Returns a list of State objects, representing all possible sons of the current "self" node in the search tree
    def state_possible_moves(self):
        moves = self.game_configuration.game_moves(self.current_player)
        opponent = self.game_configuration.opposite_player(self.current_player)

        state_moves = [State(move, opponent, self.depth - 1, parent = self) for move in moves]
        return state_moves

    # return the current player as Player object, knowing it symbol
    def get_player(self):
        return self.game_configuration.player1 if self.game_configuration.player1 == self.current_player else self.game_configuration.player2



def mini_max(state):
    # We check if we have reached a leaf of the tree, that is:
    # - if we expanded the tree to a maximum allowed depth
    # - or if we have reached a final game configuration
    if state.depth == 0 and state.game_configuration.final():
        # calculate score of the leaf 
        state.scor = state.game_configuration.estimate_score(state.MAX_DEPTH)
        return state

    # Otherwise, calculate all possible moves from the current state
    state.possible_moves = state.state_possible_moves()

    # I apply the minimax algorithm on all possible moves (thus calculating their subtrees)
    moves_score = [mini_max(move) for move in state.possible_moves]

    if state.current_player == GameConfiguration.JMAX:
        # If it is the MAX player's turn, I choose the son state with the maximum score
        state.chosen_state = max(moves_score, key = lambda x : x.score)
    else:
        # If it is the MAX player's turn, I choose the son state with the minimum score
        state.chosen_state = min(moves_score, key = lambda x : x.score)

    # update the score of the "father" = the score of the chosen "son"
    state.score = state.chosen_state.score
    return state



def alpha_beta(alpha, beta, state):
    # We check if we have reached a leaf of the tree, that is:
    # - if we expanded the tree to a maximum allowed depth
    # - or if we have reached a final game configuration
    if state.depth == 0 or state.game_configuration.final():
        # calculate score of the leaf
        state.score = state.game_configuration.estimate_score(state.MAX_DEPTH)
        return state

    # prune tree condition
    if alpha >= beta:
        return state    # is an invalid range, so I'm not processing it anymore
    
    # Calculate all possible moves from the current state
    state.possible_moves = state.state_possible_moves()

    if state.current_player == GameConfiguration.PMAX:
        current_score = float('-inf') 

        # for each MIN son 
        for move in state.possible_moves: 
            #calculate the score of the current on
            new_state = alpha_beta(alpha, beta, move)

            # Try to improve (increase) the score and alpha of the father 
            # MAX player tries to win or maximize his score, using the current son's score
            if current_score < new_state.score:
                state.chosen_state = new_state
                current_score = new_state.score

            if alpha < new_state.score:
                alpha = new_state.score
                if alpha >= beta:   # check the prunning condition
                    break   # the other MIN type sons do NOT extend anymore
    
    elif state.current_player == GameConfiguration.PMIN:
        current_score = float('inf')

        # for each MAX score
        for move in state.possible_moves:
            new_state = alpha_beta(alpha, beta, move)

            # Try to improve (decrease) the score
            # MIN player tries to minimize MAX score, using current son score
            if current_score > new_state.score:
                state.chosen_state = new_state
                current_score = new_state.score

            if beta > new_state.score:
                beta = new_state.score
                if alpha >= beta:   # check the prunning condition
                    break   # the other MAX type sons do NOT extend anymore
    
    # update the score of the "father" = the score of the chosen "son"
    if state.chosen_state != None:
        state.score = state.chosen_state.score

    return state


# defines the user moves
def user_move(state):
    global no_moves

    directions = [[-1,0], [0,-1], [1,0], [0,1]]
    player = state.get_player()
    game_map = deepcopy(state.game_configuration.game_map)
    bomb_was_placed = False

    while True:
        prompt_chose_move = "Press x keyboard first, if you want to place a bomb, otherwise you can move on another block.\n"
        key = validate_user_input(prompt=prompt_chose_move, type_=str, range_=['a', 's', 'd', 'w', 'x', 'q', 'Q'])
        

        if key == 'x':
            # user decided to place a bomb
            if player.bomb_position == [-1, -1]:
                player.bomb_position = player.position
                bomb_was_placed = True
            else:
                print("Ops! You have already placed a bomb.")
                prompt_msg_user = "Do you want to detonate it?\n(Y/N): "
                user_choice = validate_user_input(prompt=prompt_msg_user, type_=str, range_=['y', 'n', 'Y', 'N', 'q', 'Q'])
                if user_choice == 'y' or user_choice == 'Y':
                    player.bomb_activate = True
                    if display(state): # final state
                        print('\nGame is over after {} moves.'.format(no_moves))
                        exit()
                    game_map[player.bomb_position[0]][player.bomb_position[1]] = ' '
                    player.bomb_position = [-1, -1]
                    player.bomb_activate = False
                elif user_choice == 'q' or user_choice == 'Q':
                    score = state.game_configuration.estimate_score(state.depth)
                    print('Score: ', round(score * 10, 2))
                    print('\nGame is over after {} moves.'.format(no_moves))
                    exit()

            key = validate_user_input(prompt='Move: ', type_=str, range_=['a', 's', 'd', 'w', 'q', 'Q'])


        if key == 'q' or key == 'Q':
            score = state.game_configuration.estimate_score(state.depth)
            print('Score: ', round(score * 10, 2))
            print('\nGame is over after {} moves.'.format(no_moves))
            exit()


        if key == 'w':
            new_position = [player.position[0] + directions[0][0], player.position[1] + directions[0][1]]
        elif key == 'a':
            new_position = [player.position[0] + directions[1][0], player.position[1] + directions[1][1]]
        elif key == 's':
            new_position = [player.position[0] + directions[2][0], player.position[1] + directions[2][1]]
        else:
            new_position = [player.position[0] + directions[3][0], player.position[1] + directions[3][1]]

        if game_map[new_position[0]][new_position[1]] == ' ' or game_map[new_position[0]][new_position[1]] == 'p':
            if bomb_was_placed:
                game_map[player.position[0]][player.position[1]] = 'b'
            else:
                game_map[player.position[0]][player.position[1]] = ' '
            
            if game_map[new_position[0]][new_position[1]] == 'p':
                player.no_protections += 1

            game_map[new_position[0]][new_position[1]] = str(state.current_player)
            player.position = new_position

            # if there is a bomb placed in a precendent turn, after the player moves in another block, he can decide to denonate the bomb or not
            if bomb_was_placed == False and player.bomb_position != [-1, -1]:
                prompt_detonate_bomb = "Do you want to detonate your bomb now?\n(Y/N):"
                user_choice = validate_user_input(prompt=prompt_detonate_bomb, type_=str, range_=['y', 'n', 'Y', 'N', 'q', 'Q'])
                if user_choice == 'y' or user_choice == 'Y':
                    player.bomb_activate = True
                    if display(state): # final state
                        print('\nGame is over after {} moves.'.format(no_moves))
                        exit()
                    game_map[player.bomb_position[0]][player.bomb_position[1]] = ' '
                    player.bomb_position = [-1, -1]
                    player.bomb_activate = False
                elif user_choice == 'q'or user_choice == 'Q':
                    score = state.game_configuration.estimate_score(state.depth)
                    print('\nGame is over after {} moves.'.format(no_moves))
                    print('Score: ', round(score * 10, 2))
                    exit()

            if player == state.game_configuration.player1:
                new_game_sconfiguration = GameConfiguration(player, state.game_configuration.player2, game_map)
            else:
                new_game_sconfiguration = GameConfiguration(state.game_configuration.player1, player, game_map)

            return State(new_game_sconfiguration, GameConfiguration.PMIN, depth=State.MAX_DEPTH)

        else:
            print("You can't go in that direction! Please try again!")
            continue



# generic function to validate the user's input   
def validate_user_input(prompt, type_= None, min_= None, max_= None, range_=None):
    if min_ is not None and max_ is not None and min_ > max_:
        raise ValueError("min_ must be less than max_")
    
    user_input = input(prompt)
    while True:
        if type_ is not None:
            try:
                user_input = type_(user_input)
            except ValueError:
                print("Input type must be {}".format(type_.__name__))
                continue
        try:
            if min_ is not None and min_ > user_input:
                raise ValueError("Input must be greater than or equal to {}.".format(min_))
            elif max_ is not None and max_ < user_input:
                raise ValueError("Input must be less than or equal to {}.".format(max_))
            elif range_ is not None and user_input not in range_:
                if isinstance(range_, range):
                    template = "Input must be between {0.start} and {0.stop}."
                    raise ValueError(template.format(range_))
                else:
                    template = "Input must be {}."
                    if len(range_) == 1:
                        raise ValueError(template.format(*range_))
                    else:
                        raise ValueError(template.format(" or ".join((", ".join(map(str,
                                                                        range_[:-1])),
                                                                    str(range_[-1])))))
        except ValueError as err:
            print(err)
            user_input = input(prompt)
            continue     
        else:
            break

    return user_input



""" Variables and functions defined for displaying. """

RESET = "\033[0;0m"
BOLD  = "\033[;1m"
GREEN = "\033[0;32m"
RED   = "\033[1;31m"


def indent(text, amount, ch = ' '):
    padding = amount * ch
    return ''.join(padding + line for line in text.splitlines(True))


def instructions():
    sys.stdout.write(BOLD)
    print("Object:")
    sys.stdout.write(RESET)
    print("Gameplay involves strategically placing down bombs in order to kill your enemy and to be the last player in the game\n")
    sys.stdout.write(BOLD )
    print("Play:")
    sys.stdout.write(RESET)
    print("You can only move on 4 directions: UP, RIGHT, DOWN, LEFT. For this use [a, s, d, w] keyboards.")
    print("The game is over when one or both players die(in this case it is declared DRAW).")
    print("Each player can move only in a free space or in a place where there is a protection.")
    print("At each turn a player must move in a different block and optional, it can place a bomb before it moves. Each player can have only one bomb at a time(inactive).")
    print("Someone can die when a bomb is activated(by the opponent or by himself) and is in the range of the explosion.")
    print("It will survive the explosion only if it has a protection or the explosion is stopped by a block.\n")


def display(current_state):
    final = current_state.game_configuration.final()
    if final:
        if final == 'Remiza':
            print(final.center(100, ' '))
        else:
            if final == GameConfiguration.PMAX:
                sys.stdout.write(RED)
            else:
                sys.stdout.write(GREEN)
            cstr = "A castigat Player{}!".format(final)
            print(cstr.center(100, ' '))
            sys.stdout.write(RESET)
        return True
    else:
        return False


""" Variables and functions used for the graphic interface """

screen_width = 1500
screen_height = 800
block_width = 60
block_height = 65
black = (0,0,0)
white = (255,255,255)


def draw_game(display, current_game):

    player1_img = pygame.image.load('C:\\Users\\Dana\\Desktop\\IA\\player1.png')
    player1_img = pygame.transform.scale(player1_img, (block_width, block_height))

    # player2_img = pygame.image.load('C:\\Users\\Dana\\Desktop\\IA\\player2.png')
    # player2_img = pygame.transform.scale(player2_img, (block_width, block_height))

    # block_img = pygame.image.load('C:\\Users\\Dana\\Desktop\\IA\\block.png')
    # block_img = pygame.transform.scale(block_img, (block_width, block_height))

    # wall_img = pygame.image.load('C:\\Users\\Dana\\Desktop\\IA\\wall.png')
    # wall_img = pygame.transform.scale(wall_img, (block_width, block_height))
    
    # bomb_img = pygame.image.load('C:\\Users\\Dana\\Desktop\\IA\\bomb.png')
    # bomb_img = pygame.transform.scale(bomb_img, (block_width, block_height))

    # protection_img = pygame.image.load('C:\\Users\\Dana\\Desktop\\IA\\protection.png')
    # protection_img = pygame.transform.scale(protection_img, (block_width, block_height))

    drt = []

    for row in range(GameConfiguration.NO_ROWS):
        for col in range(GameConfiguration.NO_COLUMNS):
            window = pygame.Rect(col * (block_width + 1), row * (block_height + 1), block_width, block_height)
            drt.append(drt)
            pygame.draw.rect(display, white, window)
            
            if current_game.game_configuration.game_map[row][col] == '1':
                display.blit(player1_img, (col * block_width, row * block_height))
            # elif current_game.game_configuration.game_map[row][col] == '2':
            #     display.blit(player2_img, (col * block_width, row * block_height))
            # elif current_game.game_configuration.game_map[row][col] == ' ':
            #     display.blit(block_img, (col * block_width, row * block_height))
            # elif current_game.game_configuration.game_map[row][col] == '#':
            #     display.blit(wall_img, (col * block_width, row * block_height))
            # elif current_game.game_configuration.game_map[row][col] == 'p':
            #     display.blit(protection_img, (col * block_width, row * block_height))
            # elif current_game.game_configuration.game_map[row][col] == 'b':
            #     display.blit(bomb_img, (col * block_width, row * block_height))

    pygame.display.flip()
    return drt

""" END defining graphic interface """

def main():
    global no_moves
    first_time_display = True

    prompt_chosen_algorithm = "Choose algorithm (answer with 1 or 2):\n1.Minimax\n2.Alpha-Beta Prunning\nA: "
    chosen_algorithm = validate_user_input(prompt=prompt_chosen_algorithm, type_=str, range_=['1', '2'])

    GameConfiguration.PMIN = 2
    GameConfiguration.PMAX = 1

    player1 = Player(player1_position, 1)
    player2 = Player(player2_position, 2)

    EASY, MEDIUM, DIFFICULT = 5, 7, 10
    prompt_chosen_game_difficulty = "\nChose the difficulty of the game\nPress 1 for EASY, 2 for MEDIUM and 3 for DIFFICULT\nA: "
    chosen_difficulty = int(validate_user_input(prompt=prompt_chosen_game_difficulty, type_=str, range_=['1', '2', '3']))

    if chosen_difficulty == 1:
        State.MAX_DEPTH = EASY
    elif chosen_difficulty == 2:
        State.MAX_DEPTH = MEDIUM
    else:
        State.MAX_DEPTH = DIFFICULT

    game_configuration = GameConfiguration(player1, player2, default_table)

    current_state = State(game_configuration, GameConfiguration.PMAX, State.MAX_DEPTH)

    print("\nCurent map:\n")
    print(indent(str(game_configuration), 10))

    while True:
        if current_state.current_player == GameConfiguration.PMAX:
            # computer's turn
            start_time = int(round(time.time() * 1000))
            if chosen_algorithm == 1:
                updated_status = mini_max(current_state)
            else:
                updated_status = alpha_beta(-INFINITY, INFINITY, current_state)

            current_state = updated_status.chosen_state
            print("\nGame map after opponent moved:\n")
            print(indent(str(current_state.game_configuration), 10))

            finish_time = int(round(time.time() * 1000))
            print('\nOpponent took {} milliseconds to think.\n'.format(finish_time - start_time))

            # display the map if the status if the game is over
            if display(current_state):
                print('\nGame is over after {} moves.'.format(no_moves))
                break

            no_moves += 1
            
        else:
            # player's turn
            if first_time_display:
                sys.stdout.write(BOLD)
                prompt_msg = "Press h keyboard for instructions. Press anytime in your turn q keyboard to exit. Press c keyboard to continue.\n"
                user_choice_1 = validate_user_input(prompt = prompt_msg, type_=str, range_=['q', 'Q', 'h', 'H', 'C', 'c'])
                if user_choice_1 == 'q' or user_choice_1 == 'Q':
                    score = current_state.game_configuration.estimate_score(current_state.depth)
                    print('Score: ', round(score * 10, 2))
                elif user_choice_1 == 'h' or user_choice_1 == 'H':
                    instructions()

                first_time_display = False
                sys.stdout.write(RESET)

            start_time = int(round(time.time()))

            current_state = user_move(current_state)

            print("\nGame map after your move:\n")
            print(indent(str(current_state.game_configuration), 10))

            finish_time = int(round(time.time()))
            print('It took you {} seconds to take a decision.'.format(finish_time - start_time))


            if display(current_state):
                print('\nGame is over after {} moves.'.format(no_moves))
                break
            print("\nNow is opponent's turn.")

            current_state.current_player = GameConfiguration.PMAX

            no_moves +=1
    
   

if __name__ == "__main__":
    main()