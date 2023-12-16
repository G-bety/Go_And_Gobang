#ifndef BOARDSHOW_H
#define BOARDSHOW_H

#include <QWidget>
#include "Chessboard.h"
#include "Game.h"
#include <QMouseEvent>
#include "Game.h"
#include <vector>
#include "Game.h"
#include "PointState.h"
#include <QPushButton>
#include <QStatusBar>
#include <QMessageBox>

class BoardShow : public QWidget
{
    Q_OBJECT

protected:
    int size;//棋盘规模
    int d;//棋子大小
    std::vector<std::vector<Chessboardpoint*>> points;
    GameTurn gameturn;
    Gamestate gamestate;
    QPushButton* button_undo;
    QPushButton* button_reset;
    QStatusBar* statusbar;
    void onButton_undo_Clicked();
     void onButton_reset_Clicked();

public:
    explicit BoardShow(QWidget *parent = nullptr);
    BoardShow(int size,std::vector<std::vector<Chessboardpoint*>>, int d=40);
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    //void change_turn();
    void showboard(std::vector<std::vector<Chessboardpoint*>> chessboard, GameTurn gameturn, Gamestate gamestate);
    void closeEvent(QCloseEvent *event) override;
signals:
    void signalset(int x, int y);
    void button_undo_clicked();
    void winclose();
    void pro_save();
    void pro_reset();
};

#endif // BOARDSHOW_H
