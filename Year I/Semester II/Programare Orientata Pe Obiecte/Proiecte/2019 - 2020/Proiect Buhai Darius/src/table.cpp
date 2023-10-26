#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <utility>

#include "../include/piece.h"
#include "../include/table.h"
#include "../include/exception.h"

#if defined(_WIN32)
    #include "pieces.cpp"
#endif

using namespace std;
using namespace sf;

Table::Table(){
    brain = new Brain(&rules, &playAgainstStockFish);
}

Table::~Table(){
    delete brain;
    delete darkMode;
    delete cursorHand;
};

void Table::initComponents(){
    labels.setDarkMode(this->darkMode);

    labels += {"timer", new Label({screenWidth - 135,400}, "00:00", 43)};
    labels += {"timer", new Label({screenWidth - 135,480}, "00:00", 43)};
}

/** Setters */
void Table::setCursorHand(bool* _cursorHand){
    //delete cursorHand;
    *cursorHand = std::move(*_cursorHand);
}

void Table::setDarkMode(bool* _darkMode){
    //delete darkMode;
    *darkMode = std::move(*_darkMode);
}

void Table::setSize(SizeType s) {
    this->size = s;
}

void Table::setPosition(std::pair<int,int> p) {
    this->position = p;
}

void Table::togglePlayAgainstAi(){
    playAgainstAi = !playAgainstAi;
}

bool Table::isPlayingAgainstAi() const{
    return playAgainstAi;
}

void Table::togglePlayAgainstStockfish(){
    playAgainstStockFish = !playAgainstStockFish;
}

bool Table::isPlayingAgainstStockfish() const{
    return playAgainstStockFish;
}

bool Table::getIsCheckMate() const {
    return checkMate;
}

bool Table::getIsStaleMate() const{
    return staleMate;
}
int Table::getWinnerPlayer() const {
    return winnerPlayer;
}

/** Resseters */

void Table::resetFuturePositions(){
    this->futurePositions.clear();
}

void Table::resetSelectedSquare(){
    this->selectedSquare = {-1,-1};
}

void Table::resetSelectedPieceLocation(){
    this->selectedPieceCurrentLocation = {-1, -1};
}

void Table::resetShowingBestMove(){
    this->showingBestMove = false;
}

/** Update checkmate or stalemate status */
void Table::updateCheckmateStatus(int player){
    if(rules.isCheckMate(player)){
        if(rules.isInCheck(player)){
            winnerPlayer = !player;
            resetSelectedSquare();
            resetFuturePositions();
            checkMate = true;
        }
        else{
            resetSelectedSquare();
            resetFuturePositions();
            staleMate = true;
        }
    }
    if(checkMate || staleMate){
        timer1.Pause();
        timer2.Pause();
    }
}

/** Called on each frame */
void Table::updateBrainMove(){
    if(!(checkMate || staleMate) && rules.getCurrentPlayer()==1 && playAgainstAi && !awaitNextMove){
        Move m = brain->determineBestMove();
        if(m.piece != nullptr && m.piece->getType() != "Null" && m.piece->isInTable()){
            rules.movePiece(m.piece, m.to);
            awaitNextMove = true;
            updateCheckmateStatus(!m.piece->getPlayer());
        }
    }
}

/** Content generators */
void Table::updateFrame(RenderWindow *window) {

    this->updateBrainMove();

    drawIndicators(window, size, position);
    drawOutline(window, SizeType(size.width-indicatorSpacing, size.height-indicatorSpacing), {position.first+indicatorSpacing, position.second});
    drawGrid(window, SizeType(size.width-2*padding-indicatorSpacing, size.height-2*padding-indicatorSpacing), std::pair<int,int>(position.first + indicatorSpacing + padding, position.second + padding));

    bool containsSelectedPiece = false;
    for(auto piece : rules.getPieces())
        if(piece!=selectedPiece) drawPiece(window, piece);
        else containsSelectedPiece = true;

    /** Draw the selected piece at the end, to be above */
    awaitNextMove = false;
    if(selectedPiece != nullptr && selectedPiece->getType() != "Null" && containsSelectedPiece)
        drawPiece(window, selectedPiece);

    /** Draw timers */
    int mins1 = static_cast<int>(timer1.GetElapsedSeconds())/60;
    int secs1 = static_cast<int>(timer1.GetElapsedSeconds())-mins1*60;

    int mins2 = static_cast<int>(timer2.GetElapsedSeconds())/60;
    int secs2 = static_cast<int>(timer2.GetElapsedSeconds())-mins2*60;

    if(!playAgainstAi) *labels["timer"][0] = (29-mins1<10 ? "0" : "")+to_string(29-mins1)+":"+(59-secs1<10 ? "0" : "")+to_string(59-secs1);
    else *labels["timer"][0] = "";
    *labels["timer"][1] = (29-mins2<10 ? "0" : "")+to_string(29-mins2)+":"+(59-secs2<10 ? "0" : "")+to_string(59-secs2);

    labels["timer"][!rules.getCurrentPlayer()]->setColor(Color(80,102,47), Color(105,127,72));
    labels["timer"][rules.getCurrentPlayer()]->setColor(Color::Black, Color::White);

    labels.draw(window, "timer");
}

