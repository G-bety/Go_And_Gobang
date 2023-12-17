#include "consturtgame.h"

ConstructGame::ConstructGame(int size):size(size){
    chessboard = new Chessboard(size);
}

ConstructGame::~ConstructGame(){
    delete chessboard;
}

bool ConstructGame::set(int x, int y){
    //加入备忘录
    this->caretaker->addMemento(this->create_memento(), this->step);
    this->step++;
    if(gameturn==GameTurn::Black){
        if(set(x,y,PointState::Black)){
            gameturn = GameTurn::White;
            return true;
        }
    }
    if(gameturn==GameTurn::White){
        if(set(x,y,PointState::White)){
            gameturn = GameTurn::Black;
            return true;
        }
    }
    this->step--;
}

bool ConstructGame::undo()
{
    if(step==0){
        printf("无棋可悔");
        return false;
    }
    step--;
    this->restore_from_memento(this->caretaker->getMemento(step));
}

//撤销悔棋是不安全的，需要在用户端来保证安全性
bool ConstructGame::unundo()
{
    step++;
    this->restore_from_memento(this->caretaker->getMemento(step));
}

void ConstructGame::reset()
{
    this->chessboard->initChessboard();
    this->gamestate = Gamestate::Keeping_battle;
    this->gameturn = GameTurn::Black;
    this->step = 0;
}


void ConstructGame::restore_from_memento(MementIF *)
{
//在子类中实现
}

void ConstructGame::savetofile(std::ofstream& outfile)
{
    chessboard->savetofile(outfile);
    outfile.write(reinterpret_cast<char *>(&this->size), sizeof(this->size));
    outfile.write(reinterpret_cast<char *>(&this->step), sizeof(this->step));
    outfile.write(reinterpret_cast<char *>(&this->gameturn), sizeof(this->gameturn));
    outfile.write(reinterpret_cast<char *>(&this->gamestate), sizeof(this->gamestate));
    caretaker->savetofile(outfile);
}

void ConstructGame::readfromfile(std::ifstream& infile)
{
    chessboard->readfromfile(infile);
    infile.read(reinterpret_cast<char *>(&this->size), sizeof(this->size));
    infile.read(reinterpret_cast<char *>(&this->step), sizeof(this->step));
    infile.read(reinterpret_cast<char *>(&this->gameturn), sizeof(this->gameturn));
    infile.read(reinterpret_cast<char *>(&this->gamestate), sizeof(this->gamestate));
    caretaker->readfromfile(infile, size);
}

void ConstructGame::surrender()
{
    if(gameturn == GameTurn::Black){
        gameturn  = GameTurn::White;
        gamestate = Gamestate::White_win;
    }
    else if(gameturn == GameTurn::White){
        gameturn  = GameTurn::Black;
        gamestate = Gamestate::Black_win;
    }
}

