#include "go_caretaker.h"
#include "GoMoment.h"

Go_CareTaker::Go_CareTaker()
{

}

void Go_CareTaker::readfromfile(std::ifstream &infile,int chessboard_size)
{
    int size;
    this->mementolist.clear();
    infile.read(reinterpret_cast<char *>(&size),sizeof (size));
    for(int i = 0 ; i < size ;i++){
       Chessboard* temp = new Chessboard(chessboard_size);
       GoMoment* gomoment = new GoMoment(temp, GameTurn::Black, Gamestate::Black_win);//初始化，无所谓，之后会更新
       gomoment->readfromfile(infile);
       mementolist.push_back(dynamic_cast<MomentIF*>(gomoment));
    }
}
