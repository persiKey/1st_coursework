#include "carddeque.h"
#include <QDebug>

using Constants::MAX_DEQUE_DISPLAYING_CARDS;
using Constants::NUM_OF_SUITS;
using Constants::NUM_OF_VALUES;
using Constants::COUNTER_SIZE;
using namespace Constants;
void ProcessAndPause(int msec);

CardDeque::CardDeque(QWidget *wnd, Card Cards[])
{
    Displayer = new DequeDisplayer(wnd);
    RandomCardGen(Cards);
    Counter = new QLabel(wnd);
    Counter->setFixedSize(COUNTER_SIZE,COUNTER_SIZE);
    Displayer->move((WINDOW_WIDTH-PLAYER_HOLDER_WIDTH)/2,WINDOW_HEIGHT/2.5);
    Counter->move((WINDOW_WIDTH-PLAYER_HOLDER_WIDTH + Displayer->size().width())/2,WINDOW_HEIGHT/2.5 + Displayer->size().height());
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
    Counter = new QLabel(wnd);
    Counter->setFixedSize(COUNTER_SIZE,COUNTER_SIZE);
    Displayer->move((WINDOW_WIDTH-PLAYER_HOLDER_WIDTH)/2 + PLAYER_HOLDER_WIDTH - Displayer->size().width(),WINDOW_HEIGHT/2.5);
    Counter->move((WINDOW_WIDTH-PLAYER_HOLDER_WIDTH + Displayer->size().width())/2 + PLAYER_HOLDER_WIDTH - Displayer->size().width(),WINDOW_HEIGHT/2.5 + Displayer->size().height());
    Counter->setText(QString::number(this->Cards.size()));
    Displayer->show();
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
        Displayer->update();
        ProcessAndPause(500);
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
