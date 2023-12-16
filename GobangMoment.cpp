#include "GobangMoment.h"
#include "Chessboard.h"

GobangMoment::GobangMoment(Chessboard *chessboard, std::tuple<int, int> last_piece, GameTurn turn, Gamestate gamestate)
{
    this->chessboard = new Chessboard(*chessboard);
    this->last_piece = last_piece;
    this->turn = turn;
    this->gamestate = gamestate;
}
/*
void GobangMoment::set_state(Chessboard* chessboard,std::tuple<int,int> last_piece, GameTurn turn, Gamestate gamestate){
    this->chessboard = chessboard;
    this->last_piece = last_piece;
    this->turn = turn;
    this->gamestate = gamestate;
}
*/
std::tuple<Chessboard*,std::tuple<int,int>,GameTurn,Gamestate> GobangMoment::get_state(){
    return  std::make_tuple(chessboard, last_piece ,turn, gamestate);
}

GobangMoment::~GobangMoment()
{
    delete chessboard;
}

void GobangMoment::savetofile(std::ofstream &outfile)
{
    chessboard->savetofile(outfile);
    outfile.write(reinterpret_cast<char *>(&turn), sizeof (turn));
    outfile.write(reinterpret_cast<char *>(&gamestate), sizeof (gamestate));
    outfile.write(reinterpret_cast<char *>(&last_piece), sizeof (last_piece));
}

void GobangMoment::readfromfile(std::ifstream &infile)
{
    chessboard->readfromfile(infile);
    infile.read(reinterpret_cast<char *>(&turn), sizeof (turn));
    infile.read(reinterpret_cast<char *>(&gamestate), sizeof (gamestate));
    infile.read(reinterpret_cast<char *>(&last_piece), sizeof (last_piece));
}
