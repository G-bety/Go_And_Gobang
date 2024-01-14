#include "othello.h"


Othello::Othello(int size):ConstructGame(size)
{
    chessboard->getpoint(size/2-1,size/2-1)->set_state(PointState::White);
    chessboard->getpoint(size/2,size/2)->set_state(PointState::White);
    chessboard->getpoint(size/2-1,size/2)->set_state(PointState::Black);
    chessboard->getpoint(size/2,size/2-1)->set_state(PointState::Black);
    this->caretaker = new Othello_CareTaker();
}

bool Othello::set(int x, int y, PointState pointstate=PointState::Blank)
{
    search_vali_locs();
    std::vector<std::tuple<int,int>>& vali_locs = gameturn==GameTurn::Black?black_vali_locs:white_vali_locs;
    PointState state = gameturn==GameTurn::Black?PointState::Black:PointState::White;
    PointState adverse_state = gameturn==GameTurn::Black?PointState::White:PointState::Black;
    for(auto vali_loc:vali_locs){
        if(vali_loc == std::make_tuple(x,y)){
            //上方向翻转
            int k = x-1;
            if(k>=0 && chessboard->getpoint(k, y)->get_state()==adverse_state){
                for(; k>=0 ; k--){
                    Chessboardpoint* point = chessboard->getpoint(k, y);
                    if(point->get_state()==adverse_state){
                        continue;
                    }
                    else{
                        break;
                    }
                }
                if(k>=0&&chessboard->getpoint(k,y)->get_state() == state){
                    for(; k < x; k++){
                        chessboard->getpoint(k,y)->set_state(state);
                    }
                }
            }


            //下方向翻转
            k = x+1;
            if(k<=size-1 && chessboard->getpoint(k, y)->get_state()==adverse_state){
                for(; k<=size-1 ; k++){
                    Chessboardpoint* point = chessboard->getpoint(k, y);
                    if(point->get_state()==adverse_state){
                        continue;
                    }
                    else{
                        break;
                    }
                }
                if(k<=size-1&&chessboard->getpoint(k,y)->get_state() == state){
                    for(; k > x; k--){
                        chessboard->getpoint(k,y)->set_state(state);
                    }
                }
            }

            //左方向翻转
            k = y-1;
            if(k>=0 &&chessboard->getpoint(x, k)->get_state()==adverse_state){
                for(; k>=0 ; k--){
                    Chessboardpoint* point = chessboard->getpoint(x, k);
                    if(point->get_state()==adverse_state){
                        continue;
                    }
                    else{
                        break;
                    }
                }
                if(k>=0&&chessboard->getpoint(x,k)->get_state() == state){
                    for(; k < y; k++){
                        chessboard->getpoint(x,k)->set_state(state);
                    }
                }
            }



            //右方向翻转
            k = y+1;
            if(k<=size-1&&chessboard->getpoint(x, k)->get_state()==adverse_state){
                for(; k<=size-1 ; k++){
                    Chessboardpoint* point = chessboard->getpoint(x, k);
                    if(point->get_state()==adverse_state){
                        continue;
                    }
                    else{
                        break;
                    }
                }
                if(k<=size-1&&chessboard->getpoint(x,k)->get_state() == state){
                    for(; k > y; k--){
                        chessboard->getpoint(x,k)->set_state(state);
                    }
                }
            }


            //左上翻转
            k = 1;
            if(y-k>=0 && x-k >=0 && chessboard->getpoint(x-k,y-k)->get_state() == adverse_state){
                for(;x-k>=0 && y-k >=0;k++){
                    Chessboardpoint* point = chessboard->getpoint(x-k, y-k);
                    if(point->get_state()==adverse_state){
                        continue;
                    }
                    else{
                        break;
                    }
                }
                if(x-k>=0 && y-k >=0 && chessboard->getpoint(x-k,y-k)->get_state() == state){
                    for(k = k-1; k >=1 ; k--){
                        chessboard->getpoint(x-k,y-k)->set_state(state);
                    }
                }
            }

            //左下翻转
            k = 1;
            if(y-k>=0 && x+k <=size-1 && chessboard->getpoint(x+k,y-k)->get_state() == adverse_state){
                for(;x+k <=size-1 && y-k >=0;k++){
                    Chessboardpoint* point = chessboard->getpoint(x+k, y-k);
                    if(point->get_state()==adverse_state){
                        continue;
                    }
                    else{
                        break;
                    }
                }
                if(x+k <=size-1 && y-k >=0 && chessboard->getpoint(x+k,y-k)->get_state() == state){
                    for(k = k-1; k >=1 ; k--){
                        chessboard->getpoint(x+k,y-k)->set_state(state);
                    }
                }
            }

            //右上翻转
            k = 1;
            if(y+k<=size-1 && x-k >=0 && chessboard->getpoint(x-k,y+k)->get_state() == adverse_state){
                for(;x-k>=0 && y+k<=size-1;k++){
                    Chessboardpoint* point = chessboard->getpoint(x-k, y+k);
                    if(point->get_state()==adverse_state){
                        continue;
                    }
                    else{
                        break;
                    }
                }
                if(x-k>=0 && y+k<=size-1 && chessboard->getpoint(x-k,y+k)->get_state() == state){
                    for(k = k-1; k >=1 ; k--){
                        chessboard->getpoint(x-k,y+k)->set_state(state);
                    }
                }
            }

            //右下翻转
            k = 1;
            if(y+k<=size-1 && x+k <=size-1 && chessboard->getpoint(x+k,y+k)->get_state() == adverse_state){
                for(;x+k <=size-1 && y+k<=size-1;k++){
                    Chessboardpoint* point = chessboard->getpoint(x+k, y+k);
                    if(point->get_state()==adverse_state){
                        continue;
                    }
                    else{
                        break;
                    }
                }
                if(x+k <=size-1 && y+k<=size-1 && chessboard->getpoint(x+k,y+k)->get_state() == state){
                    for(k = k-1; k >=1 ; k--){
                        chessboard->getpoint(x+k,y+k)->set_state(state);
                    }
                }
            }
            chessboard->getpoint(x,y)->set_state(state);
            return true;//成功翻转，返回true
        }
    }
    return false;//下棋位置无法翻转，即下棋的位置不是一个合法位置
}

