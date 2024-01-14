#ifndef MINWINDOW_H
#define MINWINDOW_H

#include <QWidget>
#include "creator.h"
#include <QVBoxLayout>
#include <QComboBox>

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
    void sig_creatorsig(Creator*);

    void sig_closeevent();

private slots:

    void on_Button_SelectGo_clicked(bool checked);

    void on_Button_SelectGoang_clicked(bool checked);

    void winclose();

    void on_Button_SelectOthello_clicked(bool checked);


    void on_Button_SelectGoang_AI_clicked(bool checked);

private:
    Ui::MinWindow *ui;
    void closeEvent(QCloseEvent *event) override;
};

#endif // MINWINDOW_H
