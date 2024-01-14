#include "othello_caretaker.h"
#include "othellomoment.h"

Othello_CareTaker::Othello_CareTaker()
{

}

void Othello_CareTaker::readfromfile(std::ifstream &infile, int board_size)
{
    int size;
    this->mementolist.clear();
    infile.read(reinterpret_cast<char*>(&size), sizeof(size));
    for(int i = 0 ; i < size ;i++){
       Chessboard* chessboard = new Chessboard(board_size);
       OthelloMement* othellomoment = new OthelloMement(chessboard,GameTurn::Black, Gamestate::Black_win);//初始化，无所谓，之后会更新
       othellomoment->readfromfile(infile);
       mementolist.push_back(dynamic_cast<MementIF*>(othellomoment));
    }
}
