#ifndef GOBANG_H
#define GOBANG_H
#include "consturtgame.h"
#include "GobangMoment.h"
#include <tuple>
#include <iostream>
#include <fstream>
#include "gobang_caretaker.h"
class Gobang:public ConstructGame{
    private:
    std::tuple<int,int> last_piece;


    public:
    bool set(int x, int y, PointState pointstate)override;
    Gamestate Ultimate_judgment()override;
    void reset()override;
    Gobang(int size);
    MementIF* create_memento()override;
    void restore_from_memento(MementIF*)override;
    void savetofile(std::ofstream &) override;
    void readfromfile(std::ifstream &) override;
};

#endif // GOBANG_H