void Table::drawIndicators(RenderWindow *window, SizeType s, std::pair<int,int> p) const{

    double indicatorHeight = (s.height-indicatorSpacing) / 8;
    double indicatorWidth = (s.width-indicatorSpacing) / 8;

    for(int i=0;i<8;i++){
        Text l;
        Font font;
        if (!font.loadFromFile("resources/sansation.ttf")) throw Exception("Error: Cannot load font!");
        l.setString(string(1, '1'+(7-i)));
        l.setFont(font);
        l.setCharacterSize(40);

        if(i%2) l.setFillColor(*darkMode ? Color(100,122,67) : Color(125,147,92));
        else l.setFillColor(*darkMode ? Color(210,210,186) : Color(145,145,121));

        l.setPosition(p.first + indicatorSpacing / 2 - 10, p.second +indicatorHeight*i + indicatorHeight/2 -10);
        window->draw(l);
    }
    for(int j=0;j<8;j++){
        Text l;
        Font font;
        if (!font.loadFromFile("resources/sansation.ttf")) throw Exception("Error: Cannot load font!");
        l.setString(string(1, 'A'+j));
        l.setFont(font);
        l.setCharacterSize(40);

        if(!(j%2)) l.setFillColor(*darkMode ? Color(100,122,67) : Color(125,147,92));
        else l.setFillColor(*darkMode ? Color(210,210,186) : Color(145,145,121));

        l.setPosition(p.first + indicatorWidth * j + indicatorSpacing + indicatorWidth / 2 - 20, s.height - indicatorHeight / 2 + 10);
        window->draw(l);
    }
}

void Table::drawOutline(RenderWindow *window, SizeType s, std::pair<int,int> p) const{
    RectangleShape fill(Vector2f(s.width - 2*borderWidth, s.height - 2*borderWidth));
    fill.setOutlineThickness((float)borderWidth);
    fill.setOutlineColor(*darkMode ? Color(80,102,47) : Color(105,127,72));
    fill.setPosition(static_cast<float>(p.first + borderWidth), static_cast<float>(p.second + borderWidth));
    window->draw(fill);
}

void Table::drawGrid(RenderWindow *window, SizeType s, std::pair<int,int> p){
    double squareWidth = (s.width) / 8;
    double squareHeight = (s.height) / 8;

    pair<int,int> hoveringSquare = {-1,-1};

    if(mousePressing){
        try{
            hoveringSquare = determineGridPosition(selectedPieceCurrentLocation);
        } catch (Exception &e) {
            //std::cerr<<e.what()<<'\n';
        }
    }

    for(int i=0;i<8;++i)
        for(int j=0;j<8;++j){
            bool oddSquare = (i+j)%2 != 0;
            RectangleShape square;
            square.setSize(Vector2f(squareWidth, squareHeight));
            square.setPosition(static_cast<float>(p.first +squareWidth*i), static_cast<float>(p.second + squareHeight*j));

            if(oddSquare) square.setFillColor(*darkMode ? Color(100,122,67) : Color(125,147,92));
            else square.setFillColor(*darkMode ? Color(210,210,186) : Color(235,235,211));

            pair<int, int> current_pos = {i, j};
            if(selectedSquare==current_pos) {
                square.setFillColor(oddSquare ? Color(189, 202, 83) : Color(247, 247, 139));
            }

            window->draw(square);

            if(find(futurePositions.begin(), futurePositions.end(), current_pos)!=futurePositions.end()){
                if(rules[current_pos]->getType() != "Null" && rules[selectedSquare]->getType() != "Null" && rules[current_pos]->getPlayer()!=rules[selectedSquare]->getPlayer()){
                    RectangleShape insideRectangle;
                    insideRectangle.setSize(Vector2f(squareWidth, squareHeight));
                    insideRectangle.setPosition(static_cast<float>(p.first +squareWidth*i), static_cast<float>(p.second + squareHeight*j));
                    insideRectangle.setFillColor(Color(178,65,55));
                    window->draw(insideRectangle);
                }else{
                    CircleShape insideCircle;
                    insideCircle.setPosition(static_cast<float>(p.first +squareWidth*i)+squareWidth/2-20, static_cast<float>(p.second + squareHeight*j)+squareHeight/2-20);
                    insideCircle.setRadius(20);
                    insideCircle.setFillColor(*darkMode ? Color(255,255,255) : Color(50,50,50));
                    window->draw(insideCircle);
                }
            }

            if (showingBestMove && current_pos==bestMove.to){
                CircleShape insideCircle;
                insideCircle.setPosition(static_cast<float>(p.first +squareWidth*i)+squareWidth/2-20, static_cast<float>(p.second + squareHeight*j)+squareHeight/2-20);
                insideCircle.setRadius(20);
                insideCircle.setFillColor(Color(207,90,38));
                window->draw(insideCircle);
            }

            if(hoveringSquare.first==i && hoveringSquare.second==j){
                RectangleShape insideRectangle;
                insideRectangle.setFillColor(Color::Transparent);
                insideRectangle.setOutlineColor(darkMode ? Color::White : Color::Black);
                insideRectangle.setOutlineThickness(4);
                insideRectangle.setSize(Vector2f(squareWidth-8, squareHeight-8));
                insideRectangle.setPosition(square.getPosition().x+4, square.getPosition().y+4);
                window->draw(insideRectangle);
            }
        }
}

