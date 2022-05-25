#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QtWidgets>
#include "constants.h"
#include "playerstat.h"

class Menu : public QObject
{
    Q_OBJECT
    LoginWidget* Login;
    QWidget* Wnd;
    QLabel Title;
    QGridLayout Layout;
    QPushButton FuncButton1;
    QPushButton FuncButton3;
    QPushButton FuncButton2;
    int players;
    int difficulty;
    PlayerStat Profile;

private slots:
    void PlayersMenu();
    void DifficultyMenu();
    void Exit();
    void SetPlayers();
    void SetDifficulty();

public slots:
    void MainMenu();
    void Start(PlayerStat);
signals:
    void StartGame(int pl, int dif);

public:
    Menu(QWidget* parent = nullptr);
    void setWnd(QWidget* wnd);

};

#endif // MENU_H
