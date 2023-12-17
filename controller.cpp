#include "Controller.h"

Controller::Controller(QDir storedir):storedir(storedir)
{

    minwindow = new MinWindow();
    minwindow->show();
    select_neworold  = nullptr;
    select_size = nullptr;
    boardshow = nullptr;
    game = nullptr;
    creator = nullptr;
    oldgamelist = nullptr;
    QObject::connect(minwindow, &MinWindow::emit_creatorsig, this, &Controller::process_and_get_creator);

    //getboard_and_show();
}

Controller::~Controller()
{
    delete game;
    delete boardshow;
}

void Controller::setchessboardpoint(int x, int y){
    if(game->get_gamestatu() == Gamestate::Keeping_battle){
        game->set(x,y);
    }
    getboard_and_show();
}

void Controller::undo_operation()
{
    game->undo();
    getboard_and_show();
}

void Controller::skip_operation()
{
    game->set(-1,-1);
    getboard_and_show();
}

void Controller::save_current_game()
{
    if(current_gamestore_name.length() != 0){
        QFile file(current_gamestore_name);

           if (file.remove()) {
               std::cout << "Delete Failed"<<std::endl;
           } else {
               std::cout << "Delete Success"<<std::endl;
           }
    }
    QDateTime currentTime = QDateTime::currentDateTime();
    QString timeString = currentTime.toString("yyyyMMdd_hhmmss");
    QDir* constructdir;
    constructdir = creator->dir_product(storedir);
    QString filePath = constructdir->absoluteFilePath(timeString.append(".bin"));
    //QString filePath = constructdir->absoluteFilePath("test.bin");
    this->savetofile(filePath);
}


void Controller::savetofile(QString filePath)
{
    std::ofstream outfile(filePath.toStdString(), std::ios::binary);
    if(outfile.good()){
        outfile.write(reinterpret_cast<char*>(&this->size),sizeof(this->size));
        game->savetofile(outfile);
    }
    else{
        std::cout<<filePath.toStdString()<<"打开失败"<<std::endl;
    }
    outfile.close();
}

void Controller::readfromfile(QString filePath)
{
    std::ifstream infile(filePath.toStdString(), std::ios::binary);
    if(!infile.good()){
        std::printf("打开文件失败");
    }
    infile.read(reinterpret_cast<char*>(&this->size),sizeof(this->size));
    this->game = creator->game_product(size);//这步骤只是为了初始化
    make_board();//同时顺带初始化棋盘
    game->readfromfile(infile);
    infile.close();
}

void Controller::getboard_and_show(){
    boardshow->showboard(game->get_chessboard()->get_points(),game->get_gameturn(), game->get_gamestatu());
}

void Controller::make_board()
{
    this->game = creator->game_product(size);
    this->boardshow = creator->boardshow_product(size, game, this);
    //this->boardshow->deleteLater();
    QObject::connect(boardshow, &BoardShow::emit_closesig, this, &Controller::process_boardclose);
    QObject::connect(boardshow, &BoardShow::emit_setsig, this , &Controller::setchessboardpoint);
    QObject::connect(boardshow, &BoardShow::emit_undosig, this , &Controller::undo_operation);
    QObject::connect(boardshow, &BoardShow::emit_save, this , &Controller::save_current_game);
    QObject::connect(boardshow, &BoardShow::emit_reset, this , &Controller::process_reset);
    QObject::connect(boardshow, &BoardShow::emit_surrender, this , &Controller::process_surrender);
    QObject::connect(boardshow, &BoardShow::emit_Ultimate_judgement, this , &Controller::process_Ultimate_judgement);
}



//确定了生成器也就确定了游戏模式
void Controller::process_and_get_creator(Creator * creator)
{
    this->creator = creator;
    minwindow->hide();
    this->select_neworold = new Select_neworold();
    select_neworold->show();
    //select_neworold->deleteLater();
    QObject::connect(select_neworold, &Select_neworold::emit_newgamesig, this, &Controller::process_new_game);
    QObject::connect(select_neworold, &Select_neworold::emit_closesig, this, &Controller::process_selectneworoldclose);
    QObject::connect(select_neworold, &Select_neworold::emit_loadoldgamesig, this, &Controller::process_load_old_game);
}

void Controller::process_new_game()
{
    //先调用选择期盼大小的类并展示出来
    this->select_size = creator->select_size_product();
   select_neworold->hide();
   select_size->show();
   QObject::connect(select_size, &Select_sizeIF::emit_sizesig, this, &Controller::process_sizeinfo_and_makeboard);
   QObject::connect(select_size, &Select_sizeIF::emit_closesig, this, &Controller::process_selectsizeclose);
}

void Controller::process_load_old_game()
{
    QDir* constructdir;
    constructdir = creator->dir_product(storedir);
    if(!constructdir->exists()){
           constructdir->mkpath(".");
    }
    QFileInfoList Qfilelist = constructdir->entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    QStringList filenames;
    foreach (auto Qfile, Qfilelist){
        filenames.append(Qfile.fileName());
    }
    oldgamelist = new OldgameListShow(filenames);
    QObject::connect(oldgamelist, &OldgameListShow::pro_oldgameinfo, this, &Controller::load_old_game);
}

void Controller::process_sizeinfo_and_makeboard(int size)
{
    this->size = size;
    select_size->hide();
    make_board();
   // this->savetofile("./test.bin");
    this->boardshow->show();
    getboard_and_show();
}

void Controller::process_boardclose()
{
    boardshow->hide();
    this->boardshow->deleteLater();
    this->boardshow = nullptr;
    if(select_size){
        select_size->deleteLater();
        select_size = nullptr;
    }

    select_neworold->show();
    //this->select_size->deleteLater();
}

void Controller::process_selectsizeclose()
{
    if(select_size!=nullptr){
        select_size->hide();
        select_size->deleteLater();
        select_size = nullptr;
    }
    select_neworold->show();
}

void Controller::process_selectneworoldclose()
{
    select_neworold->hide();
    if(this->select_size!=nullptr){
        this->select_size->deleteLater();
        this->select_size = nullptr;
    }
    if(this->select_neworold!=nullptr){
        this->select_neworold->deleteLater();
        this->select_neworold = nullptr;
    }
    minwindow->show();
}

void Controller::load_old_game(QString filename)
{
    QDir* constructdir;
    constructdir = creator->dir_product(storedir);
    QString filePath = constructdir->absoluteFilePath(filename);
    current_gamestore_name = filePath;
    this->readfromfile(filePath);
   //
    this->boardshow->show();
    this->select_neworold->hide();
    getboard_and_show();
}

void Controller::process_getmash_and_show()
{
    tuple<int,int> mashes = dynamic_cast<Go*>(game)->getmash();
    dynamic_cast<Goboardshow*>(boardshow)->showmash(mashes);
}

void Controller::process_reset()
{
    game->reset();
    getboard_and_show();
}

void Controller::process_surrender()
{
    game->surrender();
    getboard_and_show();
}

void Controller::process_Ultimate_judgement()
{
    game->Ultimate_judgment();
    getboard_and_show();
}
