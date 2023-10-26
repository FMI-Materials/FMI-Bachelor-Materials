import chess
import chess.engine

engine = chess.engine.SimpleEngine.popen_uci("stockfish/stockfish_mac")
#engine = chess.engine.SimpleEngine.popen_uci("../stockfish/stockfish_mac")

fin = open("donotopen/buffer.txt", "r")
#fin = open("buffer.txt", "r")
board_pos = fin.readline().strip().split()

board = chess.Board()
for mv in board_pos:
    if len(mv) == 4:
        board.push(chess.Move.from_uci(mv))
    elif len(mv) == 5 and mv != "moves":
        board.push(chess.Move.from_uci(mv))

result = engine.play(board, chess.engine.Limit(time = 0.1))

fin.close()
fout = open("donotopen/buffer.txt", "w")
#fout = open("buffer.txt", "w")
fout.write(str(result.move))
fout.close()


engine.quit()
