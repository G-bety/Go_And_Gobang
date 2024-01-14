#include "Go.h"


/**
 * @brief Go::set
 * @param x
 * @param y
 * @param pointstate
 * @param turn
 * @return true表示成功下子，false表示下子失败
 */
bool Go::set(int x, int y, PointState pointstate){
    if(x==-1 && y==-1){
        return true;
    }
    Chessboardpoint* point = this->chessboard->getpoint(x,y);
    if(point->get_state()== PointState::Blank){//如果此处还未落子，则可以下在此处

        point->set_state(pointstate);//先下子，不管有没有气

        bool has_captured = false;
        //判断是否可以提子，如果可以提子的话就可以不用判断是否有气就可以在此位置下子
        if(point->get_up()!=nullptr && point->get_up()->get_state()!=pointstate && (point->get_up()->get_state()!=PointState::Blank)){
            vector<Chessboardpoint*> vec;
            if(!liberty(point->get_up(), vec)){
                capture(vec);
                has_captured = true;
            }
        }

        if(point->get_down()!=nullptr && point->get_down()->get_state()!=pointstate && (point->get_down()->get_state()!=PointState::Blank)){
            vector<Chessboardpoint*> vec;
            if(!liberty(point->get_down(), vec)){
                capture(vec);
                has_captured = true;
            }
        }

        if(point->get_left()!=nullptr && point->get_left()->get_state()!=pointstate && (point->get_left()->get_state()!=PointState::Blank)){
            vector<Chessboardpoint*> vec;
            if(!liberty(point->get_left(), vec)){
                capture(vec);
                has_captured = true;
            }
        }

        if(point->get_right()!=nullptr && point->get_right()->get_state()!=pointstate && (point->get_right()->get_state()!=PointState::Blank)){
            vector<Chessboardpoint*> vec;
            if(!liberty(point->get_right(), vec)){
                capture(vec);
                has_captured = true;
            }
        }


        //如果没有提子，则需要进一步判断当前是否有气
        if(has_captured == false){
            if(!liberty(x,y)){
                point->set_state(PointState::Blank);
                return false;
            }
        }
            //如果不可以提子，此处不可以下子

    }
    else{
        return false;
    }
    return true;
}


MementIF *Go::create_memento()
{
     return static_cast<MementIF*>(new GoMement(chessboard, gameturn, gamestate));
}

void Go::restore_from_memento(MementIF* IFgomoment)
{
    GoMement* gomoment = static_cast<GoMement*>(IFgomoment);
    auto [firstElement, secondElement, thirdElement] = gomoment->get_state();
    this->chessboard = firstElement;
    this->gameturn = secondElement;
    this->gamestate = thirdElement;
}


