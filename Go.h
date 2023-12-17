#ifndef GO_H
#define GO_H
#include "GoMoment.h"
#include <tuple>
#include <unordered_set>
#include <queue>
#include <iostream>
#include <fstream>
#include <go_caretaker.h>
#include "consturtgame.h"


using namespace std;

class Go:public ConstructGame{
    private:

    /**
     * @brief 给定位置坐标，判断该位置周围邻近四个方向是否有需要提去的子
     * */
    bool capture(const vector<Chessboardpoint*>& vec);//判断是否需要提子

    /**
     * @brief 判断当前位置的棋子是否有气
     * @return true:有气
    */
    bool liberty(int x, int y, vector<Chessboardpoint*>& capture_points);

    /**
     * @brief 判断当前位置的棋子是否有气
     * @return true:有气
    */
    bool liberty(int x, int y);

    /**
     *
    */
    bool liberty(Chessboardpoint* point ,vector<Chessboardpoint*>& capture_points);


    public:
    Go(int size);
    bool set(int x, int y, PointState pointstate)override;
    Gamestate Ultimate_judgment()override;
    MementIF* create_memento()override;
    void restore_from_memento(MementIF*)override;
    std::tuple<int,int> getmash();//点目函数
};


#endif // GO_H
