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
    void AddCard(Card*);
    vector<Card *> PlaceCards();
    void SetDequeSuit(CardSuit);
};

class MainPlayer : public Player
{
private:
    PlayerCardHolder* Holder;
public:
    MainPlayer(QWidget* wnd,CardMaker* maker);
    void AddCard(Card* card);
    vector<Card *> PlaceCards();
    void SetDequeSuit(CardSuit);
};

class Enemy : public Player
{

private:
    EnemyCardHolder* Holder;
public:
    Enemy(QWidget* wnd, CardOrientation, int x, int y);
    void AddCard(Card* card);
    vector<Card *> PlaceCards();
};

#endif // PLAYER_H
