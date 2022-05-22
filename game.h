#ifndef GAME_H
#define GAME_H

#include <QObject>


#include "player.h"
#include "carddeque.h"

#include "cardmaker.h"
using std::vector;
class Game : public QObject
{
    Q_OBJECT
    QWidget* Wnd;
    QPushButton* Move;
    CardSuit last;

    int players;
    int difficulty;

    Card Cards[NUM_OF_SUITS*NUM_OF_VALUES];
    CardMaker* Maker;
    MainPlayer* Player;
    Enemy** Enemies;
    CardDeque* Deque;
    OpenCardDeque* OpenDeque;


private:
    void GenerateCards();
    void GiveCards();
    void MainLoop();
    void GiveCardsToPlayers();
    bool CheckMovesAvailable(class Player* pl);
    void TakeAllOpenCards(class Player*pl);
    bool CheckIfWin(class Player* pl);
    void RenewDeque();
    int OnePlayerTact(class Player *pl);
public:
    explicit Game(QObject *parent = nullptr);
    void setWnd(QWidget* wnd);
private slots:
    void OneGameTact();
public slots:
    void Init(int pl, int dif);
signals:

};

#endif // GAME_H
