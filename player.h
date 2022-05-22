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
public:
    Player();
    virtual void AddCard(Card*);
    virtual vector<Card *> PlaceCards();
    virtual void SetDequeSuit(CardSuit);
};

class MainPlayer : public Player
{
private:
    PlayerCardHolder* Holder;
public:
    MainPlayer(QWidget* wnd,CardMaker* maker);
    void AddCard(Card* card) override;
    vector<Card *> PlaceCards() override;
    void SetDequeSuit(CardSuit) override;
};

class Enemy : public Player
{

private:
    EnemyCardHolder* Holder;
    CardSuit last;
public:
    Enemy(QWidget* wnd, CardOrientation, int x, int y);
    void AddCard(Card* card) override;
    vector<Card *> PlaceCards() override;
    void SetDequeSuit(CardSuit) override;
};

#endif // PLAYER_H
