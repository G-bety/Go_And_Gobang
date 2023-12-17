#include "GoMoment.h"
#include <tuple>
#include "Chessboard.h"

GoMement::GoMement(Chessboard *chessboard, GameTurn turn, Gamestate gamestate)
{
    if(chessboard == nullptr){//这步是因为有时只是需要初始化Goment方便后面readfromfile，此时只需要对this->chessboard进行简单初始化即可
        this->chessboard = new Chessboard(0);
    }
    else{
        this->chessboard = new Chessboard(*chessboard);
    }
    this->turn = turn;
    this->gamestate = gamestate;
}

/*void GoMoment::set_state(Chessboard* chessboard, GameTurn turn, Gamestate gamestate){
    this->chessboard = chessboard;
    this->turn = turn;
    this->gamestate = gamestate;
}*/

std::tuple<Chessboard* , GameTurn , Gamestate> GoMement::get_state(){
    return std::make_tuple(chessboard, turn, gamestate);
}

GoMement::~GoMement()
{
    delete chessboard;
}

void GoMement::savetofile(std::ofstream& outfile)
{
    chessboard->savetofile(outfile);
    outfile.write(reinterpret_cast<char *>(&turn), sizeof (turn));
    outfile.write(reinterpret_cast<char *>(&gamestate), sizeof (gamestate));
}

void GoMement::readfromfile(std::ifstream& infile)
{
    chessboard->readfromfile(infile);
    infile.read(reinterpret_cast<char *>(&turn), sizeof (turn));
    infile.read(reinterpret_cast<char *>(&gamestate), sizeof (gamestate));
}
