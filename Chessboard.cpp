#include "Chessboard.h"
Chessboard::Chessboard(int size):size(size),points(size, std::vector<Chessboardpoint*>(size, nullptr)){
    for(int i = 0; i < size; i++){
        for(int j = 0 ; j < size; j++){
            points[i][j] = new Chessboardpoint(i, j);
        }
    }
    for(int i = 0; i < size; i++){
        for(int j = 0 ; j < size; j++){
            if(i-1>=0){
                points[i][j]->up = points[i-1][j];
            }
            if(i+1<size){
                points[i][j]->down = points[i+1][j];
            }
            if(j-1>=0){
                points[i][j]->left = points[i][j-1];
            }
            if(j+1<size){
                points[i][j]->right = points[i][j+1];
            }
        }
    }
}

Chessboardpoint* Chessboard::getpoint(int x,int y){
    return points[x][y];
}

Chessboard::Chessboard(const Chessboard &other):size(other.size),points(other.size, std::vector<Chessboardpoint*>(other.size, nullptr))
{
    for(int i = 0; i < size; i++){
        for(int j = 0 ; j < size; j++){
            points[i][j] = new Chessboardpoint(i, j);
            points[i][j]->state = other.points[i][j]->get_state();
        }
    }
    for(int i = 0; i < size; i++){
        for(int j = 0 ; j < size; j++){
            if(i-1>=0){
                points[i][j]->up = points[i-1][j];
            }
            if(i+1<size){
                points[i][j]->down = points[i+1][j];
            }
            if(j-1>=0){
                points[i][j]->left = points[i][j-1];
            }
            if(j+1<size){
                points[i][j]->right = points[i][j+1];
            }
        }
    }
}

void Chessboard::savetofile(std::ofstream& outfile)
{
    outfile.write(reinterpret_cast<char *>(&this->size), sizeof(this->size));
    PointState temp;
    for(int i = 0 ; i < this->size ; i++){
        for(int j = 0 ; j < this->size;j++){
            temp = this->points[i][j]->get_state();
            outfile.write(reinterpret_cast<char *>(&temp), sizeof(temp));
        }
    }
}

void Chessboard::readfromfile(std::ifstream& infile)
{
    infile.read(reinterpret_cast<char *>(&this->size), sizeof(this->size));
    PointState temp;
    for(int i = 0 ; i < this->size ; i++){
        for(int j = 0 ; j < this->size;j++){
            infile.read(reinterpret_cast<char *>(&temp), sizeof(temp));
            this->points[i][j]->set_state(temp);
        }
    }
}

std::vector<std::vector<Chessboardpoint*>> Chessboard::get_points(){
    return points;
}
