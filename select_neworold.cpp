#include "select_neworold.h"
#include "ui_select_neworold.h"

Select_neworold::Select_neworold(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Select_neworold)
{
    ui->setupUi(this);
}

Select_neworold::~Select_neworold()
{
    delete ui;
}

void Select_neworold::closeEvent(QCloseEvent *event)
{
    emit emit_close();
    QWidget::closeEvent(event);
}

void Select_neworold::on_newgame_clicked(bool checked)
{
    emit emit_newgame();
}

void Select_neworold::on_load_oldgame_clicked(bool checked)
{
    emit emit_loadoldgame();
}
