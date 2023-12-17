#ifndef GOBANGMOMENT_H
#define GOBANGMOMENT_H

#include "MomentIF.h"
#include "Chessboardpoint.h"
#include "GameTurn.h"
#include "Gamestate.h"
#include <vector>
#include <tuple>

class GobangMement:public MementIF{
    private:
    Chessboard* chessboard;
    std::tuple<int,int> last_piece;
    GameTurn turn;
    Gamestate gamestate;
    public:
    GobangMement(Chessboard* chessboard,std::tuple<int,int> last_piece, GameTurn turn, Gamestate gamestate);
    //void set_state(Chessboard* chessboard,std::tuple<int,int> last_piece, GameTurn turn, Gamestate gamestate);
    std::tuple<Chessboard* ,std::tuple<int,int> , GameTurn , Gamestate > get_state();
    ~GobangMement();
    void savetofile(std::ofstream &outfile) override;
    void readfromfile(std::ifstream &infile) override;
};

#endif // GOBANGMOMENT_H
