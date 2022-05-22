#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QtWidgets>
#include "constants.h"


class Menu : public QObject
{
    Q_OBJECT
    QWidget* Wnd;
    QLabel Title;
    QGridLayout Layout;
    QPushButton FuncButton1;
    QPushButton FuncButton3;
    QPushButton FuncButton2;
    int players;
    int difficulty;

private slots:
    void StartMenu();
    void PlayersMenu();
    void DifficultyMenu();
    void Exit();
    void SetPlayers();
    void SetDifficulty();

signals:
    void StartGame(int pl, int dif);

public:
    Menu(QWidget* parent = nullptr);
    void setWnd(QWidget* wnd);

};

#endif // MENU_H
