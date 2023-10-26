#include <vector>
#include <utility>

#include "../include/piece.h"
#include "../include/table.h"


std::ostream& operator<<(std::ostream& out, const Piece& ob)
{
    out<<"Piesa este de tipul: " << " " << (ob.player ? "alb" : "negru") << '\n';
    out<<"Se afla la pozitia: " << ob.pos.first << " " << ob.pos.second<<'\n';
    out<< (ob.hasMoved ? "Nu se afla pe pozitia initiala\n" : "Se afla pe pozitia initiala\n");
    return out;
}



// ------------- piece methods ----------------
Piece::Piece(std::pair<int, int> pos, int player) : pos(pos), hasMoved(false), player(player) {}
Piece::Piece() : pos({0,0}), hasMoved(false), player(0) {}

std::vector<std::vector<std::pair<int, int>> >  Piece::path(std :: pair <int,int>){
    return std::vector<std::vector<std::pair<int,int>>>(0);
}

void Piece::TemplateMethod()
{
    this->path(this->getPos());
}

void Piece_Code(Piece *piece_)
{
    piece_->TemplateMethod();
}

void Piece::move(std::pair<int, int> position){
    hasMoved = true;
    pos = position;
}

std::pair<int,int> Piece::getPos(){
    return this->pos;
}

std::pair<int,int> Piece::getPosCastleShort(){
    pos.first += 1;
    return this->pos;
}

std::pair<int,int> Piece::getPosCastleLong(){
    pos.first -= 1;
    return this->pos;
}

int Piece::getPlayer(){
    return this->player;
}

bool Piece::getHasMoved(){
    return hasMoved;
}

void Piece::resetHasMoved() {
    hasMoved = false;
}

void Piece::setPosition(int x_next, int y_next){
    pos.first = x_next;
    pos.second = y_next;
}

bool Piece::isInTable(std::pair<int, int> position){
    return ((position.first>= 0 && position.first<= 7) && (position.second>= 0 && position.second <= 7));
}

bool Piece::isInTable(){
    return isInTable(this->pos);
}


std::string Piece::getImage(int type){
    return "resources/pieces/"+std::to_string(type)+"/Bishop_black.png";
}

std::string Piece::getType(){
    return "piece";
}

//--------------- Pawn methods -------------------

Pawn::Pawn(std::pair<int,int> pos, bool isBlack) : Piece(pos, isBlack){}
Pawn::Pawn(Piece piece): Piece(piece.getPos(), piece.getPlayer()){}

std::vector<std::vector<std::pair<int, int>>>Pawn::path(std::pair<int,int> position)
{
    std::vector<std::vector< std::pair<int,int >>>p;
    p.resize(2);
    int posx, posy;
    posx = position.first;
    posy = position.second;

    // we go down, we are black
    if (player == 1){
        posy++;
        posx++;
        if (isInTable({posx, posy}))
            p[0].push_back(std::make_pair(posx, posy));
        posx -= 2;
        if (Piece::isInTable({posx, posy}))
            p[1].push_back(std::make_pair(posx, posy));
    }
    // we go up, we are white
    else{
        posy--;
        posx++;
        if (isInTable({posx, posy}))
            p[0].push_back(std::make_pair(posx, posy));
        posx -= 2;
        if (isInTable({posx, posy}))
            p[1].push_back(std::make_pair(posx, posy));
    }
    return p;
}

std::string Pawn::getImage(int type){
    std::string img_location = "resources/pieces/"+std::to_string(type)+"/Pawn_";
    img_location += player==1 ? "black" : "white";
    img_location += ".png";
    return img_location;
}

std::string Pawn::getType(){
    return "pawn";
}

//-------------- Rook Methods ----------------

Rook::Rook(std::pair<int,int> pos, bool isBlack) : Piece(pos, isBlack){}
Rook::Rook(Piece piece): Piece(piece.getPos(), piece.getPlayer()){}

