#include "GoBoardshow.h"
#include <QApplication>
#include "Go.h"
#include "Chessboard.h"
#include "GameTurn.h"
#include "controller.h"
#include <QDir>
#include <QDebug>
#include <QString>
#include <string>
#include "minwindow.h"

int main(int argc, char* argv[]){
    QApplication app(argc, argv);
    QDir directory(".");

    Controller* controller = new Controller(directory);
    //controller->show();
    //string current_path = QDir::currentPath().toStdString();
    //std::cout<<current_path<<endl;
    return app.exec();

}
