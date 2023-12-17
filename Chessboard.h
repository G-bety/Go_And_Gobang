#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <vector>
#include "Chessboardpoint.h"
#include <fstream>
#include <operationwithfile.h>

class DFS_tool;

class Chessboard:public OperationWithFile
{
private:
    /* data */
    int size;//棋局大小
    std::vector<std::vector<Chessboardpoint*>> points;//棋局中的点集合

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

    Chessboardpoint* getpoint(int x, int y);//给定位置坐标返回交叉点信息

    Chessboard(const Chessboard& other);

    void savetofile(std::ofstream& outfile)override;//存储到文件中的操作

    void readfromfile(std::ifstream& infile)override;//从文件中读取的操作
};
#endif // CHESSBOARD_H
