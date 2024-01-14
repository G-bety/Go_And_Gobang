#include "minwindow.h"
#include "ui_minwindow.h"


MinWindow::MinWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MinWindow)
{
    ui->setupUi(this);
}

MinWindow::~MinWindow()
{
    delete ui;
}

void MinWindow::on_Button_SelectGo_clicked(bool checked)
{
    emit sig_creatorsig(new Go_Creator());
}

void MinWindow::on_Button_SelectGoang_clicked(bool checked)
{
    emit sig_creatorsig(new Gobang_Creator());
}



void MinWindow::winclose()
{
    this->show();
}

void MinWindow::on_Button_SelectOthello_clicked(bool checked)
{
    emit sig_creatorsig(new Othello_Creator());
}

void MinWindow::closeEvent(QCloseEvent *event)
{
    emit sig_closeevent();
}

void MinWindow::on_Button_SelectGoang_AI_clicked(bool checked)
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("选择AI级别");

    QVBoxLayout vlayout;

    QComboBox comboBox;
    comboBox.addItem("一级AI");
    comboBox.addItem("二级AI");
    comboBox.addItem("三级AI");

    //文字居中显示
    comboBox.setStyleSheet("QComboBox::item { text-align: center; }");

    vlayout.addWidget(&comboBox);
    // 在对话框中添加需要的控件，如选择框、按钮等
    QPushButton dialogButton("确定");
    dialogButton.setFixedSize(50,20);

    vlayout.addWidget(&dialogButton,0, Qt::AlignHCenter);

    dialog->resize(200,100);
    dialog->setLayout(&vlayout);

    connect(&dialogButton, &QPushButton::clicked, [&](){
        auto index = comboBox.currentIndex();
        if(index == 0){
            emit sig_creatorsig(new Gobang_AI_1_Creator());
            dialog->close();
        }
        else if(index == 1){
            emit sig_creatorsig(new Gobang_AI_2_Creator());
             dialog->close();
        }
    });
    // 连接对话框按钮的槽函数，处理按钮点击事件
    //connect(dialogButton, &QPushButton::clicked, dialog, &QDialog::accept);


    // 设置对话框布局和控件

    dialog->exec(); // 执行对话框，阻塞主窗口的事件循环

}
