#ifndef SELECT_OTHELLOSIZE_H
#define SELECT_OTHELLOSIZE_H
#include "select_sizeif.h"
#include <QWidget>

namespace Ui {
class Select_OthelloSize;
}

class Select_OthelloSize : public Select_sizeIF
{
    Q_OBJECT

public:
    explicit Select_OthelloSize(QWidget *parent = nullptr);
    ~Select_OthelloSize();

private slots:
    void on_button8_clicked(bool checked);

private:
    Ui::Select_OthelloSize *ui;
     void setupUi() override;
};

#endif // SELECT_OTHELLOSIZE_H