bool Table::isInsideTable(std::pair<int,int> pos) const{
    SizeType s(size.width-2*padding-indicatorSpacing, size.height-2*padding-indicatorSpacing);
    std::pair<int,int> p(position.first + indicatorSpacing + padding, position.second + padding);
    return pos.first>=p.first && pos.first<=p.first+s.width && pos.second>=p.second && pos.second <= p.second + s.height;
}

pair<int, int> Table::determineGridPosition(std::pair<int,int> pos) const{
    pair<int, int> r(0,0);

    SizeType s(size.width-2*padding-indicatorSpacing, size.height-2*padding-indicatorSpacing);
    std::pair<int,int> p(position.first + indicatorSpacing + padding, position.second + padding);

    if(isInsideTable(pos)){
        r.first = (int) (pos.first - p.first) / (s.width/8);
        r.second = (int) (pos.second - p.second) / (s.height/8);
    }else{
        throw Exception("Warning: Pressed outside the table");
    }

    return r;
}

void Table::drawPiece(RenderWindow* window, Piece* piece) const{

    SizeType s(this->size.width - this->borderWidth - this->indicatorSpacing, this->size.height - this->borderWidth - this->indicatorSpacing);
    std::pair<int,int> p = std::pair<int,int>(this->position.first + this->indicatorSpacing + piece->getPos().first * (s.width/8), this->position.second + piece->getPos().second * (s.height/8));

    /** If the piece is selected with the mouse */
    if(piece==selectedPiece && selectedPieceCurrentLocation.first!=-1 && selectedPieceCurrentLocation.second!=-1)
        p = std::pair<int,int>(selectedPieceCurrentLocation.first - 50, selectedPieceCurrentLocation.second - 40);

    Texture piece_img;

    pair<double, double> origin = {-110,-50}, scale = {.3,.3};
    if (!piece_img.loadFromFile(piece->getImage())) throw Exception("Error: Cannot load image!");

    Sprite item;
    item.setScale(scale.first, scale.second);
    item.setOrigin(origin.first, origin.second);
    item.setTexture(piece_img);
    item.setPosition(Vector2f(p.first, p.second));

    window->draw(item);
}

/** Action digesters */
void Table::updateSelectedSquare(pair<int, int> new_position){
    if(!(new_position.first>=0 && new_position.first<8 && new_position.second>=0 && new_position.second<8)) return;
    this->selectedSquare = new_position;
    Piece* current = rules[new_position];
    resetShowingBestMove();
    if(find(futurePositions.begin(), futurePositions.end(), new_position)!=futurePositions.end()){
        rules.movePiece(selectedPiece, new_position);
        awaitNextMove = true;
        resetFuturePositions();
        resetSelectedSquare();
        updateCheckmateStatus(!selectedPiece->getPlayer());
        return;
    }
    resetFuturePositions();
    selectedPiece = current;
    if(current != nullptr){
        try{
            vector<pair<int, int>> _futurePositions = rules.getFuturePositions(current);
            this->futurePositions = _futurePositions;
        }catch (int e){
            cout<<"An error occurred trying to find future positions!";
        }
    }
}

