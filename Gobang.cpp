#include "Gobang.h"
#include <tuple>

/**
 * @param turn 下一步轮到的下棋者
*/

bool Gobang::set(int x, int y, PointState pointstate){//此处不需要判断游戏的输赢，判断游戏输赢的函数由Ultimate_judgment实现
    this->gameturn = gameturn;
    Chessboardpoint* point = this->chessboard->getpoint(x,y);
    if(point->get_state()!=PointState::Blank) return false;
    point->set_state(pointstate);
    last_piece = std::make_tuple(x,y);
    this->gamestate =  this->Ultimate_judgment();
    return true;
}


void Gobang::reset(){
    chessboard->initChessboard();
    this->last_piece = std::make_tuple(-1,-1);
    this->gamestate = Gamestate::Keeping_battle;
    this->gameturn = GameTurn::Black;
}

Gobang::Gobang(int size):ConstructGame(size)
{
    caretaker = new Gobang_CareTaker();
}

MementIF* Gobang::create_memento()
{
    return static_cast<MementIF*>(new GobangMement(chessboard, last_piece, gameturn, gamestate));
}

void Gobang::restore_from_memento(MementIF * momentIF)
{
    GobangMement* gobangmoment = static_cast<GobangMement*>(momentIF);
    auto [chessboard, last_piece, gameturn, state] = gobangmoment->get_state();
    this->chessboard = chessboard;
    this->last_piece = last_piece;
    this->gameturn = gameturn;
    this->gamestate = state;
}

void Gobang::savetofile(std::ofstream & outfile)
{
        ConstructGame::savetofile(outfile);
        outfile.write(reinterpret_cast<char*>(&last_piece), sizeof(last_piece));
}

void Gobang::readfromfile(std::ifstream & infile)
{
       ConstructGame::readfromfile(infile);
       infile.read(reinterpret_cast<char*>(&last_piece),sizeof(last_piece));
}



Gamestate Gobang::Ultimate_judgment(){//终局判断
    int x = std::get<0>(last_piece);
    int y = std::get<1>(last_piece);
    PointState nowstate = chessboard->getpoint(x,y)->get_state();
    Gamestate ret;

    if(nowstate==PointState::Black){
        ret = Gamestate::Black_win;
    }
    else{
        ret = Gamestate::White_win;
    }

    //四个方向依次判断
    //垂直方向
    int samenumber=0;
    for(int i=x-1; i>=0 && chessboard->getpoint(i,y)->get_state()==nowstate; i--){
        samenumber++;
    }
    for(int i=x+1; i<size && chessboard->getpoint(i,y)->get_state()==nowstate; i++){
        samenumber++;
    }
    if(samenumber+1 >=5){
        return ret;
    }

    //水平方向
    samenumber = 0;
    for(int j=y-1;j>=0 && chessboard->getpoint(x,j)->get_state()==nowstate; j--){
        samenumber++;
    }
    for(int j=y+1;j<size && chessboard->getpoint(x,j)->get_state()==nowstate; j++){
        samenumber++;
    }
    if(samenumber+1 >=5){
        return ret;
    }


    //-45°方向
    samenumber = 0;
    int i,j;
    for(i=x-1,j=y-1; i>=0 && j >=0 && chessboard->getpoint(i,j)->get_state()==nowstate;i--,j--){
        samenumber++;
    }

    for(i=x+1,j=y+1; i<size && j <size && chessboard->getpoint(i,j)->get_state()==nowstate;i++,j++){
        samenumber++;
    }
    if(samenumber+1 >=5){
        return ret;
    }

    //45°方向

    samenumber = 0;
    for(i=x-1,j=y+1; i>=0 && j<size && chessboard->getpoint(i,j)->get_state()==nowstate;i--,j++){
        samenumber++;
    }

    for(i=x+1,j=y-1; i<size && j>=0 && chessboard->getpoint(i,j)->get_state()==nowstate;i++,j--){
        samenumber++;
    }
    if(samenumber+1 >=5){
        return ret;
    }

    //如果没有子可下，返回平局
    for(int i=0 ; i < size ; i++){
        for (int j = 0 ; j < size ; j++){
            if(chessboard->getpoint(i,j)->get_state()==PointState::Blank){
                return Gamestate::Keeping_battle;
            }
        }
    }

    return Gamestate::Dogfall;
}

