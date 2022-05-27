#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QLabel>
#include <QGridLayout>
#include <time.h>

#include "player.h"
#include "carddeque.h"
#include "cardmaker.h"
#include "playerstat.h" // will change to constants

using std::vector;
class Game : public QObject
{
    Q_OBJECT
    QWidget* Wnd;
    QPushButton* Move;
    QPushButton* PauseButton;

    QLabel* Text;
    QGridLayout* Layout;
    QPushButton* ResumeButton;
    QPushButton* RestartButton;
    QPushButton* MainMenuButton;

    PlayerStat* Profile;
    int players;
    int difficulty;
    clock_t game_started;
    int active_player;

    CardSuit last;
    Card Cards[NUM_OF_SUITS*NUM_OF_VALUES];
    CardMaker* Maker;
    MainPlayer* Player;
    Enemy** Enemies;
    CardDeque* Deque;
    OpenCardDeque* OpenDeque;


private:
    void GenerateCards();
    void GiveCardsToPlayers();
    void GiveOneCardFromDequeToPlayer(class Player* pl);
    bool CheckMovesAvailable(class Player* pl);
    void TakeAllOpenCards(class Player*pl);
    bool CheckIfWin(class Player* pl);
    void RenewDeque();
    int OnePlayerTact(class Player *pl);

    void HideGameElements();
    void ShowGameElements();
    void HideMenuElements();
    void ShowMenuElements();
    void FreeResourses();
    void Restart();
    void FillPlayerStat(bool win);
    void DisplayWinLoose(QString msg);

    void InitMenuElements();
    void DeleteMenuElements();
public:
    explicit Game(QObject *parent = nullptr);
    void setWnd(QWidget* wnd);
private slots:
    void OneGameTact();

    void PauseGame();
    void ResumeGame();
    void RestartGame();
    void EnterMainMenu();
public slots:
    void Init(int pl, int dif, PlayerStat*);
signals:
    void MainMenu();
};

#endif // GAME_H
