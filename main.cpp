#include <QApplication>
#include "func.h"
#include "menu.h"
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PrepareAppToStart(a);

    QWidget MainWnd;
    SetUpWnd(&MainWnd);

    Menu menu;
    menu.setWnd(&MainWnd);

    Game game;
    game.setWnd(&MainWnd);

    QObject::connect(&menu,SIGNAL(StartGame(int, Difficulty, PlayerStat*)),&game,SLOT(Init(int, Difficulty, PlayerStat*)));
    QObject::connect(&game,SIGNAL(MainMenu()),&menu,SLOT(MainMenu()));

    return a.exec();
}
