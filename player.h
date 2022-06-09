#ifndef PLAYER_H
#define PLAYER_H

#include <QLabel>
#include <vector>
#include <deque>
#include "playercardholder.h"
#include "enemycardholder.h"
#include "nextcardsdisplayer.h"
#include "ai.h"

using std::deque;
using Types::CardOrientation;
using Types::Difficulty;

class Person
{
    friend class Game;
protected:
    // Карти в руці
    vector<const Card*> Hand;
    // Можливі наступні карти
    deque<const Card*> PossibleNextCards;
    // Наступні карти
    deque<const Card*> NextCards;
    // Масть відкритої карти
    CardSuit* OpenSuit;
    // Відображувач кількості карт у руці
    QLabel* Counter;
public:
    Person ();
    //Додати карту в руку
    virtual void AddCard(const Card*);
    //Карти якими ходить
    virtual vector<const Card *> PlaceCards() = 0;
    //Встановити масть останньої відкритої карти для відслідковування
    virtual void SetDequeSuit(CardSuit*)  = 0;
    //Скинути всі налаштування і очистити всі колоди
    virtual void Clear() = 0;
    //Показати інтерфейсну частину
    virtual void Show() = 0;
    //Приховати інтерфейсну частину
    virtual void Hide() = 0;
    //Позначити, що хід перейшов до цього гравця
    virtual void SetFocus(bool);
    //Оновити відображувач кількості карт
    void UpdateCounter();
    virtual ~Person ();
};

class MainPlayer : public Person
{

private:
    // Візуальне представлення гравця
    PlayerCardHolder* Holder;
    // Відображувач наступних карт
    NextCardsDisplayer* Hint;
public:
    MainPlayer(QWidget* wnd,CardMaker* maker, bool is_hard);
    //Оновити відображувач наступних карт
    void UpdateHint();
    //Примусово оновити руку
    void UpdateHolder();
    //Очистити всі вибрані карти в руці
    void ResetChoosenCards();
    void AddCard(const Card* card) override;
    vector<const Card *> PlaceCards() override;
    void SetDequeSuit(CardSuit*) override;
    void Clear() override;
    void Show() override;
    void Hide() override;
    ~MainPlayer();
};

class Enemy : public Person
{
    Difficulty dif;
private:
    // Візуальне представлення противника
    EnemyCardHolder* Holder;
    // Штучний інтелект для прийняття рішень
    AI Ai;
public:
    Enemy(QWidget* wnd, CardOrientation, int x, int y);
    void AddCard(const Card* card) override;
    vector<const Card *> PlaceCards() override;
    void SetDequeSuit(CardSuit*) override;
    void Clear() override;
    void Show() override;
    void Hide() override;
    // Встановити рівень складності
    void SetDifficulty(Difficulty dif);
    ~Enemy();
};

#endif // PLAYER_H
