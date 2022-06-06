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
    //Тасування(випадкова генерація) карт в колоді
    void RandomCardGen(const Card[]);
    //Взяти верхню карту з колоди
    const Card *TakeCard();
    //Очистити колоду логічно і візуально
    void Clear();
    //Показати колоду
    void Show();
    //Приховати колоду
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
    //Покласти дану карту поверх колоду
    void PlaceCard(const Card*);
    //Покласти дані карти поверх колоди
    void PlaceCards(const vector<const Card*>&);
    //Очистити колоду
    void Clear();
    //Показати колоду
    void Show();
    //Приховати колоду
    void Hide();
    ~OpenCardDeque();
};

#endif // CARDDEQUE_H
