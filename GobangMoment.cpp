#include "GobangMoment.h"
#include "Chessboard.h"

GobangMement::GobangMement(Chessboard *chessboard, std::tuple<int, int> last_piece, GameTurn turn, Gamestate gamestate)
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
std::tuple<Chessboard*,std::tuple<int,int>,GameTurn,Gamestate> GobangMement::get_state(){
    return  std::make_tuple(chessboard, last_piece ,turn, gamestate);
}

GobangMement::~GobangMement()
{
    delete chessboard;
}

void GobangMement::savetofile(std::ofstream &outfile)
{
    chessboard->savetofile(outfile);
    outfile.write(reinterpret_cast<char *>(&turn), sizeof (turn));
    outfile.write(reinterpret_cast<char *>(&gamestate), sizeof (gamestate));
    outfile.write(reinterpret_cast<char *>(&last_piece), sizeof (last_piece));
}

void GobangMement::readfromfile(std::ifstream &infile)
{
    chessboard->readfromfile(infile);
    infile.read(reinterpret_cast<char *>(&turn), sizeof (turn));
    infile.read(reinterpret_cast<char *>(&gamestate), sizeof (gamestate));
    infile.read(reinterpret_cast<char *>(&last_piece), sizeof (last_piece));
}
