#include "login_on.h"
#include "ui_login_on.h"

Login_on::Login_on(QDir storedir ,QWidget *parent) :
    QWidget(parent) ,storedir(storedir),
    ui(new Ui::Login_on)
{
    ui->setupUi(this);
}

Login_on::~Login_on()
{
    delete ui;
}

void Login_on::on_login_on_button_clicked(bool checked)
{
    QString user = ui->user_text->text();
    QString password = ui->password_text->text();
    QStringList users_name = storedir.entryList(QDir::NoDotAndDotDot | QDir::Dirs);
    for(auto user_hasloginin: users_name){
        if(user_hasloginin == user){
            ui->statu_label->setText("账号已经存在");
            return;
        }
    }
    if(password.length()==0){
        ui->statu_label->setText("密码不能为空");
        return;
    }
    storedir.mkpath(storedir.relativeFilePath(user));
    //std::string str = storedir.relativeFilePath(user+"/password.bin").toStdString();
    std::ofstream outfile(storedir.absoluteFilePath(user+"/password.bin").toStdString(), std::ios::binary);
    outfile.write(password.toStdString().c_str(), password.toStdString().size());
    ui->statu_label->setText("注册成功，单击取消键返回");
}

void Login_on::on_undo_button_clicked(bool checked)
{
    close();
}
