#ifndef GOBOARDSHOW_H
#define GOBOARDSHOW_H
#include "boardshow.h"
#include <tuple>

class Goboardshow:public BoardShow
{
   Q_OBJECT
protected:
    QPushButton* button_skip;
    QPushButton* button_getmash;

public:
    Goboardshow(int size,std::vector<std::vector<Chessboardpoint*>>, int d=40);
public:
    void showmash(std::tuple<int,int>);
signals:
    void emit_setsig(int x, int y);
    void emit_skipsig();
    void emit_closesig();
    void emit_getmashsig();
};

#endif // GOBOARDSHOW_H
