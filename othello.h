#ifndef OTHELLO_H
#define OTHELLO_H

#include <tuner.h>
#include "consturtgame.h"
#include "othellomoment.h"
#include "othello_caretaker.h"
class Othello:public ConstructGame
{
public:
    Othello(int size);


    // OperationWithFile interface
public:
    //void savetofile(std::ofstream &filePath);
    //void readfromfile(std::ifstream &filePath);

    // ConstructGame interface
protected:
    bool set(int x, int y, PointState pointstate)override;
    std::vector<std::tuple<int,int>> black_vali_locs;
    std::vector<std::tuple<int,int>> white_vali_locs;
    void search_vali_locs();

public:
    //bool set(int x, int y);
    Gamestate Ultimate_judgment()override;
    MementIF *create_memento()override;
    void restore_from_memento(MementIF *)override;
    //void surrender();

    // ConstructGame interface
public:
    void reset()override;
};

#endif // OTHELLO_H
