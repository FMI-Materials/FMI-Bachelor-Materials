#ifndef CHECKMATE_UTILS_H
#define CHECKMATE_UTILS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <exception>

#include "piece.h"
#include "exception.h"

#if defined(_WIN32)
    #define ScreenWidth 1100
    #define ScreenHeight 1100
#else
    #define ScreenWidth 1100
    #define ScreenHeight 1100
#endif

struct SizeType{
    double width, height;
    SizeType(double width = 0, double height = 0){
        this->width = width;
        this->height = height;
    }
};

struct Evaluation{
    int nr_pieces;
    int eval;
};

struct Move{
    Piece *piece = nullptr;
    Piece *deletedPiece = nullptr;
    Piece *updatedPiece = nullptr;
    std::pair<int, int> from, to;

    Move(Piece* p, std::pair<int, int> f, std::pair<int, int> t, Piece *dp = nullptr){
        this->piece = p;
        this->from = f;
        this->to = t;
        this->deletedPiece = dp;
    }
    Move(Piece* p, std::pair<int, int> t){
        this->piece = p;
        this->to = t;
    }
    Move(){
        piece = nullptr;
    }
};

class Utils{
public:
    static bool mouseInsideLimits(std::pair<int, int> location, std::pair<int, int> x, std::pair<int,int> y){
        y.first = ScreenHeight - y.first;
        y.second = ScreenHeight - y.second;
        return (location.first > x.first && location.first < x.second) &&
               (location.second > y.first && location.second < y.second);
    }

    static bool mouseInsideLimits(sf::Event event, std::pair<int, int> x, std::pair<int,int> y){
        return mouseInsideLimits({event.mouseButton.x,event.mouseButton.y}, x, y);
    }

    static void drawText(sf::RenderWindow* window, std::string title, sf::Color color, std::pair<int, int> position, int size = 40){
        sf::Text text = sf::Text();
        text.setString(title);
        sf::Font font;
        if (!font.loadFromFile("resources/sansation.ttf"))
            throw Exception("Error: Cannot load font!");
        text.setFont(font);
        text.setCharacterSize(size);
        text.setFillColor(color);
        text.setPosition(position.first, position.second);
        window->draw(text);
    }

    static void drawBox(sf::RenderWindow* window, std::pair<int, int> x, std::pair<int, int> y, sf::Color borderColor = sf::Color::Black, sf::Color backgroundColor = sf::Color::Transparent){
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(x.second-x.first, y.second-y.first));
        rectangle.setOutlineColor(borderColor);
        rectangle.setOutlineThickness(5);
        rectangle.setPosition(x.first, ScreenHeight-y.second);
        rectangle.setFillColor(backgroundColor);
        window->draw(rectangle);
    }
};

class Timer {
private:
    sf::Clock mC;
    float runTime;
    bool bPaused;
public:

    Timer() {
        bPaused = false;
        runTime = 0;
        mC.restart();
    }

    void Reset() {
        mC.restart();
        runTime = 0;
        bPaused = false;
    }

    void Start() {
        if (bPaused) {
            mC.restart();
        }
        bPaused = false;
    }

    void Pause() {
        if (!bPaused) {
            runTime += mC.getElapsedTime().asSeconds();
        }
        bPaused = true;
    }

    float GetElapsedSeconds() {
        if (!bPaused) {
            return runTime + mC.getElapsedTime().asSeconds();
        }
        return runTime;
    }
};

#endif //CHECKMATE_UTILS_H
