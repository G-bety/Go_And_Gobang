#include "othellomoment.h"

OthelloMement::OthelloMement(Chessboard *chessboard, GameTurn turn, Gamestate gamestate):
  turn(turn), gamestate(gamestate)
{
    this->chessboard = new Chessboard(*chessboard);
}

OthelloMement::~OthelloMement()
{
    delete chessboard;
}

void OthelloMement::savetofile(std::ofstream &outfile)
{
    chessboard->savetofile(outfile);
    outfile.write(reinterpret_cast<char *>(&turn), sizeof (turn));
    outfile.write(reinterpret_cast<char *>(&gamestate), sizeof (gamestate));
}

void OthelloMement::readfromfile(std::ifstream &infile)
{
    chessboard->readfromfile(infile);
    infile.read(reinterpret_cast<char *>(&turn), sizeof (turn));
    infile.read(reinterpret_cast<char *>(&gamestate), sizeof (gamestate));
}

std::tuple<Chessboard *, GameTurn, Gamestate> OthelloMement::get_state()
{
    return std::make_tuple(chessboard, turn, gamestate);
}




