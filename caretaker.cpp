#include "caretaker.h"
#include <fstream>

CareTaker::CareTaker()
{

}

MementIF *CareTaker::getMemento(int i)
{
    std::printf("%d\n",mementolist.size()-1);
    if(i>mementolist.size()-1){
        std::printf("出现了非预期情况");
        return nullptr;
    }
    return this->mementolist[i];
}

MementIF *CareTaker::addMemento(MementIF * moment, int index)
{
    if(index <mementolist.size()){
        auto old_moment = mementolist[index];
        delete old_moment;
        mementolist[index] = moment;
    }
    else if(index == mementolist.size()){
        mementolist.push_back(moment);
    }
    else{
        std::printf("出现了非预期情况");
        return nullptr;
    }
}

void CareTaker::savetofile(std::ofstream& outfile)
{
    int size = mementolist.size();
    outfile.write(reinterpret_cast<char *>(&size),sizeof (size));
    for(int i = 0; i < size; i++){
        mementolist[i]->savetofile(outfile);
    }
}

