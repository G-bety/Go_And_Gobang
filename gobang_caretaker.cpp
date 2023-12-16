#include "gobang_caretaker.h"
#include "GobangMoment.h"

Gobang_CareTaker::Gobang_CareTaker()
{

}

void Gobang_CareTaker::readfromfile(std::ifstream &infile, int board_size)
{
    int size;
    this->mementolist.clear();
    infile.read(reinterpret_cast<char *>(&size),sizeof (size));
    for(int i = 0 ; i < size ;i++){
       Chessboard* chessboard = new Chessboard(board_size);
       GobangMoment* gobangmoment = new GobangMoment(chessboard,std::make_tuple(-1,-1),GameTurn::Black, Gamestate::Black_win);//初始化，无所谓，之后会更新
       gobangmoment->readfromfile(infile);
       mementolist.push_back(dynamic_cast<MomentIF*>(gobangmoment));
    }
}
