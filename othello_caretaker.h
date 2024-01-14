#ifndef OTHELLO_CARETAKER_H
#define OTHELLO_CARETAKER_H

#include "caretaker.h"


class Othello_CareTaker:public CareTaker
{
public:
    Othello_CareTaker();

    // CareTaker interface
public:
    void readfromfile(std::ifstream &infile, int);
};

#endif // OTHELLO_CARETAKER_H