void Table::digestAction(Event event, sf::RenderWindow* window){

    /** If is in drag and drop */
    if(mousePressing)
        *cursorHand = true;

    if(event.type==Event::MouseButtonPressed && event.mouseButton.button==Mouse::Left){
        this->resetSelectedPieceLocation();
        try{
            if(!checkMate && !staleMate){
                pair<int, int> grid_position = this->determineGridPosition(std::pair<int,int>(event.mouseButton.x, event.mouseButton.y));
                if(grid_position==this->selectedSquare){
                    /// Deprecated for drag&drop to work better
                    //resetFuturePositions();
                    //resetSelectedSquare();
                }else{
                    updateSelectedSquare(grid_position);
                }
            }
        }catch (Exception &e){
            //std::cerr<<e.what()<<'\n';
        }
        if(!mousePressing)
            mousePressingTimeout.restart();
        mousePressing = true;
    }
    if(event.type==Event::MouseButtonReleased){
        try{
            pair<int, int> grid_position = this->determineGridPosition(std::pair<int,int>(selectedPieceCurrentLocation.first, selectedPieceCurrentLocation.second));
            updateSelectedSquare(grid_position);
        } catch (Exception &e) {
            //std::cerr<<e.what()<<'\n';
        }
        mousePressing = false;
        resetSelectedPieceLocation();
    }
    if(mousePressing && mousePressingTimeout.getElapsedTime().asMilliseconds()>100){
        if(selectedPiece->getType() != "Null" && selectedPiece->getPlayer()==rules.getCurrentPlayer() && isInsideTable({event.mouseMove.x, event.mouseMove.y}))
            selectedPieceCurrentLocation = {Mouse::getPosition(*window).x,Mouse::getPosition(*window).y};
    }
    if(event.type==Event::KeyPressed){
        if(selectedSquare.first==-1 || selectedSquare.second==-1){
            if(rules.getCurrentPlayer()==1) selectedSquare = {3,1};
            else selectedSquare = {3,6};
        }
        if(event.key.code==Keyboard::Right)
            updateSelectedSquare({selectedSquare.first+1, selectedSquare.second});
        else if(event.key.code==Keyboard::Left)
            updateSelectedSquare({selectedSquare.first-1, selectedSquare.second});
        else if(event.key.code==Keyboard::Up)
            updateSelectedSquare({selectedSquare.first, selectedSquare.second-1});
        else if(event.key.code==Keyboard::Down)
            updateSelectedSquare({selectedSquare.first, selectedSquare.second+1});
    }


    /** Update timers */
    if(!checkMate && !staleMate)
        toggleTimers();
}

void Table::toggleTimers(bool pause, bool reset){
    if(pause){
        timer1.Pause();
        timer2.Pause();
    }else{
        if(rules.getCurrentPlayer()==0){
            timer1.Pause();
            timer2.Start();
        }else{
            timer2.Pause();
            timer1.Start();
        }
    }
    if(reset){
        timer1.Reset();
        timer2.Reset();
    }
}

/** Button actions */
void Table::resetGame() {
    checkMate = false;
    staleMate = false;
    rules.resetGame();
    brain->restartGame();
    resetSelectedSquare();
    resetShowingBestMove();
    resetFuturePositions();
    selectedPiece = rules.getPiece(0, {6, 6});
    /** Reset and start timers */
    toggleTimers(false, true);
}

void Table::undoMove() {
    checkMate = false;
    staleMate = false;
    if(playAgainstAi && rules.getCurrentPlayer()==0)
        rules.undoMove();
    rules.undoMove();
    resetSelectedSquare();
    resetFuturePositions();
    resetShowingBestMove();
}

void Table::showBestMove() {
    bestMove = brain->determineStockFishBestMove(rules.getCurrentPlayer());
    if(bestMove.piece!=NULL){
        cout<<bestMove.piece->getType()[0] << char(bestMove.from.first +97) << 8 - bestMove.from.second << '\n';
        cout<<bestMove.piece->getType()[0] << char(bestMove.to.first +97) << 8 - bestMove.to.second << '\n';
        resetSelectedPieceLocation();
        resetFuturePositions();
        resetSelectedSquare();
        this->selectedSquare = bestMove.piece->getPos();
        this->selectedPiece = bestMove.piece;
        this->futurePositions = rules.getFuturePositions(bestMove.piece);
        this->showingBestMove = true;
    }
}
