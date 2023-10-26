#include "../include/brain.h"
#include "../include/connector.h"
#include "../include/exception.h"

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

ostream& operator<<(ostream& out, const Brain& ob)
{
    out<<"Au fost efectuate " << ob.moves << " mutari\n";
    out<<"Evaluarea pieselor este: \n";
    for(const auto& x : ob.evaluation)
    {
        out << x.first << '\n';
        for(const auto& v : x.second)
        {
            for(const auto& eval : v)
                out << eval << " ";
            out <<'\n';
        }
    }
    return out;
}

Brain::Brain(Rules* _rules, bool *_playAgainstStockFish)
{
#if defined(_WIN32)
    ConnectToEngine("stockfish/stockfish_windows.exe");
#endif
    delete playAgainstStockFish;
    this->rules = _rules;
    this->playAgainstStockFish = _playAgainstStockFish;

    initializeEvaluation();
}
Brain::~Brain()
{
    //delete playAgainstStockFish;
    #if defined(_WIN32)
        CloseConnection();
    #endif
}

void Brain::initializeEvaluation()
{
    vector<string> pt = {"pawn", "bishop", "knight", "queen", "rook", "king"};
    for(const auto& p: pt)
    {
        ifstream read("resources/evaluation/"+p+".txt");
        int x;
        evaluation[p].resize(8);
        for(int i=0; i<8; i++)
            for (int j = 0; j < 8; j++)
            {
                read>>x;
                evaluation[p][i].push_back(x);
            }
        read.close();
    }
}

int Brain::getPointsEvaluation(Piece* piece)
{
    if (dynamic_cast<Pawn *>(piece))
        return 10;
    if (dynamic_cast<Knight *>(piece))
        return 30;
    if (dynamic_cast<Bishop *>(piece))
        return 30;
    if (dynamic_cast<Rook *>(piece))
        return 50;
    if (dynamic_cast<Queen *>(piece))
        return 90;
    if (dynamic_cast<King *>(piece))
        return 900;
    return 0;
}

int Brain::getEvaluation(Piece* piece, pair<int,int> pos, int for_player){
    if(for_player==1)
        return evaluation[piece->getType()][pos.second][pos.first];
    return evaluation[piece->getType()][7-pos.second][7-pos.first];
}

Evaluation Brain::evalAttacked(Piece* piece,  std::pair<int,int> position)
{
    Evaluation evalAttack{};
    evalAttack.eval = 0;
    evalAttack.nr_pieces = 0;
    for(Piece* current : rules->getPieces())
    {
        if(current -> getPlayer() != piece -> getPlayer())
        {
            Evaluation evalProtect = evalProtected(piece,position);
            if((current -> getType() != "king") || (current -> getType() == "king" && evalProtect.nr_pieces == 0))
            {
                vector<pair<int, int>> futurePositions =rules->canAttackPos(current,current -> getPos());
                for(auto x : futurePositions)
                    if(x.first == position.first && x.second == position.second)
                    {
                        evalAttack.nr_pieces ++;
                        evalAttack.eval += getPointsEvaluation(current);
                    }
            }
        }
    }
    return evalAttack;
}

Evaluation Brain::evalProtected(Piece* piece,  std::pair<int,int> position)
{
    Evaluation evalProtect{};
    evalProtect.eval =  getPointsEvaluation(piece);
    evalProtect.nr_pieces = 1;
    int maxim = getPointsEvaluation(piece);
    for(Piece* current : rules->getPieces())
        if(current -> getPlayer() == piece -> getPlayer() && current != piece)
        {

            vector<pair<int, int>> protectedPositions = rules->getProtectedPositions(current);


            for(auto x : protectedPositions)
                if(x.first == position.first && x.second == position.second)
                {
                    evalProtect.nr_pieces ++;
                    evalProtect.eval += getPointsEvaluation(current);
                    maxim = max ( maxim, getPointsEvaluation(current));
                    break;
                }
        }
    evalProtect.nr_pieces--;
    evalProtect.eval -= maxim;
    return evalProtect;
}

