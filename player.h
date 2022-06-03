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

class Player
{
    friend class Game;
protected:
    vector<const Card*> Hand;
    deque<const Card*> PossibleNextCards;
    deque<const Card*> NextCards;
    CardSuit* OpenSuit;
    QLabel* Counter;
public:
    Player();
    virtual void AddCard(const Card*);
    virtual vector<const Card *> PlaceCards();
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
    void AddCard(const Card* card) override;
    vector<const Card *> PlaceCards() override;
    void SetDequeSuit(CardSuit*) override;
    void Clear() override;
    void Show() override;
    void Hide() override;
    ~MainPlayer();
};

class Enemy : public Player
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
