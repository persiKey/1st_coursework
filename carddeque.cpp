#include "carddeque.h"
#include <QDebug>

CardDeque::CardDeque(QWidget *wnd, Card Cards[])
{
    Displayer = new DequeDisplayer(wnd);
    RandomCardGen(Cards);
    Counter = new QLabel(wnd);
    Counter->setFixedSize(20,20);
    Displayer->move(300,300);
    Counter->move(300,507);
    Counter->setText(QString::number(this->Cards.size()));
    Counter->show();
    Displayer->show();
}

Card *CardDeque::TakeCard()
{
    Card* card = Cards.back();
    Cards.pop_back();
    Counter->setText(QString::number(this->Cards.size()));
    if(Cards.size() < MAX_DEQUE_DISPLAYING_CARDS)
        Displayer->ExtractCard();
    return card;
}

void CardDeque::Clear()
{
    Cards.clear();
    Displayer->Clear();
    Counter->setText(QString::number(this->Cards.size()));
}

void CardDeque::Show()
{
    Displayer->show();
    Counter->show();
}

void CardDeque::Hide()
{
    Displayer->hide();
    Counter->hide();
}

CardDeque::~CardDeque()
{
    delete Counter;
}

void CardDeque::RandomCardGen(Card Cards[])
{
    this->Cards.clear();
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
        this->Cards.push_back(&Cards[indexes[k]]);
        Displayer->AddCard();
        indexes.erase(indexes.begin()+k);
    }
}

OpenCardDeque::OpenCardDeque(QWidget *wnd, CardMaker *maker)
{
    Displayer = new OpenDequeDisplayer(wnd,maker);
    Displayer->move(600,300);
    Displayer->show();
    Counter = new QLabel(wnd);
    Counter->setFixedSize(20,20);
    Counter->move(600,507);
    Counter->setText(QString::number(this->Cards.size()));
    Counter->show();
}

void OpenCardDeque::PlaceCard(Card* card)
{
    Cards.push_back(card);
    Displayer->PrintCardOver(card);
    Counter->setText(QString::number(this->Cards.size()));
}

void OpenCardDeque::PlaceCards(vector<Card *> &cards)
{
    for(auto card : cards)
    {
        Cards.push_back(card);
        Displayer->PrintCardOver(card);
    }
    Counter->setText(QString::number(this->Cards.size()));
}

void OpenCardDeque::Clear()
{
    Cards.clear();
    Displayer->ClearDeque();
    Counter->setText(QString::number(this->Cards.size()));
}

void OpenCardDeque::Show()
{
    Displayer->show();
    Counter->show();
}

void OpenCardDeque::Hide()
{
    Displayer->hide();
    Counter->hide();
}

OpenCardDeque::~OpenCardDeque()
{
    delete Counter;
}
