#include "game.h"
// 11:17
Game::Game(QObject *parent) : QObject(parent)
{

}

void Game::setWnd(QWidget *wnd)
{
    this->Wnd = wnd;
}

void Game::Init(int pl, int dif)
{
    this->players = pl;
    this->difficulty = dif;
    qDebug() << players << " " << difficulty << "\n";

}

