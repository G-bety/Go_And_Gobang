#include "boardshow.h"
#include <QPainter>
#include <cmath>

BoardShow::BoardShow(QWidget *parent) : QWidget(parent)
{
}

BoardShow::BoardShow(int size,std::vector<std::vector<Chessboardpoint*>> points,int d){
    this->size = size;
    this->d = d;
    this->setFixedSize(1100,800);
    this->points = points;
    username = new QStatusBar(this);
    username->setGeometry((size+2)*d, 2*d, 4*d, d);
    userwinratio = new QStatusBar(this);
    userwinratio->setGeometry((size+2)*d, 3*d, 4*d, d);
    statusbar = new QStatusBar(this);
    statusbar->setGeometry((size+2)*d, 4*d, 4*d,d);
    button_undo = new QPushButton("Undo", this);
    button_undo->setGeometry((size+2)*d, 8*d, 4*d, d);
    QObject::connect(button_undo,&QPushButton::clicked,this, [&](){
        emit emit_undosig();
    });
    button_unundo = new QPushButton("UnUndo", this);
    button_unundo->setGeometry((size+2)*d, 6*d, 4*d, d);
    QObject::connect(button_unundo,&QPushButton::clicked,this, [&](){
        emit emit_unundosig();
    });
    button_reset = new QPushButton("Reset",this);
    button_reset->setGeometry((size+2)*d, 10*d, 4*d,d);
    QObject::connect(button_reset,&QPushButton::clicked,this, [&](){
        emit emit_reset();
    });
    button_surrender = new QPushButton("弃子认输",this);
    button_surrender->setGeometry((size+2)*d, 12*d, 4*d,d);
    QObject::connect(button_surrender,&QPushButton::clicked,this, [&](){
        emit emit_surrender();
    });


}



void BoardShow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    for(int i = 1 ; i <=size; i++){
        if(i==1 || i == size){
            painter.drawLine(i*d,d,i*d,size*d);
        }
        else{
            painter.drawLine(i*d,d,i*d,size*d);
        }
    }
    for(int i = 1; i <= size ; i++){
        if(i==1 || i == size){
            painter.drawLine(d,i*d,size*d,i*d);
        }
        else{
            painter.drawLine(d,i*d,size*d,i*d);
        }
    }

    QBrush blackbrush(Qt::black);
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);

    for(int i = 0 ; i < size ; i++){
        for(int j = 0 ; j < size ; j++){
            if((points)[i][j]->get_state() == PointState::Black){
                painter.setBrush(blackbrush);
                painter.setPen(blackPen);
                painter.drawEllipse((i+1)*d-d/2,(j+1)*d-d/2,d,d);
            }
            else if((points)[i][j]->get_state() == PointState::White){
                painter.setBrush(whiteBrush);
                painter.setPen(blackPen);
                painter.drawEllipse((i+1)*d-d/2,(j+1)*d-d/2,d,d);
            }
        }
    }
    if(gamestate == Gamestate::Keeping_battle){
        if(gameturn == GameTurn::Black){
            this->statusbar->showMessage("黑方执子");
        }
        else if(gameturn == GameTurn::White){
            this->statusbar->showMessage("白方执子");
        }
    }
    else if(gamestate == Gamestate::Black_win){
        this->statusbar->showMessage("黑胜");
    }
    else if(gamestate == Gamestate::White_win){
        this->statusbar->showMessage("白胜");
    }

    else if(gamestate == Gamestate::Dogfall){
        this->statusbar->showMessage("平局");
    }
    this->username->showMessage(user_info.name);
    this->userwinratio->showMessage("胜率："+QString::number(double(user_info.win_games)/(1e-6+user_info.win_games+user_info.loss_games)));
}

void BoardShow::mouseReleaseEvent(QMouseEvent *event)
    {
        int x = static_cast<int>(std::round(event->pos().x()/static_cast<double>(d)));
        int y = static_cast<int>(std::round(event->pos().y()/static_cast<double>(d)));

        if (x >= 1 && x <= size && y >= 1 && y <= size) {
            emit emit_setsig(x-1,y-1);
        }

    }


void BoardShow::showboard(std::vector<std::vector<Chessboardpoint*>> points, GameTurn gameturn, Gamestate gamestate, User_info user_info){
    this->points = points;
    this->gameturn = gameturn;
    this->gamestate = gamestate;
    this->user_info = user_info;
    update();
}

void BoardShow::closeEvent(QCloseEvent *event)
{
    //关闭当前窗口会弹出一个对话框确认是否保存
    QMessageBox::StandardButton answer;

    QMessageBox::StandardButtons buttons = QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel;
    QMessageBox msgBox(QMessageBox::Question, "Confirmation", "Do you want to save the changes?", buttons, this);

    msgBox.setDefaultButton(QMessageBox::Save);
    msgBox.setEscapeButton(QMessageBox::Cancel);

    answer = static_cast<QMessageBox::StandardButton>(msgBox.exec());

    if (answer == QMessageBox::Save)
    {
        emit emit_save();
    }
    else if (answer == QMessageBox::Cancel)
    {
        event->ignore(); // 取消关闭操作
        return;
    }
    emit emit_closesig();
    QWidget::closeEvent(event);
}

