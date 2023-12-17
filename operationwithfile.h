#ifndef OPERATIONWITHFILE_H
#define OPERATIONWITHFILE_H
#include <QString>
#include <fstream>

class OperationWithFile
{
public:
    OperationWithFile();
    virtual void savetofile(std::ofstream& filePath)=0;
    virtual void readfromfile(std::ifstream& filePath)=0;
};

#endif // OPERATIONWITHFILE_H
