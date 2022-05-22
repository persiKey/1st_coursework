#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QLabel>
#include <QGridLayout>

#include "player.h"
#include "carddeque.h"
#include "cardmaker.h"

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

    int players;
    int difficulty;

    CardSuit last;
    Card Cards[NUM_OF_SUITS*NUM_OF_VALUES];
    CardMaker* Maker;
    MainPlayer* Player;
    Enemy** Enemies;
    CardDeque* Deque;
    OpenCardDeque* OpenDeque;


private:
    void GenerateCards();
    void MainLoop();
    void GiveCardsToPlayers();
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
    void Init(int pl, int dif);
signals:
    void MainMenu();
};

#endif // GAME_H
