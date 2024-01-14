#ifndef LOGIN_ON_H
#define LOGIN_ON_H

#include <QWidget>
#include <QDir>
#include <fstream>

namespace Ui {
class Login_on;
}

class Login_on : public QWidget
{
    Q_OBJECT

public:
    explicit Login_on(QDir storedir ,QWidget *parent = nullptr);
    ~Login_on();

private slots:
    void on_login_on_button_clicked(bool checked);

    void on_undo_button_clicked(bool checked);

private:
    Ui::Login_on *ui;
    QDir storedir;
};

#endif // LOGIN_ON_H
