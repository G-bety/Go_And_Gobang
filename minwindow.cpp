#include "minwindow.h"
#include "ui_minwindow.h"


MinWindow::MinWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MinWindow)
{
    ui->setupUi(this);
}

MinWindow::~MinWindow()
{
    delete ui;
}

void MinWindow::on_Button_SelectGo_clicked(bool checked)
{
    emit pro_creator(new Go_Creator());
}

void MinWindow::on_Button_SelectGoang_clicked(bool checked)
{
    emit pro_creator(new Gobang_Creator());
}



void MinWindow::winclose()
{
    this->show();
}
