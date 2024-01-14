#include "gobang_ai.h"
#include <random>
#include <vector>
#include <tuple>
#include <chrono>


Gobang_AI::Gobang_AI(int size):Gobang(size){}

bool Gobang_AI::set(int x, int y)
{
    if(ConstructGame::set(x,y)){
        //Gamestate ret =  this->Ultimate_judgment();
        if(this->Ultimate_judgment()!=Gamestate::Keeping_battle){
            return true;
        }
        if(this->observe_step < this->step) {
            this->step = this->observe_step;
        }
        if(this->step == 0){
            this->caretaker->addMemento(this->create_memento(), this->step);
            this->step++;
        }
        if(gameturn==GameTurn::Black){
            gameturn = GameTurn::White;
            if(autoset(x,y,PointState::Black)){
                this->gamestate =  this->Ultimate_judgment();
                this->caretaker->addMemento(this->create_memento(), this->step);
                this->step++;
                this->observe_step = this->step;
                return true;
            }
        }
        if(gameturn==GameTurn::White){
            gameturn = GameTurn::Black;
            if(autoset(x,y,PointState::White)){
                this->gamestate =  this->Ultimate_judgment();
                this->caretaker->addMemento(this->create_memento(), this->step);
                this->step++;
                this->observe_step = this->step;
                return true;
            }
        }
        return false;

    }
    return false;
}


Gobang_AI_1::Gobang_AI_1(int size):Gobang_AI(size){}

bool Gobang_AI_1::autoset(int x, int y, PointState pointstate)
{
    std::vector<std::tuple<int,int>> candidate_points;
    for(int i = 0 ; i < size ; i++){
        for(int j = 0 ; j < size ; j++){
            if(chessboard->getpoint(i,j)->get_state() == PointState::Blank){
                candidate_points.push_back(std::make_tuple(i,j));
            }
        }
    }
    if(candidate_points.size()==0){
        return false;
    }
    auto timestamp = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(static_cast<unsigned int>(timestamp));
    std::uniform_int_distribution<> dis(0, candidate_points.size() - 1);
    int randomIndex = dis(gen);
    int index_x = std::get<0>(candidate_points[randomIndex]);
    int index_y = std::get<1>(candidate_points[randomIndex]);
    chessboard->getpoint(index_x,index_y)->set_state(pointstate);
    this->last_piece = std::make_tuple(index_x,index_y);
    this->gamestate =  this->Ultimate_judgment();
}

bool Gobang_AI::undo()
{
    Gobang::undo();
    if(this->observe_step<=1){
        printf("无棋可悔");
        return false;
    }
    observe_step--;
    this->restore_from_memento(this->caretaker->getMemento(observe_step-1));

}

bool Gobang_AI::unundo()
{
    Gobang::unundo();
    if(observe_step < step){
        observe_step++;
        this->restore_from_memento(this->caretaker->getMemento(observe_step-1));
    }
}

Gobang_AI_2::Gobang_AI_2(int size):Gobang_AI(size){}



bool Gobang_AI_2::autoset(int x, int y, PointState pointstate)
{
    std::vector<std::vector<std::tuple<int,int>>> candidate_points(10);
    PointState positive = pointstate;
    PointState negative = PointState::White==pointstate?PointState::Black:PointState::White;
    for(int i = 0 ; i < size ; i++){
        for(int j = 0 ; j < size ; j++){
            if(chessboard->getpoint(i,j)->get_state() == PointState::Blank){
                int positive_bondnums = get_bond_num(i,j,positive);
                candidate_points[positive_bondnums*2+1].push_back(std::make_tuple(i,j));
                int negative_bondnums = get_bond_num(i,j,negative);
                candidate_points[negative_bondnums*2].push_back(std::make_tuple(i,j));
            }
        }
    }
    for(int i = candidate_points.size()-1 ; i >= 0 ; i--){
        if(candidate_points[i].size()>0){
            auto timestamp = std::chrono::system_clock::now().time_since_epoch().count();
            std::mt19937 gen(static_cast<unsigned int>(timestamp));
            std::uniform_int_distribution<> dis(0, candidate_points[i].size() - 1);
            int randomIndex = dis(gen);
            int index_x = std::get<0>(candidate_points[i][randomIndex]);
            int index_y = std::get<1>(candidate_points[i][randomIndex]);
            chessboard->getpoint(index_x,index_y)->set_state(pointstate);
            this->last_piece = std::make_tuple(index_x,index_y);
            this->gamestate =  this->Ultimate_judgment();
            return true;
        }
    }
    return false;
}

int Gobang_AI_2::get_bond_num(int x, int y, PointState nowstate)
{
    //四个方向依次判断
    //垂直方向
    int ret = 0;
    int samenumber=0;
    for(int i=x-1; i>=0 && chessboard->getpoint(i,y)->get_state()==nowstate; i--){
        samenumber++;
    }
    for(int i=x+1; i<size && chessboard->getpoint(i,y)->get_state()==nowstate; i++){
        samenumber++;
    }
    ret = ret<samenumber?samenumber:ret;

    //水平方向
    samenumber = 0;
    for(int j=y-1;j>=0 && chessboard->getpoint(x,j)->get_state()==nowstate; j--){
        samenumber++;
    }
    for(int j=y+1;j<size && chessboard->getpoint(x,j)->get_state()==nowstate; j++){
        samenumber++;
    }
    ret = ret<samenumber?samenumber:ret;

    //-45°方向
    samenumber = 0;
    int i,j;
    for(i=x-1,j=y-1; i>=0 && j >=0 && chessboard->getpoint(i,j)->get_state()==nowstate;i--,j--){
        samenumber++;
    }

    for(i=x+1,j=y+1; i<size && j <size && chessboard->getpoint(i,j)->get_state()==nowstate;i++,j++){
        samenumber++;
    }
    ret = ret<samenumber?samenumber:ret;

    //45°方向

    samenumber = 0;
    for(i=x-1,j=y+1; i>=0 && j<size && chessboard->getpoint(i,j)->get_state()==nowstate;i--,j++){
        samenumber++;
    }

    for(i=x+1,j=y-1; i<size && j>=0 && chessboard->getpoint(i,j)->get_state()==nowstate;i++,j--){
        samenumber++;
    }
    ret = ret<samenumber?samenumber:ret;
    return ret;

}
