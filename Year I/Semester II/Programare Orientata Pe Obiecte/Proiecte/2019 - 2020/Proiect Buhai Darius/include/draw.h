#ifndef CHECKMATE_DRAW_H
#define CHECKMATE_DRAW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>

#include "../include/table.h"
#include "../include/materials.h"

#if defined(_WIN32)
    #define ScreenWidth 1100
    #define ScreenHeight 1100
#else
    #define ScreenWidth 1100
    #define ScreenHeight 1100
#endif

class Draw{
private:

    const double screenWidth = ScreenWidth;
    const double screenHeight = ScreenHeight;

    Table table;

    static Draw* instance_;

    bool cursorHand = false;

    bool darkMode = true;
    bool viewCredits = false;
    bool resetGameGulp = false;
    bool playAgainstStockFish = false;
    bool showBestMoveGulp = false;
    bool undoMoveGulp = false;
    bool playAgainstAi = false;

    Container<Button*> buttons;
    Container<Label*> labels;
    Container<ImageLabel*> images;

    void updateFrame(sf::RenderWindow*);
    void digestAction(sf::RenderWindow*, sf::Event);

    void init();
    void initComponents();
    Draw();

public:
    static Draw* getInstance();
    void startGame();
    friend std::ostream& operator<<(std::ostream& , const Draw&);
    friend Table;
};

#endif //CHECKMATE_DRAW_H
