#ifndef PLAYER_H
#define PLAYER_H

#include <QLabel>
#include <vector>
#include "playercardholder.h"
#include "enemycardholder.h"

class Player
{
    friend class Game;
protected:
    vector<Card*> Hand;
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
    void UpdateCounter();
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
    void Show() override;
    void Hide() override;
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
    void Show() override;
    void Hide() override;
};

#endif // PLAYER_H
