#ifndef SELECT_GOBANGSIZE_H
#define SELECT_GOBANGSIZE_H

#include <QWidget>
#include "select_sizeif.h"

namespace Ui {
class Select_Gobangsize;
}

class Select_Gobangsize : public Select_sizeIF
{
    Q_OBJECT

public:
    explicit Select_Gobangsize(QWidget *parent = nullptr);
    ~Select_Gobangsize();

private slots:
    void on_button17_clicked(bool checked);

    void on_button15_clicked(bool checked);

private:
    Ui::Select_Gobangsize *ui;
    void setupUi() override;
};

#endif // SELECT_GOBANGSIZE_H
