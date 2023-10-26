#ifndef CHECKMATE_MATERIALS_H
#define CHECKMATE_MATERIALS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "../include/utils.h"

class ImageLabel{
    std::pair<int, int> position;
    std::string image_path;
    std::pair<double, double> scale;
    sf::Color color;
public:
    ImageLabel(std::pair<int,int> _position, std::string _image_path, std::pair<double, double> _scale = {1,1}, sf::Color _color = sf::Color::Transparent): position(_position), image_path(_image_path), scale(_scale), color(_color){}

    void draw(sf::RenderWindow*, bool = false);

    ImageLabel &operator=(const std::string&);
};

class Button{
    std::pair<int,int> x, y;
    std::string text, disabledText = "";
    bool* pressed;
    bool* cursorHand = new bool(false);
    bool hovering;
public:
    Button(std::pair<int, int> _x, std::pair<int, int> _y, bool* _pressed, bool* _cursorHand, std::string _text, std::string _disabledText = ""): x(_x), y(_y), pressed(_pressed), text(_text), disabledText(_disabledText), hovering(false), cursorHand(_cursorHand){}

    void draw(sf::RenderWindow*, bool = false);
    void digestAction(sf::Event, sf::RenderWindow*);

    Button &operator=(const std::pair<std::string, std::string>&);
};

class Label{
    std::pair<int, int> position;
    std::string text;
    sf::Color color, oppositeColor;
    int size;
public:
    Label(std::pair<int, int> _position, std::string _text, int _size = 40, sf::Color _color = sf::Color::Black, sf::Color _oppositeColor = sf::Color::White): position(_position), text(_text), size(_size), color(_color), oppositeColor(_oppositeColor){}

    void draw(sf::RenderWindow*, bool = false);
    void setColor(sf::Color = sf::Color::Black, sf::Color = sf::Color::White);

    Label &operator=(std::string);
};

template <class T>
class Container{
    std::vector<std::pair<std::string, T>> childs;
    bool* darkMode = new bool(false);
    //bool* auxDarkMode;
    double screenWidth, screenHeight;
public:
    Container(){
        //auxDarkMode = darkMode;
    }

    ~Container(){
        delete darkMode;
        for(auto child: childs)
            delete (&child)->second;
        childs.clear();
    }

    void draw(sf::RenderWindow * window, std::string category = "") {
        for(auto child: this->childs)
            if(category=="" || child.first=="default" || child.first==category)
                child.second->draw(window, *this->darkMode);
    }

    void digestAction(sf::Event event, sf::RenderWindow * window, std::string category = "") {
        for(auto child: this->childs)
            if(category=="" || child.first=="default" || child.first==category)
                child.second->digestAction(event, window);
    }

    void setDarkMode(bool* _darkMode){
        //delete this->darkMode;
        *(this-> darkMode) = *_darkMode;
    }

    std::vector<T> operator[](std::string category){
        std::vector<T> res;
        for(auto child: childs)
            if(child.first==category)
                res.push_back(child.second);
        return res;
    }

    Container<T>* operator+(T to_append){
        childs.push_back({"default", to_append});
        return this;
    }

    Container<T>* operator+(std::pair<std::string, T> to_append){
        childs.push_back(to_append);
        return this;
    }

    Container<T>* operator+=(T to_append){
        return *this + to_append;
    }

    Container<T>* operator+=(std::pair<std::string, T> to_append){
        return *this + to_append;
    }
};

#endif //CHECKMATE_MATERIALS_H
