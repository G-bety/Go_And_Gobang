#include "select_sizeif.h"
Select_sizeIF::Select_sizeIF(QWidget *parent) :
    QWidget(parent)
{

}

Select_sizeIF::~Select_sizeIF()
{
}

void Select_sizeIF::closeEvent(QCloseEvent *event)
{
    emit pro_close();
    QWidget::closeEvent(event);
}
