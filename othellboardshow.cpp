#include "othellboardshow.h"
#include <QPainter>
#include <cmath>



Othellboardshow::Othellboardshow(int size, std::vector<std::vector<Chessboardpoint *>> points, int d):BoardShow(size, points, d)
{

}

void Othellboardshow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    for(int i = 1 ; i <=size+1; i++){
        if(i==1 || i == size+1){
            painter.drawLine(i*d,d,i*d,(size+1)*d);
        }
        else{
            painter.drawLine(i*d,d,i*d,(size+1)*d);
        }
    }
    for(int i = 1; i <= size+1 ; i++){
        if(i==1 || i == size+1){
            painter.drawLine(d,i*d,(size+1)*d,i*d);
        }
        else{
            painter.drawLine(d,i*d,(size+1)*d,i*d);
        }
    }

    QBrush blackbrush(Qt::black);
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    //painter.drawEllipse(0*d,d,d,d);
    for(int i = 0 ; i < size ; i++){
        for(int j = 0 ; j < size ; j++){
            if((points)[i][j]->get_state() == PointState::Black){
                painter.setBrush(blackbrush);
                painter.setPen(blackPen);
                painter.drawEllipse((j+1)*d,(i+1)*d,d,d);
            }
            else if((points)[i][j]->get_state() == PointState::White){
                painter.setBrush(whiteBrush);
                painter.setPen(blackPen);
                painter.drawEllipse((j+1)*d,(i+1)*d,d,d);
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
}

void Othellboardshow::mouseReleaseEvent(QMouseEvent *event)
{
    int y = static_cast<int>((event->pos().x()/(d)));
    int x = static_cast<int>((event->pos().y()/(d)));

    if (x >= 1 && x <= size && y >= 1 && y <= size) {
        emit emit_setsig(x-1,y-1);
    }
}
