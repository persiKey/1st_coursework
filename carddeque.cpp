#include "carddeque.h"
#include <QDebug>

CardDeque::CardDeque(QWidget *wnd, Card Cards[])
{
    Displayer = new DequeDisplayer(wnd);
    RandomCardGen(Cards);
    Displayer->move(300,300);
    Displayer->show();
}

Card *CardDeque::TakeCard()
{
    Card* card = Deque.back();
    Deque.pop_back();
    return card;
}

void CardDeque::RandomCardGen(Card Cards[])
{
    Deque.clear();
    srand(time(NULL));
    vector<int> indexes;
    for(int i =0; i < NUM_OF_SUITS*NUM_OF_VALUES;++i)
    {
        indexes.push_back(i);
    }
    int k;
    for(int i =0; i < NUM_OF_SUITS*NUM_OF_VALUES;++i)
    {
        k = rand() % indexes.size();
        Deque.push_back(&Cards[indexes[k]]);
        Displayer->AddCard();
        indexes.erase(indexes.begin()+k);
    }
}

OpenCardDeque::OpenCardDeque(QWidget *wnd, CardMaker *maker)
{
    Displayer = new OpenDequeDisplayer(wnd,maker);
    Displayer->move(600,300);
    Displayer->show();
}

void OpenCardDeque::PlaceCard(Card* card)
{
    Displayer->PrintCardOver(card);
}

void OpenCardDeque::PlaceCards(vector<Card *> &cards)
{
    for(auto card : cards)
    {
        Displayer->PrintCardOver(card);
    }
}

void OpenCardDeque::Clear()
{
    Displayer->ClearDeque();
}
