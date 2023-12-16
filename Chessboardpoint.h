#pragma once
#include <tuple>
#include "PointState.h"
class Chessboard;


class Chessboardpoint
{
private:
    /* data */
    int x,y;
    Chessboardpoint* up;
    Chessboardpoint* down;
    Chessboardpoint* left;
    Chessboardpoint* right;
    PointState state;
public:
    Chessboardpoint(int x, int y, PointState state=PointState::Blank, Chessboardpoint* up=nullptr,Chessboardpoint* down=nullptr,
                    Chessboardpoint* left=nullptr, Chessboardpoint* right=nullptr):x(x),y(y),
                    state(state),up(up),down(down),left(left),right(right){}

    ~Chessboardpoint(){};
    Chessboardpoint* get_up(){
        return up;
    }
    Chessboardpoint* get_down(){
        return down;
    }
    Chessboardpoint* get_left(){
        return left;
    }
    Chessboardpoint* get_right(){
        return right;
    }
    std::tuple<int , int> get_location(){
      return std::tuple<int,int>(x,y);
    }
    PointState get_state(){
        return state;
    }
    void set_state(PointState state){
        this->state=state;
    }
    friend class Chessboard;
};