std::vector<std::vector<std::pair<int, int>>>Rook::path(std::pair<int,int> position)
{
    std::vector<std::vector< std::pair<int, int >>>p;
    p.resize(4);
    //it can go up, down, left, right;
    //---- first we go up
    int posx, posy;
    posx = position.first, posy = position.second;
    //left
    while (posx > 0)
        posx--, p[0].push_back(std::make_pair(posx, posy));
    posx = position.first, posy = position.second;
    //right
    while (posx < 7)
        posx++, p[1].push_back(std::make_pair(posx, posy));
    //up
    posx = position.first, posy = position.second;
    while (posy > 0)
        posy--, p[2].push_back(std::make_pair(posx, posy));
    posx = position.first, posy = position.second;
    //down
    while (posy < 7)
        posy++, p[3].push_back(std::make_pair(posx, posy));
    return p;

}

std::string Rook::getImage(int type){
    std::string img_location = "resources/pieces/"+std::to_string(type)+"/Rook_";
    img_location += player==1 ? "black" : "white";
    img_location += ".png";
    return img_location;
}

std::string Rook::getType(){
    return "rook";
}

// -------------- Knight Methods ------------------

Knight::Knight(std::pair<int,int> pos, bool isBlack) : Piece(pos, isBlack){}
Knight::Knight(Piece piece): Piece(piece.getPos(), piece.getPlayer()){}

std::vector<std::vector<std::pair<int, int>>>Knight::path(std::pair<int,int> position)
{
    std::vector<std::vector< std::pair<int, int >>>p;
    p.resize(8);
    int dist_x[] = { -2, -1, 2, 1, -2, -1, 2, 1 };
    int dist_y[] = { -1, -2, -1, -2, 1, 2, 1, 2 };
    for (int i = 0; i < 8; i++)
        if (Piece::isInTable({position.first + dist_x[i], position.second + dist_y[i]}))
            p[i].push_back(std::make_pair(position.first + dist_x[i], position.second + dist_y[i]));
    return p;

}

std::string Knight::getImage(int type){
    std::string img_location = "resources/pieces/"+std::to_string(type)+"/Knight_";
    img_location += player==1 ? "black" : "white";
    img_location += ".png";
    return img_location;
}

std::string Knight::getType(){
    return "knight";
}


// ------------ Bishop Methods ---------------

Bishop::Bishop(std::pair<int,int> pos, bool isBlack) : Piece(pos, isBlack){}
Bishop::Bishop(Piece piece): Piece(piece.getPos(), piece.getPlayer()){}

std::vector<std::vector<std::pair<int, int>>>Bishop::path(std::pair<int,int> position)
{
    std::vector<std::vector< std::pair<int, int >>>p;
    p.resize(4);
    int posx, posy;
    posx = position.first,posy = position.second;
    // up left
    while (Piece::isInTable({posx - 1, posy - 1}))
    {
        posx--, posy--, p[0].push_back(std::make_pair(posx, posy));
    }
     posx = position.first, posy = position.second;
    // up right
    while (Piece::isInTable({posx + 1, posy - 1}))
    {
        posx++, posy--, p[1].push_back(std::make_pair(posx, posy));
    }
     posx = position.first, posy = position.second;
    // down right
    while (Piece::isInTable({posx + 1, posy + 1}))
    {
        posx++, posy++, p[2].push_back(std::make_pair(posx, posy));
    }
    posx = position.first, posy = position.second;
    // down left
    while (Piece::isInTable({posx - 1, posy + 1}))
    {
        posx--, posy++, p[3].push_back(std::make_pair(posx, posy));
    }

    return p;

}


std::string Bishop::getImage(int type){
    std::string img_location = "resources/pieces/"+std::to_string(type)+"/Bishop_";
    img_location += player==1 ? "black" : "white";
    img_location += ".png";
    return img_location;
}

std::string Bishop::getType(){
    return "bishop";
}

// ---------------- Queen Methods ----------------

Queen::Queen(std::pair<int,int> pos, bool isBlack) : Piece(pos, isBlack){}
Queen::Queen(Piece piece): Piece(piece.getPos(), piece.getPlayer()){}

