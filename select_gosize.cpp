#include "select_gosize.h"
#include "ui_select_gosize.h"

Select_Gosize::Select_Gosize(QWidget *parent) :
    Select_sizeIF(parent),
    ui(new Ui::Select_Gosize)
{
    setupUi();
}

Select_Gosize::~Select_Gosize()
{
    delete ui;
}

void Select_Gosize::setupUi()
{
    Ui::Select_Gosize* Ui = new Ui::Select_Gosize();
    Ui->setupUi(this);
}

void Select_Gosize::on_button19_clicked(bool checked)
{
    emit emit_sizesig(19);
}

void Select_Gosize::on_button13_clicked(bool checked)
{
    emit emit_sizesig(13);
}

void Select_Gosize::on_button11_clicked(bool checked)
{
    emit emit_sizesig(11);
}
