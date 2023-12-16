#ifndef GO_CARETAKER_H
#define GO_CARETAKER_H
#include "caretaker.h"
#include "Chessboard.h"

class Go_CareTaker:public CareTaker
{
public:
    Go_CareTaker();
    void readfromfile(std::ifstream &infile,int) override;
};

#endif // GO_CARETAKER_H
