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
    vector<const Card*> Hand;
    deque<const Card*> PossibleNextCards;
    deque<const Card*> NextCards;
    CardSuit* OpenSuit;
    QLabel* Counter;
public:
    Person ();
    virtual void AddCard(const Card*);
    virtual vector<const Card *> PlaceCards() = 0;
    virtual void SetDequeSuit(CardSuit*)  = 0;
    virtual void Clear() = 0;
    virtual void Show() = 0;
    virtual void Hide() = 0;
    virtual void SetFocus(bool);
    void UpdateCounter();
    virtual ~Person ();
};

class MainPlayer : public Person
{

private:
    PlayerCardHolder* Holder;
    NextCardsDisplayer* Hint;
public:
    MainPlayer(QWidget* wnd,CardMaker* maker, bool is_hard);
    void UpdateHint();
    void UpdateHolder();
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
    EnemyCardHolder* Holder;
    AI Ai;
public:
    Enemy(QWidget* wnd, CardOrientation, int x, int y);
    void AddCard(const Card* card) override;
    vector<const Card *> PlaceCards() override;
    void SetDequeSuit(CardSuit*) override;
    void Clear() override;
    void Show() override;
    void Hide() override;
    void SetDifficulty(Difficulty dif);
};

#endif // PLAYER_H