bool Brain::isOkToMove(Piece* piece, std::pair<int,int> position)
{
    rules -> updateCurrentBoard(board);
    board[piece -> getPlayer()][position.first][position.second] = piece;
    board[piece -> getPlayer()][piece -> getPos().first][piece -> getPos().second] = nullPiece;

    board[piece -> getPlayer()][position.first][position.second] = nullPiece;
    board[piece -> getPlayer()][piece -> getPos().first][piece -> getPos().second] = piece;

    #if defined(_WIN32)
        Evaluation evalProtect = evalProtected(piece,position);
        Evaluation evalAttack = evalAttacked(piece,position);
        if(evalAttack.nr_pieces <= evalProtect.nr_pieces && evalAttack.eval <= evalProtect.eval)
            return true;
        return false;
    #else
        if(auto evalProtect = evalProtected(piece,position), evalAttack = evalAttacked(piece,position);evalAttack.nr_pieces <= evalProtect.nr_pieces && evalAttack.eval <= evalProtect.eval)
            return true;
        return false;
    #endif
}

bool Brain::canCheck(Piece* piece, std::pair<int,int> position)
{
    rules->updateCurrentBoard(board);

    if(board[0][position.first][position.second] ->getType() != "Null")
    {
        int eval = getPointsEvaluation(board[0][position.first][position.second]);
        int evalpiece = getPointsEvaluation(piece);
        if(eval < evalpiece)
            return false;
        else
        {
            Evaluation evalProtect = evalProtected(board[0][position.first][position.second],board[0][position.first][position.second] -> getPos());
            Evaluation evalAttack = evalAttacked(board[0][position.first][position.second],board[0][position.first][position.second] -> getPos());
            if(evalAttack.nr_pieces <= evalProtect.nr_pieces && (evalAttack.nr_pieces <= evalProtect.nr_pieces || evalAttack.eval > evalProtect.eval) )
                return false;
        }
    }
    std::pair<int,int> pos = piece -> getPos();

    board[1][position.first][position.second] = piece;
    board[1][pos.first][pos.second] = nullPiece;
    vector<pair<int, int>> futurePositions =rules->getFuturePositions(board[1][position.first][position.second],position,false);
    for(auto x : futurePositions)
        if(board[0][x.first][x.second] ->getType() != "Null" && board[0][x.first][x.second] -> getType() == "king")
        {
            board[1][position.first][position.second] = nullPiece;
            board[1][pos.first][pos.second] = piece;
            return true;
        }
    board[1][position.first][position.second] = nullPiece;
    board[1][pos.first][pos.second] = piece;
    return false;
}

bool Brain::pieceIsAttacked(Piece* piece, std::pair<int,int> position){
    Evaluation evalProtect = evalProtected(piece,position);
    Evaluation evalAttack = evalAttacked(piece,position);
    if(evalAttack.eval == 0 || (evalAttack.nr_pieces <= evalProtect.nr_pieces && evalAttack.eval >= evalProtect.eval) )
        return false;
    cout<<piece->getType() << " " << piece ->getPos().first + 1 << " " << 8 - piece->getPos().second << " "  << evalProtect.eval << " " << evalAttack.eval <<'\n';
    return true;
}

bool Brain::checkLast3Moves(Move check_move){
    int n = lastBrainMoves.size();
    try{
        if(n > 0 && lastBrainMoves[n - 1].to == check_move.to && lastBrainMoves[n - 1].from == check_move.from)
            return true;
        if(n > 1  && lastBrainMoves[n - 2].to == check_move.to && lastBrainMoves[n - 2].from == check_move.from)
            return true;
        if ( n > 2 && lastBrainMoves[n - 3].to == check_move.to && lastBrainMoves[n - 3].from == check_move.from)
            return true;
    } catch (...) {
        return false;
    }
    return false;
}

