#ifndef OTHELLOMOMENT_H
#define OTHELLOMOMENT_H
#include "MomentIF.h"
#include "boardshow.h"

class OthelloMement:public MementIF
{
public:
    OthelloMement(Chessboard* chessboard, GameTurn turn, Gamestate gamestate);
    ~OthelloMement();
    // MementIF interface
public:
    void savetofile(std::ofstream &outfile);
    void readfromfile(std::ifstream &infile);
    std::tuple<Chessboard*, GameTurn, Gamestate> get_state();

private:
    Chessboard* chessboard;
    GameTurn turn;
    Gamestate gamestate;
};

#endif // OTHELLOMOMENT_H
