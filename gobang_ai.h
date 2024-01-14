#ifndef GOBANG_AI_H
#define GOBANG_AI_H

#include "Gobang.h"
#include "PointState.h"

class Gobang_AI:public Gobang
{
public:
    Gobang_AI(int size);
    bool set(int,int)override;
    bool undo()override;
    bool unundo()override;
    virtual bool autoset(int , int, PointState)=0;
};

class Gobang_AI_1:public Gobang_AI
{
public:
    Gobang_AI_1(int size);
    virtual bool autoset(int , int, PointState)override;

};

class Gobang_AI_2:public Gobang_AI
{
public:
    Gobang_AI_2(int size);
    virtual bool autoset(int , int, PointState)override;
private:
    int get_bond_num(int x, int y, PointState pointstate);
};


#endif // GOBANG_AI_H
