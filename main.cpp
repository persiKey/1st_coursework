#include <QApplication>
#include <QPushButton>
#include <QtWidgets>
#include "menu.h"
#include "game.h"

#include "cardmaker.h"
#include "test.h"
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
    //CardMaker test;
    QFontDatabase::addApplicationFont("F:\\Projects\\Qt\\Chicken\\src\\Hoyle Playing Cards.ttf");
    Test tes(nullptr);
    tes.show();


    return a.exec();
}


