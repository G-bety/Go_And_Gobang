#include "goboardshow.h"
#include <iostream>

void Goboardshow::onButton_getmash_Clicked()
{
    emit pro_getmash();
}

void Goboardshow::onButton_skip_Clicked()
{
    emit pro_skip();
}

Goboardshow::Goboardshow(int size, std::vector<std::vector<Chessboardpoint *>> points, int d):BoardShow(size,points,d)
{
    button_skip = new QPushButton("停一手", this);
    button_skip->setGeometry((size+2)*d, 12*d, 4*d, d);
    QObject::connect(button_skip,&QPushButton::clicked,this, &Goboardshow::onButton_skip_Clicked);
    button_getmash = new QPushButton("点目",this);
    button_getmash->setGeometry((size+2)*d, 14*d, 4*d, d);
    QObject::connect(button_getmash,&QPushButton::clicked,this, &Goboardshow::onButton_getmash_Clicked);
}

void Goboardshow::showmash(std::tuple<int, int> mashes)
{
    QMessageBox messagebox(this);
    QString str = QString("黑棋："+QString::number(std::get<0>(mashes))+"目   白棋："+QString::number(std::get<1>(mashes))+"目");
    messagebox.setText(str);
    messagebox.setStandardButtons(QMessageBox::Ok);
    messagebox.exec();
}
