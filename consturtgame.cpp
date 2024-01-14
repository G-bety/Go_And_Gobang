#include "consturtgame.h"

ConstructGame::ConstructGame(int size):size(size){
    chessboard = new Chessboard(size);
}

ConstructGame::~ConstructGame(){
    delete chessboard;
}

bool ConstructGame::set(int x, int y){
    //加入备忘录
    if(this->observe_step < this->step) {
        this->step = this->observe_step;
    }
    if(this->step == 0){
        this->caretaker->addMemento(this->create_memento(), this->step);
        this->step++;
    }
    if(gameturn==GameTurn::Black){
        if(set(x,y,PointState::Black)){
            gameturn = GameTurn::White;
            this->gamestate =  this->Ultimate_judgment();
            this->caretaker->addMemento(this->create_memento(), this->step);
            this->step++;
            this->observe_step = this->step;
            return true;
        }
    }
    if(gameturn==GameTurn::White){
        if(set(x,y,PointState::White)){
            gameturn = GameTurn::Black;
            this->gamestate =  this->Ultimate_judgment();
            this->caretaker->addMemento(this->create_memento(), this->step);
            this->step++;
            this->observe_step = this->step;
            return true;
        }
    }
    return false;
}

bool ConstructGame::undo()
{
    //observe_step表示当前通过undo查看到的对局轮次位置
    if(this->observe_step<=1){
        printf("无棋可悔");
        return false;
    }
    observe_step--;
    this->restore_from_memento(this->caretaker->getMemento(observe_step-1));
}

//撤销悔棋是不安全的，需要在用户端来保证安全性
bool ConstructGame::unundo()
{
    //step表示当前棋局进行到的轮次位置
    if(observe_step < step){
        observe_step++;
        this->restore_from_memento(this->caretaker->getMemento(observe_step-1));
    }
}

void ConstructGame::reset()
{
    this->chessboard->initChessboard();
    this->gamestate = Gamestate::Keeping_battle;
    this->gameturn = GameTurn::Black;
    this->step = 0;
}



void ConstructGame::savetofile(std::ofstream& outfile)
{
    chessboard->savetofile(outfile);
    outfile.write(reinterpret_cast<char *>(&this->size), sizeof(this->size));
    outfile.write(reinterpret_cast<char *>(&this->step), sizeof(this->step));
    outfile.write(reinterpret_cast<char *>(&this->observe_step), sizeof(this->observe_step));
    outfile.write(reinterpret_cast<char *>(&this->gameturn), sizeof(this->gameturn));
    outfile.write(reinterpret_cast<char *>(&this->gamestate), sizeof(this->gamestate));
    caretaker->savetofile(outfile);
}

void ConstructGame::readfromfile(std::ifstream& infile)
{
    chessboard->readfromfile(infile);
    infile.read(reinterpret_cast<char *>(&this->size), sizeof(this->size));
    infile.read(reinterpret_cast<char *>(&this->step), sizeof(this->step));
    infile.read(reinterpret_cast<char *>(&this->observe_step), sizeof(this->observe_step));
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

