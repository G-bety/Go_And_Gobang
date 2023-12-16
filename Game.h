#ifndef GAME_H
#define GAME_H

#include "Chessboard.h"
#include "GameTurn.h"
#include "Gamestate.h"
#include <QWidget>
#include "caretaker.h"
#include <iostream>
#include <fstream>
#include <QString>

class Game
{
   // Q_OBJECT

private:
    /* data */

protected:
    Chessboard* chessboard;
    int size;
    int step=0;
    GameTurn turn = GameTurn::Black;  //下一步应该走棋的子
    Gamestate gamestate = Gamestate::Keeping_battle;
    virtual bool set(int x, int y, PointState pointstate)=0;
    CareTaker* caretaker;

public:
    Game(int size);
    virtual ~Game();
    /**
     * @brief Game::set
     * @param x
     * @param y
     * @param pointstate
     * @param turn
     * @return true表示成功下子，false表示下子失败
     */
    /**
     * @brief set 在围棋中如果输入（1-，-1）表示此步不下
     * @param x
     * @param y
     * @return
     */
    virtual bool set(int x, int y);
    virtual bool undo();
    virtual bool unundo();
    virtual Gamestate Ultimate_judgment()=0;
    virtual void reset()=0;
    virtual Chessboard* get_chessboard(){
        return chessboard;
    }

    virtual GameTurn get_gameturn(){
        return this->turn;
    }

    virtual Gamestate get_gamestatu(){
        return this->gamestate;
    }

    /**
     * @brief create_memento理论上这个函数永不会被调用，只有它的继承子类的重写才会有作用
     * @return
     */
    virtual MomentIF* create_memento();
    /**
     * @brief restore_from_memento理论上这个函数永不会被调用，只有它的继承子类的重写才会有作用
     */
    virtual void restore_from_memento(MomentIF*);
    virtual void savetofile(std::ofstream&);
    virtual void readfromfile(std::ifstream&);
};

#endif // GAME_H
