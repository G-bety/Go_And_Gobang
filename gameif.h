#ifndef GAMEIF_H
#define GAMEIF_H
#include "Chessboard.h"
#include "GameTurn.h"
#include "Gamestate.h"
#include <QWidget>
#include "caretaker.h"
#include <iostream>
#include <fstream>
#include <QString>

class GameIF
{
protected:
    Chessboard* chessboard;
    virtual bool set(int x, int y, PointState pointstate)=0;
    int size;
    int step=0;
    GameTurn turn = GameTurn::Black;  //下一步应该走棋的子
    Gamestate gamestate = Gamestate::Keeping_battle;
    CareTaker* caretaker;
public:
    GameIF();

};

#endif // GAMEIF_H
