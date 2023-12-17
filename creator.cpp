#include "creator.h"
#include "controller.h"


Creator::Creator()
{

}

ConstructGame *Creator::game_product(int size)
{
    return new Go(size);
}



ConstructGame *Gobang_Creator::game_product(int size)
{
    return new Gobang(size);
}

QDir *Gobang_Creator::dir_product(const QDir & storedir)
{
    return new QDir(storedir.filePath("Gobang"));
}

BoardShow *Gobang_Creator::boardshow_product(int size, ConstructGame *game, Controller *controller)
{
    BoardShow* boardshow = new GobangBoardshow(size, game->get_chessboard()->get_points());
    return boardshow;
}

Select_sizeIF *Gobang_Creator::select_size_product()
{
    return new Select_Gobangsize();
}

ConstructGame *Go_Creator::game_product(int size)
{
    return new Go(size);
}

QDir *Go_Creator::dir_product(const QDir& storedir)
{
    return new QDir(storedir.filePath("Go"));
}

BoardShow *Go_Creator::boardshow_product(int size , ConstructGame* game ,Controller* controller)
{
    BoardShow* boardshow = new Goboardshow(size, game->get_chessboard()->get_points());
    QObject::connect(dynamic_cast<Goboardshow*>(boardshow), &Goboardshow::emit_skipsig, controller, &Controller::skip_operation);
    QObject::connect(dynamic_cast<Goboardshow*>(boardshow), &Goboardshow::emit_getmashsig, controller, &Controller::process_getmash_and_show);
    return boardshow;
}

Select_sizeIF *Go_Creator::select_size_product()
{
    return new Select_Gosize();
}
