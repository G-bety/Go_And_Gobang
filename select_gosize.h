#ifndef SELECT_GOSIZE_H
#define SELECT_GOSIZE_H

#include <QWidget>
#include "select_sizeif.h"

namespace Ui {
class Select_Gosize;
}

class Select_Gosize : public Select_sizeIF
{
    Q_OBJECT

public:
    explicit Select_Gosize(QWidget *parent = nullptr);
    ~Select_Gosize();
private slots:
    void on_button19_clicked(bool checked);

    void on_button13_clicked(bool checked);

    void on_button11_clicked(bool checked);

private:
    Ui::Select_Gosize *ui;
    void setupUi() override;
};

#endif // SELECT_GOSIZE_H
