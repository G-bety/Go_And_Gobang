#include "login.h"
#include "ui_login.h"

Login::Login(QDir storedir, QWidget *parent) :
    QWidget(parent),storedir(storedir),
    ui(new Ui::Login)
{
    if(!storedir.exists()){
        storedir.mkpath(".");
    }
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::process_finished()
{
    this->show();
}

void Login::on_login_button_clicked(bool checked)
{
    QString user = ui->user_text->text();
    QString password = ui->password_text->text();
    QStringList users_name = storedir.entryList(QDir::NoDotAndDotDot | QDir::Dirs);
    for(auto user_hasloginin: users_name){
        if(user_hasloginin == user){
            QDir user_storedir = storedir;
            user_storedir.cd(user);
            auto file_names = user_storedir.entryList(QDir::Files|QDir::NoDotAndDotDot);
            for(auto file_name : file_names){
                if(file_name == "password.bin"){
                    //QString correct_password;
                    std::ifstream correct_password(user_storedir.absoluteFilePath(file_name).toStdString(), std::ios::binary);
                    std::ostringstream contentStream;
                        contentStream << correct_password.rdbuf();

                        // 关闭文件
                        correct_password.close();

                        // 获取字符串内容
                        std::string answer = contentStream.str();
                        if(answer == password.toStdString()){
                            Controller* controler = new Controller(user_storedir);
                            connect(controler, &Controller::destroyed, this, &Login::process_finished);
                            hide();
                            //controler->show();
                            return;
                        }
                        else{
                            ui->statu_label->setText("账号不存在或者密码错误");
                            return;
                        }
                }

            }

            ui->statu_label->setText("密码错误");

        }
    }
    ui->statu_label->setText("账号不存在或者密码错误");
}

void Login::on_login_on_button_clicked(bool checked)
{
    Login_on* login_on = new Login_on(storedir);
    login_on->show();
}

void Login::on_visitor_button_clicked(bool checked)
{
    QString user("visitor");
    if(!storedir.exists(user)){
        storedir.mkpath("./"+user);
    }
    Controller* controler = new Controller(storedir.absoluteFilePath("./"+user));
    connect(controler, &Controller::destroyed, this, &Login::process_finished);
    hide();
}
