#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QtWidgets>
#include "constants.h"
#include "playerstat.h"

using Types::Difficulty;

class Menu : public QObject
{
    Q_OBJECT
    LoginWidget* Login;
    QWidget* Wnd;
    QLabel Title;
    QGridLayout Layout;
    QTextBrowser* StatInfo;
    QPushButton FuncButton1;
    QPushButton FuncButton3;
    QPushButton FuncButton2;
    int players;
    Difficulty Diff;
    PlayerStat Profile;

private slots:
    void PlayersMenu();
    void DifficultyMenu();
    void SetPlayers();
    void SetDifficulty();
    void StatMenu();
    void Back();
    void Exit();
public slots:
    void MainMenu();
    void Start(PlayerStat);
signals:
    void StartGame(int pl, Difficulty dif, PlayerStat*);

public:
    Menu(QWidget* parent = nullptr);
    void setWnd(QWidget* wnd);

};

#endif // MENU_H
