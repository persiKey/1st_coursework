#ifndef CARDDEQUE_H
#define CARDDEQUE_H
#include <QLabel>
#include <dequedisplayer.h>
#include <vector>
using std::vector;

class CardDeque
{
    friend class Game;
    vector<const Card*> Cards;
    DequeDisplayer* Displayer;
    QLabel* Counter;

public:
    CardDeque(QWidget* wnd,const Card Cards[]);
    void RandomCardGen(const Card[]);
    const Card *TakeCard();
    void Clear();
    void Show();
    void Hide();
    ~CardDeque();
};

class OpenCardDeque
{
    friend class Game;
    vector<const Card*> Cards;
    OpenDequeDisplayer* Displayer;
    QLabel* Counter;
public:
    OpenCardDeque(QWidget* wnd, CardMaker* maker);
    void PlaceCard(const Card*);
    void PlaceCards(const vector<const Card*>&);
    void Clear();
    void Show();
    void Hide();
    ~OpenCardDeque();
};

#endif // CARDDEQUE_H
