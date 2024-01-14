#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QWidget>
#include "boardshow.h"
#include "consturtgame.h"
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
#include "operationwithfile.h"


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
    ConstructGame* game;
    int size;
    Creator* creator;
    QDir storedir;
    QString current_gamestore_name;
    OldgameListShow* oldgamelist;
    User_info user_info;
    void getboard_and_show();
    void make_board();
    void savetofile(QString filePath);
    void readfromfile(QString filePath);
    void closeEvent(QCloseEvent *event) override;
    void get_userinfo();


private slots:
    /**
     * @brief setchessboardpoint 在坐标x，y落子，注意在显示端是不关系哪一方落得子
     * @param x
     * @param y
     */
    void setchessboardpoint(int x, int y);//<得到来自Boardshow的

    /**
     * @brief undo_operation 接受悔棋事件，并令客户端执行
     */
    void undo_operation();

    /**
     * @brief unundo_operation 撤销悔棋事件
     */
    void unundo_operation();

    /**
     * @brief save_current_game 处理View发出的保存命令，以当前时间命名
     */
    void save_current_game();

    /**
     * @brief process_and_get_creator 处理用户选择游戏类型事件，传入的参数是一个工厂，由工厂决定生成什么类型的棋局
     */
    void process_and_get_creator(Creator*);

    /**
     * @brief process_new_game 处理用户选择新游戏事件，然后展示选择棋盘大小页面
     */
    void process_new_game();//处理创建新游戏的信号

    /**
     * @brief process_load_old_game 处理选择加载已有对局事件，读取已有对局列表并显示出来供用户选择
     */
    void process_load_old_game();

    /**
     * @brief process_sizeinfo_and_makeboard 处理View返还的用户选择棋盘大小事件，并根据size大小创建新的棋盘
     * @param size
     */
    void process_sizeinfo_and_makeboard(int size);

    /**
     * @brief process_boardclose 处理关闭棋盘事件，进而返回 选择开始新游戏或加载旧游戏的界面
     */
    void process_boardclose();

    /**
     * @brief process_selectsizeclose 处理关闭选择棋盘大小界面事件，返回选择开始新游戏或加载旧游戏的界面
     */
    void process_selectsizeclose();

    /**
     * @brief process_selectneworoldclose 处理关闭选择开始新游戏或加载旧游戏的界面，返回选择游戏类型界面
     */
    void process_selectneworoldclose();

    /**
     * @brief load_old_game 处理加载已有对局事件，并显示出对局
     * @param filename 选择的已有对局的文件位置
     */
    void load_old_game(QString filename);


    /**
     * @brief process_reset 处理重置棋局界面
     */
    void process_reset();

    /**
     * @brief process_surrender 处理投降事件
     */
    void process_surrender();

    /**
     * @brief process_ultimate 处理终局判断事件
     */
    void process_Ultimate_judgement();

    /**
     * @brief process_minwindow_close 处理主窗口关闭事件
     */
    void process_minwindow_close();

public slots:
    void skip_operation();
    /**
     * @brief process_getmash_and_show 处理请求点目事件，与Model交互并将结果返回显示
     */
    void process_getmash_and_show();

signals:
    void finished();

};

#endif // CONTROLLER_H
