#include "select_gobangsize.h"
#include "ui_select_gobangsize.h"

Select_Gobangsize::Select_Gobangsize(QWidget *parent) :
    Select_sizeIF(parent),
    ui(new Ui::Select_Gobangsize)
{
    setupUi();
}

Select_Gobangsize::~Select_Gobangsize()
{
    delete ui;
}

void Select_Gobangsize::setupUi()
{
    Ui::Select_Gobangsize* Ui = new Ui::Select_Gobangsize();
    Ui->setupUi(this);
}

void Select_Gobangsize::on_button17_clicked(bool checked)
{
    emit emit_sizesig(17);
}

void Select_Gobangsize::on_button15_clicked(bool checked)
{
    emit emit_sizesig(15);
}
