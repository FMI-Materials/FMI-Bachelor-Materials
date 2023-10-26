#ifndef PIECES_H_INCLUDED
#define PIECES_H_INCLUDED

#include <vector>
#include <deque>
#include <string>

#include "piece.h"
#include "utils.h"

/**
 * This is a subclass of rules! do not instantiate
 */

class Pieces{
private:
    void resizeBoard();
    void initPieces();
    void updateBoard();
protected:
    Piece* nullPiece;
    std::vector<std::vector<std::vector<Piece*>> >  board;
    std::deque<Move> history;
    std::vector<Piece*> pieces;
    int currentPlayer = 0;
public:
    Pieces();
    ~Pieces();

    std::vector<Piece* > getPieces();
    Piece* getPiece(int, std::pair<int, int>);
    Piece* operator[](std::pair<int, int>);
    std::vector<std::vector<Piece*>> operator[](int);
    void setPieces(const std::vector<Piece*>&);
    std::string parseHistory();
    void movePiece(Piece*, std::pair<int, int>, bool = false);
    void movePiece(std::pair<int, int>, std::pair<int, int>);

    int getCurrentPlayer();
    void setCurrentPlayer(int);
    void switchPlayer();

    void resetGame();
    void undoMove();
    void showGame();
    friend std::ostream& operator<<(std::ostream& , const Pieces&);
};


#endif // PIECES_H_INCLUDED
