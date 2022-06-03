#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QLabel>
#include <QGridLayout>
#include <time.h>

#include "player.h"
#include "carddeque.h"
#include "cardmaker.h"
#include "ai.h"

using std::vector;
using Constants::NUM_OF_SUITS;
using Constants::NUM_OF_VALUES;
using Types::PlayerStat;
using Types::Difficulty;
class Game : public QObject
{
    Q_OBJECT
    QWidget* Wnd;
    QPushButton* Move;
    QPushButton* PauseButton;
    QPushButton* HintButton;

    QLabel* Text;
    QGridLayout* Layout;
    QPushButton* ResumeButton;
    QPushButton* RestartButton;
    QPushButton* MainMenuButton;

    PlayerStat* Profile;
    int players;
    Difficulty difficulty;
    clock_t game_started;
    int active_player;
    int moves_offset;
    bool was_renew;

    AI* Helper;
    vector<int> lastHintIndexes;
    CardSuit last;
    Card Cards[NUM_OF_SUITS*NUM_OF_VALUES];
    CardMaker* Maker;
    MainPlayer* Player;
    Enemy** Enemies;
    CardDeque* Deque;
    OpenCardDeque* OpenDeque;
    QWidget* Desk;


private:
    void GenerateCards();
    void GiveCardsToPlayers();
    void GiveOneCardFromDequeToPlayer(class Player* pl);
    bool CheckMovesAvailable(class Player* pl);
    void TakeAllOpenCards(class Player* pl);
    void UpdatePosibleNextCards(class Player* pl);
    void UpdateNextCards();
    void UpdateNextCards(class Player* pl);
    bool CheckIfWin(class Player* pl);
    void RenewDeque();
    int OnePlayerTact(class Player *pl);

    void ClearHintCards();
    void SetEnabledControlElements(bool);
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
    ~Game();
private slots:
    void OneGameTact();

    void DisplayHint();
    void PauseGame();
    void ResumeGame();
    void RestartGame();
    void EnterMainMenu();
public slots:
    void Init(int pl, Difficulty dif, PlayerStat*);
signals:
    void MainMenu();
};

#endif // GAME_H
