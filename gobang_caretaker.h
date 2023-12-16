#ifndef GOBANG_CARETAKER_H
#define GOBANG_CARETAKER_H
#include "caretaker.h"
#include "Chessboard.h"


class Gobang_CareTaker:public CareTaker
{
public:
    Gobang_CareTaker();
    void readfromfile(std::ifstream &infile, int) override;
};

#endif // GOBANG_CARETAKER_H
