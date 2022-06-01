#ifndef PLAYER_H
#define PLAYER_H

#include <QLabel>
#include <vector>
#include <deque>
#include "playercardholder.h"
#include "enemycardholder.h"
#include <nextcardsdisplayer.h>
#include <ai.h>

using std::deque;
using Types::CardOrientation;

class Player
{
    friend class Game;
protected:
    vector<Card*> Hand;
    deque<Card*> PossibleNextCards;
    deque<Card*> NextCards;
    CardSuit* OpenSuit;
    QLabel* Counter;
public:
    Player();
    virtual void AddCard(Card*);
    virtual vector<Card *> PlaceCards();
    virtual void SetDequeSuit(CardSuit*);
    virtual void Clear();
    virtual void Show();
    virtual void Hide();
    virtual void SetFocus(bool);
    void UpdateCounter();
    virtual ~Player();
};

class MainPlayer : public Player
{

private:
    PlayerCardHolder* Holder;
    NextCardsDisplayer* Hint;
public:
    MainPlayer(QWidget* wnd,CardMaker* maker, bool is_hard);
    void UpdateHint();
    void UpdateHolder();
    void ResetChoosenCards();
    void AddCard(Card* card) override;
    vector<Card *> PlaceCards() override;
    void SetDequeSuit(CardSuit*) override;
    void Clear() override;
    void Show() override;
    void Hide() override;
    ~MainPlayer();
};

class Enemy : public Player
{
    int dif;
private:
    EnemyCardHolder* Holder;
    AI Ai;
public:
    Enemy(QWidget* wnd, CardOrientation, int x, int y);
    void AddCard(Card* card) override;
    vector<Card *> PlaceCards() override;
    void SetDequeSuit(CardSuit*) override;
    void Clear() override;
    void Show() override;
    void Hide() override;
    void SetDifficulty(int dif);
};

#endif // PLAYER_H