std::tuple<int,int> Go::getmash(){
    int white_eye=0;//白子目数
    int black_eye=0;//黑子目数
    int king=0;//单官数目
    unordered_set<Chessboardpoint*>  auxiliary;
    std::vector<std::vector<Chessboardpoint*>> points = this->chessboard->get_points();
    for(int i = 0 ; i < size ; i++){
        for(int j = 0 ; j < size ; j++){
            Chessboardpoint* first_point = points[i][j];
            if(first_point->get_state()==PointState::Blank&&auxiliary.count(first_point)==0){
                queue<Chessboardpoint*> Q;
                Q.push(first_point);
                int count = 1;//记录这次遍历的连成块的空白子数目
                int around_white=0;
                int around_black=0;
                auxiliary.insert(first_point);
                while(!Q.empty()){
                    auto now = Q.front();
                    //auxiliary.insert(now);
                    Q.pop();
                    if(now->get_up() == nullptr){//如果为空，什么也不做

                    }
                    else if(now->get_up()->get_state() == PointState::Blank && auxiliary.count(now->get_up())==0){
                        Q.push(now->get_up());
                        auxiliary.insert(now->get_up());
                        count++;
                    }
                    else if(now->get_up()->get_state() == PointState::Black){
                        around_black++;
                    }
                    else if(now->get_up()->get_state() == PointState::White){
                        around_white++;
                    }

                    if(now->get_down() == nullptr){//如果为空，什么也不做

                    }
                    else if(now->get_down()->get_state() == PointState::Blank && auxiliary.count(now->get_down())==0){
                        Q.push(now->get_down());
                        auxiliary.insert(now->get_down());
                        count++;
                    }
                    else if(now->get_down()->get_state() == PointState::Black){
                        around_black++;
                    }
                    else if(now->get_down()->get_state() == PointState::White){
                        around_white++;
                    }


                    if(now->get_left() == nullptr){//如果为空，什么也不做

                    }
                    else if(now->get_left()->get_state() == PointState::Blank && auxiliary.count(now->get_left())==0){
                        Q.push(now->get_left());
                        auxiliary.insert(now->get_left());
                        count++;
                    }
                    else if(now->get_left()->get_state() == PointState::Black){
                        around_black++;
                    }
                    else if(now->get_left()->get_state() == PointState::White){
                        around_white++;
                    }


                    if(now->get_right() == nullptr){//如果为空，什么也不做

                    }
                    else if(now->get_right()->get_state() == PointState::Blank && auxiliary.count(now->get_right())==0){
                        Q.push(now->get_right());
                        auxiliary.insert(now->get_right());
                        count++;
                    }
                    else if(now->get_right()->get_state() == PointState::Black){
                        around_black++;
                    }
                    else if(now->get_right()->get_state() == PointState::White){
                        around_white++;
                    }
                }
                if(around_black == 0){
                    white_eye += count;
                }
                else if(around_white == 0){
                    black_eye += count;
                }
                else{
                    king += count;
                }
            }
        }
    }
    for(int i = 0 ; i < size ; i++){
        for(int j = 0 ; j < size ; j++){
            if(points[i][j]->get_state() == PointState::White){
                white_eye++;
            }
            else if(points[i][j]->get_state() == PointState::Black){
                black_eye++;
            }
        }
    }
    return std::make_tuple(black_eye,white_eye);
}

Gamestate Go::Ultimate_judgment(){
        return Gamestate::Keeping_battle;
}

Gamestate Go::GoUltimate_judgment()
{
    std::tuple<int,int> mashes = getmash();
    int count_black = std::get<0>(mashes);
    int count_white = std::get<1>(mashes);
    QString str;
    if(count_black-6.5 < count_white){
        this->gamestate = Gamestate::White_win;
    }
    else if(count_black-6.5 > count_white) {
        this->gamestate = Gamestate::Black_win;
    }
    else{
        this->gamestate = Gamestate::Keeping_battle;
    }
}

bool Go::capture(const vector<Chessboardpoint*>& vec){
    for(auto it = vec.begin(); it != vec.end(); it++){
        (*it)->set_state(PointState::Blank);
    }
}


bool Go::liberty(Chessboardpoint* point, vector<Chessboardpoint*>& capture_points){
    PointState nowstate = point->get_state();
    if(nowstate==PointState::Blank) return true;
    unordered_set<Chessboardpoint*>  auxiliary;//使用辅助集合帮助对棋盘进行BFS
    queue<Chessboardpoint*> Q;
    Q.push(point);
    auxiliary.insert(point);
    while(!Q.empty()){
        auto now = Q.front();
        Q.pop();
        if(now->get_state() == PointState::Blank) return true;//说明有气，返回true
        if(now->get_state() != nowstate) continue;//说明非相连的子，忽略
        capture_points.push_back(now);
        if( now->get_down() != nullptr && auxiliary.count(now->get_down())==0){
            Q.push(now->get_down());
            auxiliary.insert(now->get_down());
        }
        if(now->get_right()!=nullptr&& auxiliary.count(now->get_right())==0){
            Q.push(now->get_right());
            auxiliary.insert(now->get_right());
        }
        if(now->get_up()!=nullptr && auxiliary.count(now->get_up())==0){
            Q.push(now->get_up());
            auxiliary.insert(now->get_up());
        }
        if(now->get_left()!=nullptr && auxiliary.count(now->get_left())==0){
            Q.push(now->get_left());
            auxiliary.insert(now->get_left());
        }
    }
    return false;
}

Go::Go(int size):ConstructGame(size){
    caretaker = new Go_CareTaker();
}

bool Go::liberty(int x, int y){
    vector<Chessboardpoint*> vec;
    return liberty(chessboard->getpoint(x,y), vec);
}


bool Go::liberty(int x, int y, vector<Chessboardpoint*>& capture_points){

    return liberty(chessboard->getpoint(x,y), capture_points);
}

