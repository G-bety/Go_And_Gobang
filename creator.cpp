#include "creator.h"


Creator::Creator()
{

}

Game *Creator::product(int size)
{
    return new Go(size);
}



Game *Gobang_Creator::product(int size)
{
    return new Gobang(size);
}

Game *Go_Creator::product(int size)
{
    return new Go(size);
}
