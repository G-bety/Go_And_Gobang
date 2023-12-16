#ifndef MOMENTIF_H
#define MOMENTIF_H
#include <fstream>

class MomentIF{
public:
    virtual void savetofile(std::ofstream& outfile)=0;
    virtual void readfromfile(std::ifstream& infile)=0;
};

#endif // MOMENTIF_H
