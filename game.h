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
    //Створити унікальні карти в пам'яті
    void GenerateCards();
    // Роздати карти та підготовитись до початку партії
    void GiveCardsToPlayers();
    // Дати одну карту з основної колоди гравцю
    void GiveOneCardFromDequeToPlayer( Person * pl);
    // Перевірити, чи гравець може походити
    bool CheckMovesAvailable( Person * pl);
    // Передати всі відкриті карти гравцю в руку
    void TakeAllOpenCards( Person * pl);
    // Оновити можливі наступні карти гравця
    void UpdatePosibleNextCards( Person * pl);
    // Оновити наступні карти усіх гравців після оновлення колоди
    void UpdateNextCards();
    // Оновити наступні карти певного гравця при ході
    void UpdateNextCards( Person * pl);
    // Перевірити чи виграв гравець
    bool CheckIfWin( Person * pl);
    // Оновити основну колоду
    void RenewDeque();
    // Один цикл гравця
    int OnePlayerTact( Person  *pl);

    // Очистити виділення карт, що були підказані
    void ClearHintCards();
    // Встановити активними елементи управління користувача
    void SetEnabledControlElements(bool);
    // Приховати ігрові елементи
    void HideGameElements();
    // Показати ігрові елементи
    void ShowGameElements();
    // Приховати елементи меню
    void HideMenuElements();
    // Показати елементи меню
    void ShowMenuElements();
    // Звільнити ресурси, які займають ігрові об'єкти
    void FreeResourses();
    // Очистити всі ігрові об'єкти та почати гру заново
    void Restart();
    // Заповнити сататистику гравця залежні від виграшу/програшу
    void FillPlayerStat(bool win);
    // Вивести повідомлення про виграш/програш
    void DisplayWinLoose(QString msg);

    // Виділити ресурси під елементи меню та налаштувати їх
    void InitMenuElements();
    // Звільнити ресурси, що займали елементи меню
    void DeleteMenuElements();
public:
    explicit Game(QObject *parent = nullptr);
    // Встановити вікно, на якому все буде відображатися
    void setWnd(QWidget* wnd);
    ~Game();
private slots:
    // Подія, що відповідає за один ігровий такт, коли натиснуто кнопку "Зробити хід"
    void OneGameTact();
    // Подія, що відповідає за виділення підказаних карт, коли натисунто кнопку "?"
    void DisplayHint();
    // Подія, що відповідає за відображення ігрового меню паузи, коли натиснуто на кнопку паузи
    void PauseGame();
    // Подія, що відповідає за продовження гри, коли натиснуто кнопку "Продовжити"
    void ResumeGame();
    // Подія, що відповідає за перезапуск гри, коли натиснуто кнопку "Заново"
    void RestartGame();
    // Подія, що відповідає за вихід до нового меню, коли натиснуто кнопку "Головне меню"
    void EnterMainMenu();
public slots:
    // Подія, що відповідає за налаштування та ініціалізацію усіх ігрових елементів за переданими параметрами
    void Init(int pl, Difficulty dif, PlayerStat*);
signals:
    void MainMenu();
};

#endif // GAME_H
