#include "goboardshow.h"
#include <iostream>


Goboardshow::Goboardshow(int size, std::vector<std::vector<Chessboardpoint *>> points, int d):BoardShow(size,points,d)
{
    button_skip = new QPushButton("停一手", this);
    button_skip->setGeometry((size+2)*d, 14*d, 4*d, d);
    QObject::connect(button_skip,&QPushButton::clicked,this, [&](){
        emit emit_skipsig();
    });
    button_getmash = new QPushButton("点目",this);
    button_getmash->setGeometry((size+2)*d, 16*d, 4*d, d);
    QObject::connect(button_getmash,&QPushButton::clicked,this, [&](){
        emit emit_getmashsig();
    });
}

void Goboardshow::showmash(std::tuple<int, int> mashes)
{
    QMessageBox::StandardButton reply;
    int count_black = std::get<0>(mashes);
    int count_white = std::get<1>(mashes);
    QString str;
    if(count_black-6.5 < count_white){
        str = QString("黑棋："+QString::number(std::get<0>(mashes))+"目   白棋："+QString::number(std::get<1>(mashes))+"目<br><center>白棋胜"+QString::number(count_white-count_black+6.5)+"目");
    }
    else if(count_black-6.5 > count_white) {
        str = QString("黑棋："+QString::number(std::get<0>(mashes))+"目   白棋："+QString::number(std::get<1>(mashes))+"目<br><center>黑棋胜"+QString::number(count_black-count_white-6.5)+"目");
    }
    else{
        str = QString("黑棋："+QString::number(std::get<0>(mashes))+"目   白棋："+QString::number(std::get<1>(mashes))+"目<br><center>均势");
    }

   QMessageBox msgBox(QMessageBox::Question, "数目结果", str,QMessageBox::Yes | QMessageBox::No,this );
   msgBox.setTextFormat(Qt::RichText);
   reply =static_cast<QMessageBox::StandardButton>(msgBox.exec());
   if (reply == QMessageBox::Yes) {
       // 用户点击了确定按钮，执行相应操作
        emit emit_Ultimate_judgement();
   } else {
       // 用户点击了取消按钮，什么也不做
   }
}
