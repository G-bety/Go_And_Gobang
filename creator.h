#ifndef CREATOR_H
#define CREATOR_H
#include "Game.h"
#include "Go.h"
#include "Gobang.h"

class Creator
{
public:
    Creator();
    virtual Game* product(int size);
};

class Go_Creator:public Creator{
    Game * product(int size) override;
};

class Gobang_Creator:public Creator{
    Game * product(int size) override;
};


#endif // CREATOR_H
