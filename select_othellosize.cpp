#include "select_othellosize.h"
#include "ui_select_othellosize.h"


Select_OthelloSize::Select_OthelloSize(QWidget *parent) :
    Select_sizeIF(parent),
    ui(new Ui::Select_OthelloSize)
{
    ui->setupUi(this);
}

Select_OthelloSize::~Select_OthelloSize()
{
    delete ui;
}

void Select_OthelloSize::on_button8_clicked(bool checked)
{
    emit emit_sizesig(8);
}

void Select_OthelloSize::setupUi()
{
    Ui::Select_OthelloSize* Ui = new Ui::Select_OthelloSize();
    Ui->setupUi(this);
}