bool Brain::checkLast3Moves(Piece* piece)
{
    int n = lastBrainMoves.size();
    try{
        if(piece->getType() == "pawn" && moves < 5 && (piece->getPos().second == 3 || piece->getPos().second == 4))
            return false;
        if(n > 0 && lastBrainMoves[n - 1].piece!=nullptr && lastBrainMoves[n - 1].piece->getType() == piece->getType())
            return true;
        if(n > 1 && lastBrainMoves[n - 2].piece!=nullptr && lastBrainMoves[n - 2].piece -> getType() == piece->getType())
            return true;
        if(n > 2 && lastBrainMoves[n - 3].piece!=nullptr && lastBrainMoves[n - 3].piece -> getType() == piece->getType())
            return true;
    } catch (...) {
        return false;
    }
    return false;
}

void Brain::restartGame()
{
     for(auto &move: lastBrainMoves)
    {
        delete move.updatedPiece;
        delete move.deletedPiece;
    }
    lastBrainMoves.clear();
}


Move Brain::determineBrainBestMove(int for_player){
    if(rules == nullptr)
        throw Exception("Error: Rules not set!");

    vector<Move> future_pos;

    Move best_eval_move;
    int best_eval = -9999;
    Move best_removed_move;
    int best_removed = -9999;
    Move best_eval_check_move;
    int best_eval_check = -9999;
    Move best_attacked_move;
    int best_eval_attacked_piece = -9999;
    ///ma plimb prin piese

    rules->updateCurrentBoard(board);
    for(Piece* piece: rules->getPieces())
        if(piece->getPlayer() == for_player){
            Move best_current_eval_move;
            int best_current_eval = -9999;
            ///ma plimb prin pozitiile in care poate ajunge fiecare piese
            for(auto pos: rules->getFuturePositions(piece)){
                Piece* opPlayer = rules->getPiece(!piece->getPlayer(), pos); ///tipul pozitiei in care poate ajunge
                future_pos.emplace_back(Move(piece, pos));
                int eval = this->getEvaluation(piece, pos, for_player) * 10;
                int evalpiece_AI = getPointsEvaluation(opPlayer);
                ///evaluarea dupa sah
                ///sa nu muti piese in pozitiile unde ataca pisele adverse,facut
                ///sa nu muti cu aceeasi piesa de mai multe ori in primele 10 mutari
                ///sa muti piesele atacate,facut
                ///sa isi apere piesele atacate
                ///sa dea mat
                if(canCheck(piece,pos) == 1 && isOkToMove(piece,pos) == 1){
                    if(eval > best_eval_check){
                        best_eval_check = eval;
                        best_eval_check_move = Move(piece,pos);
                    }
                }
                else{
                    if(opPlayer ->getType() == "Null" && eval > best_current_eval && isOkToMove(piece,pos) == 1){
                        best_current_eval = eval;
                        best_current_eval_move = Move(piece,pos);
                    }
                    if(opPlayer ->getType() == "Null" && eval > best_eval && isOkToMove(piece,pos) == 1 && checkLast3Moves(piece) == false){
                        if(piece -> getType() != "rook" && piece -> getType() != "king"){
                            best_eval = eval;
                            best_eval_move = Move(piece, pos);
                        }
                        else if( piece -> getType() == "rook" && moves > 10){
                            best_eval = eval;
                            best_eval_move = Move(piece, pos);
                        }
                        else if( piece -> getType() == "king" && (moves > 40 || abs(piece -> getPos().first - pos.first) > 1)){
                            best_eval = eval;
                            best_eval_move = Move(piece, pos);
                        }
                    }
                }
                if(opPlayer ->getType() != "Null" && opPlayer -> getType() != "king"){
                    if(piece -> getType() != "king"){
                        getPointsEvaluation(opPlayer);
                        int evalpiece_me = getPointsEvaluation(piece);
                        if(evalpiece_me <= evalpiece_AI){
                            if (evalpiece_AI > best_removed){
                                best_removed = evalpiece_AI;
                                best_removed_move = Move(piece, pos);
                            }
                        }
                        else{
                            Evaluation evalProtect = evalProtected(opPlayer,opPlayer -> getPos());
                            Evaluation evalAttack = evalAttacked(opPlayer,opPlayer -> getPos());
                            if(evalAttack.nr_pieces > evalProtect.nr_pieces || (evalAttack.nr_pieces > evalProtect.nr_pieces && evalAttack.eval <= evalProtect.eval) ){
                                if(evalpiece_AI > best_removed){
                                    best_removed = evalpiece_AI;
                                    best_removed_move = Move(piece, pos);
                                }
                            }
                        }
                    }
                    else{
                        Evaluation evalProtect = evalProtected(opPlayer,opPlayer -> getPos());
                        if(evalProtect.nr_pieces == 0){
                            best_removed = 999;
                            best_removed_move = Move(piece,pos);
                        }
                    }
                }
            }
            ///verific daca piesa e atacata
            if(pieceIsAttacked(piece,piece->getPos())){
                int evalPiece = getPointsEvaluation(piece);
                if(evalPiece > best_eval_attacked_piece){
                    best_eval_attacked_piece = evalPiece;
                    best_attacked_move = best_current_eval_move;
                }
            }
        }
    moves += 1;
    if(future_pos.empty()){
        cout << "No moves found! Checkmate\n";
        return {};
    }
    if(best_removed_move.piece != nullptr && best_removed_move.piece ->getType() != "Null"){
        cout<<"Found the best piece to remove\n";
        lastBrainMoves.push_back(best_removed_move);
        return best_removed_move;
    }
    if(best_attacked_move.piece != nullptr && best_attacked_move.piece->getType() != "Null"){
        cout<<"Found the best piece under attack to move u\n";
        lastBrainMoves.push_back(best_attacked_move);
        return best_attacked_move;
    }
    if(best_eval_check_move.piece != nullptr && best_eval_check_move.piece ->getType() != "Null" && checkLast3Moves(best_eval_check_move) == false){
        cout<<"Moving based on check\n";
        lastBrainMoves.push_back(best_eval_check_move);
        return best_eval_check_move;
    }
    if(best_eval_move.piece != nullptr && best_eval_move.piece->getType() != "Null" && checkLast3Moves(best_eval_move) == false){
        cout<<"Moving based on evaluation\n";
        lastBrainMoves.push_back(best_eval_move);
        return best_eval_move;
    }
    cout << "Moving to a random position\n";
    return future_pos[rand() % future_pos.size()];
}

Move Brain::determineStockFishBestMove(int for_player){
    Move Best_move;
    try{
        rules->updateCurrentBoard(board);

        std::string last_moves, determined_move;
        last_moves = rules->parseHistory();
        determined_move = getNextMove(last_moves);

        if(determined_move.empty() || determined_move=="None") throw Exception("Error: Wrong stockfish answer!");

        std::pair<int,int> pos_best_move;
        std::pair<int,int> pos_piece;

        pos_piece.first = int(determined_move[0] - 97);
        pos_piece.second = 8 - (determined_move[1] - '0');
        pos_best_move.first = int(determined_move[2] - 97);
        pos_best_move.second = 8 - (determined_move[3] - '0');

        Piece* piece = board[rules->getCurrentPlayer()][pos_piece.first][pos_piece.second];
        Best_move = Move(piece, pos_piece, pos_best_move);

    }catch(Exception &e){
        std::cerr<<e.what()<<'\n';
        Best_move = this->determineBrainBestMove(for_player);
    }
    return Best_move;
}

Move Brain::determineBestMove(int for_player){
    if(*playAgainstStockFish)
        return determineStockFishBestMove(for_player);
    return determineBrainBestMove(for_player);
}
