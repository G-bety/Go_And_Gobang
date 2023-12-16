#ifndef GOBANGBOARDSHOW_H
#define GOBANGBOARDSHOW_H
#include "boardshow.h"

class GobangBoardshow:public BoardShow
{
public:
    GobangBoardshow(int size, std::vector<std::vector<Chessboardpoint *>> points, int d=40);
};

#endif // GOBANGBOARDSHOW_H