void Othello::search_vali_locs()
{
     std::vector<std::tuple<int,int>>& vali_locs = gameturn==GameTurn::Black?black_vali_locs:white_vali_locs;
     vali_locs.clear();
     PointState state = gameturn==GameTurn::Black?PointState::Black:PointState::White;
     PointState adverse_state = gameturn==GameTurn::Black?PointState::White:PointState::Black;
     for(int i = 0 ; i < this->size ; i++){
        for(int j = 0 ; j < this->size; j++){

            Chessboardpoint* now_point = chessboard->getpoint(i, j);
            if(now_point->get_state()!=PointState::Blank){
                continue;
            }

            //上方向判断
            int k = i-1;
            if(k>=0 && chessboard->getpoint(k, j)->get_state()==adverse_state){
                for(; k>=0 ; k--){
                    Chessboardpoint* point = chessboard->getpoint(k, j);
                    if(point->get_state()==adverse_state){
                        continue;
                    }
                    else{
                        break;
                    }
                }
                if(k>=0&&chessboard->getpoint(k,j)->get_state() == state){
                    vali_locs.push_back(std::make_tuple(i,j));
                    continue;
                }
            }



            //下方向判断
            k = i+1;
            if(k<=size-1 && chessboard->getpoint(k, j)->get_state()==adverse_state){
                for(; k<=size-1 ; k++){
                    Chessboardpoint* point = chessboard->getpoint(k, j);
                    if(point->get_state()==adverse_state){
                        continue;
                    }
                    else{
                        break;
                    }
                }
                if(k<=size-1&&chessboard->getpoint(k,j)->get_state() == state){
                    vali_locs.push_back(std::make_tuple(i,j));
                    continue;
                }
            }



            //左方向判断
            k = j-1;
            if(k>=0 && chessboard->getpoint(i, k)->get_state()==adverse_state){
                for(; k>=0 ; k--){
                    Chessboardpoint* point = chessboard->getpoint(i, k);
                    if(point->get_state()==adverse_state){
                        continue;
                    }
                    else{
                        break;
                    }
                }
                if(k>=0&&chessboard->getpoint(i,k)->get_state() == state){
                    vali_locs.push_back(std::make_tuple(i,j));
                    continue;
                }
            }



            //右方向判断
            k = j+1;
            if(k<=size-1 && chessboard->getpoint(i, k)->get_state()==adverse_state){
                for(; k<=size-1 ; k++){
                    Chessboardpoint* point = chessboard->getpoint(i, k);
                    if(point->get_state()==adverse_state){
                        continue;
                    }
                    else{
                        break;
                    }
                }
                if(k<=size-1&&chessboard->getpoint(i,k)->get_state() == state){
                    vali_locs.push_back(std::make_tuple(i,j));
                    continue;
                }
            }


            //左上方向判断
            k = 1;
            if(j-k>=0 && i-k >=0 && chessboard->getpoint(i-k,j-k)->get_state() == adverse_state){
                for(;j-k>=0 && i-k >=0;k++){
                    Chessboardpoint* point = chessboard->getpoint(i-k, j-k);
                    if(point->get_state()==adverse_state){
                        continue;
                    }
                    else{
                        break;
                    }
                }
                if(j-k>=0 && i-k >=0 && chessboard->getpoint(i-k,j-k)->get_state() == state){
                    vali_locs.push_back(std::make_tuple(i,j));
                    continue;
                }
            }

            //左下方向判断
            k = 1;
            if(j-k>=0 && i+k <=size-1 && chessboard->getpoint(i+k,j-k)->get_state() == adverse_state){
                for(;j-k>=0 && i+k <=size-1;k++){
                    Chessboardpoint* point = chessboard->getpoint(i+k, j-k);
                    if(point->get_state()==adverse_state){
                        continue;
                    }
                    else{
                        break;
                    }
                }
                if(j-k>=0 && i+k <=size-1 && chessboard->getpoint(i+k,j-k)->get_state() == state){
                    vali_locs.push_back(std::make_tuple(i,j));
                    continue;
                }
            }


            //右上方向判断
            k = 1;
            if(j+k<=size-1 && i-k >=0 && chessboard->getpoint(i-k,j+k)->get_state() == adverse_state){
                for(;j+k<=size-1 && i-k >=0;k++){
                    Chessboardpoint* point = chessboard->getpoint(i-k, j+k);
                    if(point->get_state()==adverse_state){
                        continue;
                    }
                    else{
                        break;
                    }
                }
                if(j+k<=size-1 && i-k >=0 && chessboard->getpoint(i-k,j+k)->get_state() == state){
                    vali_locs.push_back(std::make_tuple(i,j));
                    continue;
                }
            }


            //右下方向判断
            k = 1;
            if(j+k<=size-1 && i+k <=size-1 && chessboard->getpoint(i+k,j+k)->get_state() == adverse_state){
                for(;j+k<=size-1 && i+k <=size-1;k++){
                    Chessboardpoint* point = chessboard->getpoint(i+k, j+k);
                    if(point->get_state()==adverse_state){
                        continue;
                    }
                    else{
                        break;
                    }
                }
                if(j+k<=size-1 && i+k <=size-1 && chessboard->getpoint(i+k,j+k)->get_state() == state){
                    vali_locs.push_back(std::make_tuple(i,j));
                    continue;
                }
            }



        }
     }
}

