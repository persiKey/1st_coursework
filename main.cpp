#include <QApplication>
#include "func.h"
#include "menu.h"
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PrepareAppToStart();
    a.setStyleSheet("QPushButton{"
                    "font: 16px;"
                    "background-color:lightgray;"
                    "border-radius:15%;"
                    "border: 1.5px solid black;}"
                    "QPushButton:hover{background-color:white;"
                    "border: 2px dashed gray}");
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
