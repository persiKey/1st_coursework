#ifndef CARDDEQUE_H
#define CARDDEQUE_H
#include <QLabel>
#include <dequedisplayer.h>
#include <vector>
using std::vector;

class CardDeque
{
    friend class Game;
    vector<Card*> Cards;
    DequeDisplayer* Displayer;
    QLabel* Counter;

public:
    CardDeque(QWidget* wnd, Card Cards[]);
    void RandomCardGen(Card[]);
    Card *TakeCard();
    void Clear();
    void Show();
    void Hide();
    ~CardDeque();
};

class OpenCardDeque
{
    friend class Game;
    vector<Card*> Cards;
    OpenDequeDisplayer* Displayer;
    QLabel* Counter;
public:
    OpenCardDeque(QWidget* wnd, CardMaker* maker);
    void PlaceCard(Card*);
    void PlaceCards(vector<Card*>&);
    void Clear();
    void Show();
    void Hide();
    ~OpenCardDeque();
};

#endif // CARDDEQUE_H