Gamestate Othello::Ultimate_judgment()
{
    this->search_vali_locs();
    if(gameturn == GameTurn::Black){//查找白色执子方的可下点
        if(black_vali_locs.size()==0){
            //如果白色方无子可下
            this->gameturn = GameTurn::White;//不管是否需要查子计算输赢，都可以切换为黑色方执子
            this->search_vali_locs();//查找黑色执子时的可下点
            if(white_vali_locs.size()==0){//说明黑色也无子可下，计数判断输赢
                int white_numbers=0;
                int black_numbers=0;
                for(int i = 0 ; i < size ; i++){
                    for(int j = 0 ; j < size ; j++){
                        if(chessboard->getpoint(i,j)->get_state() == PointState::White){
                            white_numbers++;
                        }
                        if(chessboard->getpoint(i,j)->get_state() == PointState::Black){
                            black_numbers++;
                        }
                    }
                }
                if(white_numbers > black_numbers){
                    return Gamestate::White_win;
                }
                else if(white_numbers < black_numbers){
                    return Gamestate::Black_win;
                }
                else{
                    return Gamestate::Dogfall;
                }
            }
            else{
                return Gamestate::Keeping_battle;
            }
        }
        else{
            return Gamestate::Keeping_battle;
        }
    }
    else if(gameturn == GameTurn::White){
        if(white_vali_locs.size()==0){
            this->gameturn = GameTurn::Black;
            this->search_vali_locs();
            if(black_vali_locs.size()==0){
                int white_numbers=0;
                int black_numbers=0;
                for(int i = 0 ; i < size ; i++){
                    for(int j = 0 ; j < size ; j++){
                        if(chessboard->getpoint(i,j)->get_state() == PointState::White){
                            white_numbers++;
                        }
                        if(chessboard->getpoint(i,j)->get_state() == PointState::Black){
                            black_numbers++;
                        }
                    }
                }
                if(white_numbers > black_numbers){
                    return Gamestate::White_win;
                }
                else if(white_numbers < black_numbers){
                    return Gamestate::Black_win;
                }
                else{
                    return Gamestate::Dogfall;
                }
            }
            else{
                return Gamestate::Keeping_battle;
            }
        }
        else{
            return Gamestate::Keeping_battle;
        }
    }
    return Gamestate::Keeping_battle;
}

MementIF *Othello::create_memento()
{
    return static_cast<MementIF*>(new OthelloMement(chessboard, gameturn, gamestate));
}

void Othello::restore_from_memento(MementIF * mementif)
{
    OthelloMement* othellomement = static_cast<OthelloMement*>(mementif);
    auto [chessboard, gameturn, gamestate] = othellomement->get_state();
    this->chessboard = chessboard;
    this->gameturn = gameturn;
            this->gamestate = gamestate;
}

void Othello::reset()
{
    ConstructGame::reset();
    chessboard->getpoint(size/2-1,size/2-1)->set_state(PointState::White);
    chessboard->getpoint(size/2,size/2)->set_state(PointState::White);
    chessboard->getpoint(size/2-1,size/2)->set_state(PointState::Black);
    chessboard->getpoint(size/2,size/2-1)->set_state(PointState::Black);
}


