#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <vector>
#include "Chessboardpoint.h"
#include <fstream>

class DFS_tool;

class Chessboard
{
private:
    /* data */
    int size;
    std::vector<std::vector<Chessboardpoint*>> points;

public:
    Chessboard(int size);
    std::vector<std::vector<Chessboardpoint*>> get_points();

    ~Chessboard(){
        for(auto row:points){
            for(auto column:row){
                delete column;
            }
        }
    }
    void initChessboard(){
        for(auto row:points){
            for(auto column:row){
                column->set_state(PointState::Blank);
            }
        }
    }

    Chessboardpoint* getpoint(int x, int y);

    Chessboard(const Chessboard& other);

    void savetofile(std::ofstream& outfile);

    void readfromfile(std::ifstream& infile);
};
#endif // CHESSBOARD_H
