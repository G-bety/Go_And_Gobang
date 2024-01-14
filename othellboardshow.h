#ifndef OTHELLBOARDSHOW_H
#define OTHELLBOARDSHOW_H


#include "boardshow.h"
class Othellboardshow:public BoardShow
{
public:
    Othellboardshow(int size,std::vector<std::vector<Chessboardpoint*>>, int d=40);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);

    // QWidget interface
protected:
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // OTHELLBOARDSHOW_H
