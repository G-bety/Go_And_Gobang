#ifndef GOBOARDSHOW_H
#define GOBOARDSHOW_H
#include "boardshow.h"
#include <tuple>

class Goboardshow:public BoardShow
{
   Q_OBJECT
protected:
    void onButton_getmash_Clicked();
    void onButton_skip_Clicked();
    QPushButton* button_skip;
    QPushButton* button_getmash;

public:
    Goboardshow(int size,std::vector<std::vector<Chessboardpoint*>>, int d=40);
public slots:
    void showmash(std::tuple<int,int>);
signals:
    void signalset(int x, int y);
    void pro_skip();
    void winclose();
    void pro_getmash();
};

#endif // GOBOARDSHOW_H
