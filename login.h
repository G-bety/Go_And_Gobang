#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QString>
#include <QDir>
#include <login_on.h>
#include <sstream>
#include "controller.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QDir storedir, QWidget *parent = nullptr);
    ~Login();
public slots:


private slots:
    void on_login_button_clicked(bool checked);

    void on_login_on_button_clicked(bool checked);

    void on_visitor_button_clicked(bool checked);

    void process_finished();

private:
    Ui::Login *ui;
    QDir storedir;
};

#endif // LOGIN_H
