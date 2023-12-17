#ifndef CARETAKER_H
#define CARETAKER_H
#include <vector>
#include "MomentIF.h"
#include <fstream>
#include "operationwithfile.h"

class CareTaker
{
public:
    CareTaker();
    virtual MementIF* getMemento(int i);
    virtual MementIF* addMemento(MementIF*, int);
    virtual void savetofile(std::ofstream& outfile);
    virtual void readfromfile(std::ifstream& infile, int)=0;
protected:
    std::vector<MementIF*> mementolist;
};

#endif // CARETAKER_H
