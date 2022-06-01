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
    MainWnd.move((QGuiApplication::primaryScreen()->geometry().width() - Constants::WINDOW_WIDTH)/2,
                 QGuiApplication::primaryScreen()->geometry().height() - Constants::WINDOW_HEIGHT - 40);
    MainWnd.setFixedSize(Constants::WINDOW_WIDTH,Constants::WINDOW_HEIGHT);
    Menu menu;
    menu.setWnd(&MainWnd);
    Game game;
    game.setWnd(&MainWnd);
    QObject::connect(&menu,SIGNAL(StartGame(int, int, PlayerStat*)),&game,SLOT(Init(int, int, PlayerStat*)));
    QObject::connect(&game,SIGNAL(MainMenu()),&menu,SLOT(MainMenu()));
    //CardMaker test;
    QFontDatabase::addApplicationFont("F:\\Projects\\Qt\\Chicken\\src\\Hoyle Playing Cards.ttf");
//    Test tes(&MainWnd);
//    tes.show();


    return a.exec();
}


