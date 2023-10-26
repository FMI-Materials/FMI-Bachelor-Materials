#ifndef CHECKMATE_TABLE_H
#define CHECKMATE_TABLE_H

#include <SFML/Graphics.hpp>

#include <vector>

#include "utils.h"
#include "piece.h"
#include "rules.h"
#include "brain.h"

#include "../include/materials.h"

#if defined(_WIN32)
    #define ScreenWidth 1100
    #define ScreenHeight 1100
#else
    #define ScreenWidth 1100
    #define ScreenHeight 1100
#endif

class Table{
private:
    /** General settings */
    const double screenWidth = ScreenWidth;
    const double screenHeight = ScreenHeight;
    bool* darkMode{new bool(false)};

    /** Custom table sizes */
    const double padding = 10;
    const double borderWidth = 10;
    double indicatorSpacing = 70;

    Rules rules;
    Brain* brain;

    SizeType size;
    std::pair<int,int> position;
    std::pair<int, int> selectedSquare = {-1, -1};
    std::pair<int, int> selectedPieceCurrentLocation = {-1,-1};
    Piece* selectedPiece = nullptr;
    std::vector<std::pair<int, int>> futurePositions;

    bool mousePressing = false;
    bool *cursorHand = new bool(false);
    bool playAgainstAi = false;
    bool playAgainstStockFish = false;
    bool awaitNextMove = false;
    bool checkMate = false;
    bool staleMate = false;
    bool showingBestMove = false;
    int winnerPlayer = -1;

    Move bestMove;

    Timer timer1;
    Timer timer2;
    sf::Clock mousePressingTimeout;

    Container<Label*> labels;

    void resetFuturePositions();
    void resetSelectedPieceLocation();
    void resetSelectedSquare();
    void resetShowingBestMove();

    void updateCheckmateStatus(int);
    void updateBrainMove();

    void updateSelectedSquare(std::pair<int, int>);
    bool isInsideTable(std::pair<int,int>) const;
    void drawGrid(sf::RenderWindow*, SizeType, std::pair<int,int>);
    void drawOutline(sf::RenderWindow*, SizeType, std::pair<int,int>) const;
    void drawIndicators(sf::RenderWindow*, SizeType, std::pair<int,int>) const;

    std::pair<int, int> determineGridPosition(std::pair<int,int>) const;
public:
    Table();
    ~Table();

    void digestAction(sf::Event, sf::RenderWindow*);

    void updateFrame(sf::RenderWindow*);
    void drawPiece(sf::RenderWindow*, Piece*) const;

    void setSize(SizeType);
    void setPosition(std::pair<int,int>);
    void setDarkMode(bool*);
    void setCursorHand(bool*);

    void toggleTimers(bool = false, bool = false);

    void initComponents();

    bool getIsCheckMate() const;
    bool getIsStaleMate() const;
    int getWinnerPlayer() const;

    void resetGame();
    void undoMove();
    void togglePlayAgainstAi();
    bool isPlayingAgainstAi() const;
    void togglePlayAgainstStockfish();
    bool isPlayingAgainstStockfish() const;
    void showBestMove();
};

#endif //CHECKMATE_TABLE_H
