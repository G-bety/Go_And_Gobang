#ifndef GOMOMENT_H
#define GOMOMENT_H

#include "MomentIF.h"
#include "Chessboardpoint.h"
#include <vector>
#include "GameTurn.h"
#include "Gamestate.h"
#include <tuple>
#include <fstream>
class GoMoment:public MomentIF{
    private:
    Chessboard* chessboard;
    GameTurn turn;
    Gamestate gamestate;
    public:
    GoMoment(Chessboard* chessboard, GameTurn turn, Gamestate gamestate);
    //void set_state(Chessboard* chessboard, GameTurn turn, Gamestate gamestate);
    std::tuple<Chessboard* , GameTurn , Gamestate> get_state();
    ~GoMoment();
    void savetofile(std::ofstream& outfile);
    void readfromfile(std::ifstream& outfile);
};


#endif // GOMOMENT_H
