#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "playercardholder.h"
#include "enemycardholder.h"

class Player
{
    friend class Game;
protected:
    vector<Card*> Hand;
    CardSuit* OpenSuit;
public:
    Player();
    virtual void AddCard(Card*);
    virtual vector<Card *> PlaceCards();
    virtual void SetDequeSuit(CardSuit*);
    virtual void Clear();
    virtual ~Player();
};

class MainPlayer : public Player
{
    friend class Game;
private:
    PlayerCardHolder* Holder;
public:
    MainPlayer(QWidget* wnd,CardMaker* maker);
    void AddCard(Card* card) override;
    vector<Card *> PlaceCards() override;
    void SetDequeSuit(CardSuit*) override;
    void Clear() override;
};

class Enemy : public Player
{
    friend class Game;
private:
    EnemyCardHolder* Holder;
public:
    Enemy(QWidget* wnd, CardOrientation, int x, int y);
    void AddCard(Card* card) override;
    vector<Card *> PlaceCards() override;
    void SetDequeSuit(CardSuit*) override;
    void Clear() override;
};

#endif // PLAYER_H
