#ifndef CREATOR_H
#define CREATOR_H
#include "consturtgame.h"
#include "Go.h"
#include "Gobang.h"
#include "boardshow.h"
#include "consturtgame.h"
#include "goboardshow.h"
#include "select_sizeif.h"
#include "select_gosize.h"
#include "select_gobangsize.h"
#include "gobangboardshow.h"
#include "othello.h"
#include "othellboardshow.h"
#include "select_othellosize.h"
#include <QDir>
class Controller;
class Creator
{
public:
    Creator();
    virtual ConstructGame* game_product(int size)=0;//返回创建的对局对象
    virtual QDir* dir_product(const QDir&)=0;//返回文件存储路径
    virtual BoardShow* boardshow_product(int size , ConstructGame* game ,Controller* controller)=0;//返回创建的用来展示棋盘的对象
    virtual Select_sizeIF* select_size_product()=0;//返回创建的选择棋局大小的对象
};

class Go_Creator:public Creator{
    ConstructGame * game_product(int size) override;
    QDir * dir_product(const QDir&) override;
    BoardShow * boardshow_product(int size , ConstructGame* game ,Controller* controller) override;
    Select_sizeIF * select_size_product() override;
};

class Gobang_Creator:public Creator{
    ConstructGame * game_product(int size) override;
    QDir * dir_product(const QDir&) override;
    BoardShow * boardshow_product(int size , ConstructGame* game ,Controller* controller) override;
    Select_sizeIF * select_size_product() override;
};

class Othello_Creator:public Creator{
    ConstructGame * game_product(int size) override;
    QDir * dir_product(const QDir&) override;
    BoardShow * boardshow_product(int size , ConstructGame* game ,Controller* controller) override;
    Select_sizeIF * select_size_product() override;
};

class Gobang_AI_1_Creator:public Gobang_Creator{
    ConstructGame * game_product(int size) override;
};


class Gobang_AI_2_Creator:public Gobang_Creator{
    ConstructGame * game_product(int size) override;
};



#endif // CREATOR_H
