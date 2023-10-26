#ifndef CHECKMATE_BRAIN_H
#define CHECKMATE_BRAIN_H

#include <map>

#include "rules.h"
#include "piece.h"

class Brain : public Rules{
private:
    Rules* rules;
    bool *playAgainstStockFish = new bool(false);
    int moves = 0;

    std::map<std::string, std::vector<std::vector<int>>>  evaluation;
    std::vector<std::vector<std::vector<Piece*>>>  boardBrain;

    static int getPointsEvaluation(Piece*);
    int getEvaluation(Piece*, std::pair<int,int>, int = 1);
    std::vector<Move>lastBrainMoves;
public:
    Brain(Rules*, bool*);

    void initializeEvaluation();

    Evaluation evalAttacked(Piece*,std::pair<int,int>);
    Evaluation evalProtected(Piece*,std::pair<int,int>);

    bool isOkToMove(Piece*,std::pair<int,int>);
    bool canCheck(Piece*,std::pair<int,int>);
    bool pieceIsAttacked(Piece*,std::pair<int,int>);

    bool checkLast3Moves(Move);
    bool checkLast3Moves(Piece*);

    Move determineBrainBestMove(int = 1);
    Move determineStockFishBestMove(int = 1);

    Move determineBestMove(int = 1);

    void restartGame();

    friend std::ostream& operator<<(std::ostream& , const Brain&);
    ~Brain();
};

#endif //CHECKMATE_BRAIN_H
