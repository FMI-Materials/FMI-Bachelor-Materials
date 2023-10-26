#ifndef RULES_H_INCLUDED
#define RULES_H_INCLUDED

#include <string>
#include <vector>

#include "piece.h"
#include "pieces.h"

/**
 *
to do -
a function that gets you a list of location that your piece can attack
a function that checks if you are in check based on the up function
a function that determines where can you move a piece based on the upper functions
a function that gets a list of all possible moves for you
*/

class Rules: public Pieces{
public:
    inline void saveBoard(Piece* [2][8][8]);
    inline void getBoard(Piece* [2][8][8]);
    void updateCurrentBoard(std::vector<std::vector<std::vector<Piece*>> >&);
    Rules();
    ~Rules();
    std::vector <std::pair<int, int>> canAttackPos(Piece*,std::pair<int,int>);
    std::vector <std::pair<int, int>> canProtectPos(Piece*);
    bool isInCheck(int);
    std::vector<std::pair<int, int>> getFuturePositions(Piece*, bool = true);
    std::vector<std::pair<int, int>> getFuturePositions(Piece*, std::pair<int, int>, bool = true );
    std::vector<std::pair<int, int>> getProtectedPositions(Piece*);
    std::vector<std::pair<int, int>> getFuturePawn(Piece*);
    std::vector<std::pair<int, int>> canCastle(Piece*);

    bool isCheckMate(int);
    void getAttackedPositions(bool [8][8], int);

};

#endif
