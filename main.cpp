#include <QApplication>
#include "func.h"
#include "menu.h"
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PrepareAppToStart();

    QWidget MainWnd;
    SetUpWnd(&MainWnd);

    Menu menu;
    menu.setWnd(&MainWnd);

    Game game;
    game.setWnd(&MainWnd);

    QObject::connect(&menu,SIGNAL(StartGame(int, int, PlayerStat*)),&game,SLOT(Init(int, int, PlayerStat*)));
    QObject::connect(&game,SIGNAL(MainMenu()),&menu,SLOT(MainMenu()));

    return a.exec();
}
