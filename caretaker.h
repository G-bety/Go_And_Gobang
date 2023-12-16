#ifndef CARETAKER_H
#define CARETAKER_H
#include <vector>
#include "MomentIF.h"
#include <fstream>

class CareTaker
{
public:
    CareTaker();
    virtual MomentIF* getMemento(int i);
    virtual MomentIF* addMemento(MomentIF*, int);
    virtual void savetofile(std::ofstream& outfile);
    virtual void readfromfile(std::ifstream& infile, int)=0;
protected:
    std::vector<MomentIF*> mementolist;
};

#endif // CARETAKER_H