std::vector<std::vector<std::pair<int, int>>>Queen::path(std::pair<int,int> position)
{
    std::vector<std::vector< std::pair<int, int >>>p;
    p.resize(8);
    int posx, posy;
    posx = position.first, posy = position.second;
    //left
    while (posx > 0)
        posx--, p[0].push_back(std::make_pair(posx, posy));
     posx = position.first, posy = position.second;
    //right
    while (posx < 7)
        posx++, p[1].push_back(std::make_pair(posx, posy));
    //up
    posx = position.first, posy = position.second;
    while (posy > 0)
        posy--, p[2].push_back(std::make_pair(posx, posy));
    posx = position.first, posy = position.second;
    //down
    while (posy < 7)
        posy++, p[3].push_back(std::make_pair(posx, posy));


    posx = position.first, posy = position.second;
    // up left
    while (Piece::isInTable({posx - 1, posy - 1}))
    {
        posx--, posy--, p[4].push_back(std::make_pair(posx, posy));
    }
     posx = position.first, posy = position.second;
    // up right
    while (Piece::isInTable({posx + 1, posy - 1}))
    {
        posx++, posy--, p[5].push_back(std::make_pair(posx, posy));
    }
    posx = position.first, posy = position.second;
    // down right
    while (Piece::isInTable({posx + 1, posy + 1}))
    {
        posx++, posy++, p[6].push_back(std::make_pair(posx, posy));
    }
     posx = position.first, posy = position.second;
    // down left
    while (Piece::isInTable({posx - 1, posy + 1}))
    {
        posx--, posy++, p[7].push_back(std::make_pair(posx, posy));
    }

    return p;
}


std::string Queen::getImage(int type){
    std::string img_location = "resources/pieces/"+std::to_string(type)+"/Queen_";
    img_location += player==1 ? "black" : "white";
    img_location += ".png";
    return img_location;
}

std::string Queen::getType(){
    return "queen";
}

// ---------- King Methods -------------


King::King(std::pair<int,int> pos, bool isBlack) : Piece(pos, isBlack){}
King::King(Piece piece): Piece(piece.getPos(), piece.getPlayer()){}

std::vector<std::vector<std::pair<int, int>>>King::path(std::pair<int,int> position)
{
    std::vector<std::vector< std::pair<int, int >> >  p;
    p.resize(9);
    int dist_x[] = { 1, 1, 1, 0, -1, -1, -1, 0};
    int dist_y[] = { -1, 0, 1, 1, 1, 0, -1, -1 };
    for (int i = 0; i < 8; i++)
    {
        if (Piece::isInTable({position.first + dist_x[i], position.second + dist_y[i]}))
            p[i].push_back(std::make_pair(position.first + dist_x[i], position.second + dist_y[i]));
    }
    return p;
}

std::string King::getImage(int type){
    std::string img_location = "resources/pieces/"+std::to_string(type)+"/King_";
    img_location += player==1 ? "black" : "white";
    img_location += ".png";
    return img_location;
}

std::string King::getType(){
    return "king";
}

Piece* PieceFactory::createElement(std::string name, std::pair<int, int> pos, bool colour) const
{

    if(name == "Pawn"){
 
        return new Pawn(pos, colour);
    }
    if (name == "Rook"){

        return new Rook(pos, colour);
    }
    if (name == "Knight"){
        return new Knight(pos, colour);
    }
    if (name == "Bishop"){
        return new Bishop(pos, colour);
    }
    if (name == "Queen"){
        return (new Queen(pos, colour));
    }
    if(name == "King"){
        return (new King(pos, colour));
    }

    return nullptr;
}

std::vector<std::vector<std::pair<int, int>> >NullPiece::path(std::pair<int,int>)
{
    std::vector<std::vector<std::pair<int, int>> > v(0);
    return v;

}

std::string NullPiece::getType()
{
    std::string type = "Null";
    return type;
}