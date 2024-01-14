#ifndef CONSTURTGAME_H
#define CONSTURTGAME_H
#include "Chessboard.h"
#include "GameTurn.h"
#include "Gamestate.h"
#include <QWidget>
#include "caretaker.h"
#include <iostream>
#include <fstream>
#include <QString>
#include "operationwithfile.h"

class ConstructGame:public OperationWithFile
{
    // Q_OBJECT

  private:
      /* data */

  protected:
      Chessboard* chessboard;
      virtual bool set(int x, int y, PointState pointstate)=0;
      int size;
      int step=0;
      int observe_step=0;
      GameTurn gameturn = GameTurn::Black;  //下一步应该走棋的子
      Gamestate gamestate = Gamestate::Keeping_battle;
      CareTaker* caretaker;

  public:
      ConstructGame(int size);
      virtual ~ConstructGame();
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
      virtual void reset();
      virtual Chessboard* get_chessboard(){
          return chessboard;
      }

      virtual GameTurn get_gameturn(){
          return this->gameturn;
      }

      virtual Gamestate get_gamestatu(){
          return this->gamestate;
      }

      /**
       * @brief create_memento理论上这个函数永不会被调用，只有它的继承子类的重写才会有作用
       * @return
       */
      virtual MementIF* create_memento()=0;
      /**
       * @brief restore_from_memento理论上这个函数永不会被调用，只有它的继承子类的重写才会有作用
       */
      virtual void restore_from_memento(MementIF*)=0;
      virtual void savetofile(std::ofstream&)override;
      virtual void readfromfile(std::ifstream&)override;
      virtual void surrender();
};

#endif // CONSTURTGAME_H
