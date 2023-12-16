#ifndef MINWINDOW_H
#define MINWINDOW_H

#include <QWidget>
#include "creator.h"

namespace Ui {
class MinWindow;
}

class MinWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MinWindow(QWidget *parent = nullptr);
    ~MinWindow();

signals:
    void pro_creator(Creator*);


private slots:

    void on_Button_SelectGo_clicked(bool checked);

    void on_Button_SelectGoang_clicked(bool checked);

    void winclose();

private:
    Ui::MinWindow *ui;
};

#endif // MINWINDOW_H
