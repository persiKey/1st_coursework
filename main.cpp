#include <QApplication>
#include <QPushButton>
#include <QtWidgets>
#include "menu.h"
#include "game.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget MainWnd;
    MainWnd.setFixedSize(1080,720);
    Menu menu;
    menu.setWnd(&MainWnd);
    Game game;
    game.setWnd(&MainWnd);
    QObject::connect(&menu,SIGNAL(StartGame(int, int)),&game,SLOT(Init(int, int)));

    return a.exec();
}


