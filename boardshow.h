#ifndef BOARDSHOW_H
#define BOARDSHOW_H

#include <QWidget>
#include "Chessboard.h"
#include "consturtgame.h"
#include <QMouseEvent>
#include <vector>
#include "PointState.h"
#include <QPushButton>
#include <QStatusBar>
#include <QMessageBox>
#include <string>

class User_info{
public:
    char name[50];
    int total_games;
    int win_games;
    int loss_games;
};

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
    QPushButton* button_unundo;
    QStatusBar* statusbar;
    QPushButton* button_surrender;
    QStatusBar* username;
    QStatusBar* userwinratio;
    User_info user_info;

public:
    explicit BoardShow(QWidget *parent = nullptr);
    BoardShow(int size,std::vector<std::vector<Chessboardpoint*>>, int d=40);
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    //void change_turn();
    void showboard(std::vector<std::vector<Chessboardpoint*>> chessboard, GameTurn gameturn, Gamestate gamestate, User_info user_info);
    void closeEvent(QCloseEvent *event) override;
signals:
    void emit_setsig(int x, int y);
    void emit_undosig();
    void emit_closesig();
    void emit_save();
    void emit_reset();
    void emit_surrender();
    void emit_Ultimate_judgement();
    void emit_unundosig();
};

#endif // BOARDSHOW_H
