#include "Game.h"
#include "go_caretaker.h"

Game::Game(int size):size(size){
    chessboard = new Chessboard(size);
}

Game::~Game(){
    delete chessboard;
}

bool Game::set(int x, int y){
    //加入备忘录
    this->caretaker->addMemento(this->create_memento(), this->step);
    this->step++;
    if(turn==GameTurn::Black){
        if(set(x,y,PointState::Black)){
            turn = GameTurn::White;
            this->gamestate = Ultimate_judgment();
            return true;
        }
    }
    if(turn==GameTurn::White){
        if(set(x,y,PointState::White)){
            turn = GameTurn::Black;
            this->gamestate = Ultimate_judgment();
            return true;
        }
    }
    this->step--;
}

bool Game::undo()
{
    if(step==0){
        printf("无棋可悔");
        return false;
    }
    step--;
    this->restore_from_memento(this->caretaker->getMemento(step));
}

//撤销悔棋是不安全的，需要在用户端来保证安全性
bool Game::unundo()
{
    step++;
    this->restore_from_memento(this->caretaker->getMemento(step));
}

MomentIF *Game::create_memento()
{
    return nullptr;
}

void Game::restore_from_memento(MomentIF *)
{
//在子类中实现
}

void Game::savetofile(std::ofstream& outfile)
{
    chessboard->savetofile(outfile);
    outfile.write(reinterpret_cast<char *>(&this->size), sizeof(this->size));
    outfile.write(reinterpret_cast<char *>(&this->step), sizeof(this->step));
    outfile.write(reinterpret_cast<char *>(&this->turn), sizeof(this->turn));
    outfile.write(reinterpret_cast<char *>(&this->gamestate), sizeof(this->gamestate));
    caretaker->savetofile(outfile);
}

void Game::readfromfile(std::ifstream& infile)
{
    chessboard->readfromfile(infile);
    infile.read(reinterpret_cast<char *>(&this->size), sizeof(this->size));
    infile.read(reinterpret_cast<char *>(&this->step), sizeof(this->step));
    infile.read(reinterpret_cast<char *>(&this->turn), sizeof(this->turn));
    infile.read(reinterpret_cast<char *>(&this->gamestate), sizeof(this->gamestate));
    caretaker->readfromfile(infile, size);
}



