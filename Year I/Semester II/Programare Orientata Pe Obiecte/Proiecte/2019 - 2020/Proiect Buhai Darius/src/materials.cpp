#include <SFML/Graphics.hpp>

#include <utility>

#include "../include/utils.h"
#include "../include/materials.h"

#if defined(_WIN32)
    #define ScreenWidth 1100
    #define ScreenHeight 1100
#else
    #define ScreenWidth 1100
    #define ScreenHeight 1100
#endif

using namespace std;
using namespace sf;

void ImageLabel::draw(RenderWindow* window, bool darkMode){
    Texture piece_img;
    if(!piece_img.loadFromFile(this->image_path)) throw Exception("Error: Cannot load image");

    Sprite item;
    item.setScale(this->scale.first, this->scale.second);
    item.setTexture(piece_img);
    if(this->color!=Color::Transparent)
        item.setColor(this->color);
    item.setPosition(Vector2f(this->position.first, this->position.second));

    window->draw(item);
}

ImageLabel &ImageLabel::operator=(const std::string& _image_path){
    this->image_path = _image_path;
    return *this;
}

void Button::digestAction(Event event, RenderWindow* window){
    if(event.type==Event::MouseButtonPressed)
        if(Utils::mouseInsideLimits(event, this->x, this->y)){
            *this->pressed = !*this->pressed;
            *this->cursorHand = true;
        }
    if(event.type==Event::MouseMoved){
        if(Utils::mouseInsideLimits({event.mouseMove.x, event.mouseMove.y}, this->x, this->y)){
            *this->cursorHand = true;
            hovering = true;
        }
        else hovering = false;
    }
}

void Button::draw(RenderWindow* window, bool darkMode){
    string t = this->text;
    if(*this->pressed && !this->disabledText.empty())
        t = this->disabledText;

    const int elevation = !hovering ? 10 : 0;
    const int padding_top = 10;
    /// Button fill
    Utils::drawBox(window, x, {y.first+padding_top+elevation,y.second+elevation}, darkMode ? Color(80,102,47, 100) : Color(105,127,72,100), darkMode ? Color(80,102,47) : Color(105,127,72));
    /// Bottom elevated border
    if(elevation>0)
        Utils::drawBox(window, {x.first-5, x.second+5}, {y.second+elevation-15, y.second+2*elevation-15}, Color::Transparent, Color(0,0,0,100));
    /// Text
    Utils::drawText(window, t, Color::White, {x.first,1100-(!hovering ? y.first+elevation : y.first)});
}

Button &Button::operator=(const std::pair<std::string, std::string>& _texts) {
    this->text = _texts.first;
    this->disabledText = _texts.second;
    return *this;
}

void Label::draw(RenderWindow* window, bool darkMode){
    Utils::drawText(window, text, darkMode ? oppositeColor : color, position, size);
}

void Label::setColor(Color _color, Color _oppositeColor) {
    this->color = _color;
    this->oppositeColor = _oppositeColor;
}

Label &Label::operator=(std::string _text) {
    this->text = std::move(_text);
    return *this;
}
