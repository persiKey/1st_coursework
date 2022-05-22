#ifndef CARDDEQUE_H
#define CARDDEQUE_H

#include <dequedisplayer.h>
#include <vector>
using std::vector;

class CardDeque
{
    friend class Game;
    vector<Card*> Cards;
    DequeDisplayer* Displayer;


public:
    CardDeque(QWidget* wnd, Card Cards[]);
    void RandomCardGen(Card[]);
    Card *TakeCard();
    void Clear();
};

class OpenCardDeque
{
    friend class Game;
    vector<Card*> Cards;
    OpenDequeDisplayer* Displayer;
public:
    OpenCardDeque(QWidget* wnd, CardMaker* maker);
    void PlaceCard(Card*);
    void PlaceCards(vector<Card*>&);
    void Clear();
};

#endif // CARDDEQUE_H
