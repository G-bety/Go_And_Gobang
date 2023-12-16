#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QWidget>
#include "boardshow.h"
#include "Game.h"
#include "Go.h"
#include "Gobang.h"
#include <vector>
#include <experimental/filesystem>
#include "minwindow.h"
#include "select_neworold.h"
#include "select_gobangsize.h"
#include "select_gosize.h"
#include "goboardshow.h"
#include <QDir>
#include <QFile>
#include <QListView>
#include <QStringListModel>
#include <oldgamelistshow.h>
#include <QDateTime>
#include "gobangboardshow.h"

class Controller:public QWidget
{
    Q_OBJECT

public:
    Controller(QDir);
    ~Controller();
private:
    MinWindow* minwindow;
    Select_neworold* select_neworold;
    Select_sizeIF* select_size;
    BoardShow* boardshow;
    Game* game;
    int size;
    Creator* creator;
    QDir storedir;
    QString current_gamestore_name;
    OldgameListShow* oldgamelist;
    void getboard_and_show();
    void make_board();
    void savetofile(QString filePath);


private slots:
    void setchessboardpoint(int x, int y);//<得到来自Boardshow的

    void undo_operation();

    void skip_operation();

    void save_current_game();

    void readfromfile(QString filePath);

    void close();

    void get_creator(Creator*);

    void process_new_game();//处理创建新游戏的信号

    void process_load_old_game();

    void process_sizeinfo_and_makeboard(int size);

    void process_boardclose();

    void process_selectsizeclose();

    void process_selectneworoldclose();

    void load_old_game(QString filename);

    void process_getmash_and_show();

    void process_reset();

signals:
    void closeevent();
    void showmash(tuple<int,int>);

};

#endif // CONTROLLER_H
