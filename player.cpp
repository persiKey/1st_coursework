#include "player.h"
#include <QDebug>
#include "func.h"
using namespace Constants;
Person::Person(){ }

void Person::AddCard(const Card * card)
{
    Hand.push_back(card);
}

void Person::SetFocus(bool f)
{
    if(f)
        Counter->setStyleSheet("font: 20px; color: #52D017;");
    else
        Counter->setStyleSheet("font: 13px; color: black;");
    ProcessAndPause(25);
}

void Person::UpdateCounter()
{
    Counter->setText(QString::number(Hand.size()));
}

Person::~Person(){}


MainPlayer::MainPlayer(QWidget *wnd, CardMaker *maker, bool is_hard)
{
    Holder = new PlayerCardHolder(wnd,maker,&Hand);
    Holder->move((WINDOW_WIDTH - PLAYER_HOLDER_WIDTH) /2,WINDOW_HEIGHT - CARD_HEIGHT);
    Holder->show();
    Counter = new QLabel(wnd);
    Counter->setFixedSize(COUNTER_SIZE,COUNTER_SIZE);
    Counter->move(WINDOW_WIDTH/2,WINDOW_HEIGHT-CARD_HEIGHT-COUNTER_SIZE - 10);
    Counter->show();
    Hint = nullptr;
    if(!is_hard)
    {
        Hint = new NextCardsDisplayer(&NextCards,&PossibleNextCards);
    }
    Person::UpdateCounter();
}

void MainPlayer::UpdateHint()
{
    if(Hint != nullptr)
        Hint->UpdateNextCards();
    ProcessAndPause(20);
}

void MainPlayer::UpdateHolder()
{
    Holder->update();
}

void MainPlayer::ResetChoosenCards()
{
    Holder->GetIndexes();
    Holder->ClearIndexes();
}

void MainPlayer::AddCard(const Card *card)
{
    Person::AddCard(card);
    Holder->AddCard();
    Person::UpdateCounter();
}

vector<const Card *> MainPlayer::PlaceCards()
{
    vector<int> CardsIndexes = Holder->GetIndexes();
    vector<const Card*> ExtractedCards;
    for(size_t i = 0; i < CardsIndexes.size();++i)
    {
        ExtractedCards.push_back(Hand[CardsIndexes[i]]);
        Hand[CardsIndexes[i]] = nullptr;
    }
    for(size_t i = 0; i < Hand.size();++i)
    {
        if(Hand[i] == nullptr)
        {
            Hand.erase(Hand.begin()+i);
            --i;
        }
    }
    Holder->ExtractCards();
    Person::UpdateCounter();
    return ExtractedCards;
}

void MainPlayer::SetDequeSuit(CardSuit *suit)
{
    Person::OpenSuit = suit;
    Holder->UpdateDequeSuit(suit);
}

void MainPlayer::Clear()
{
    Holder->GetIndexes();
    Hand.clear();
    NextCards.clear();
    PossibleNextCards.clear();
    if(Hint != nullptr) Hint->UpdateNextCards();
    Holder->ExtractCards();
    Person::UpdateCounter();
}

void MainPlayer::Show()
{
    Holder->show();
    Counter->show();
    if(Hint != nullptr)
    {
        if(!NextCards.empty() || !PossibleNextCards.empty())
            Hint->show();
    }
}

void MainPlayer::Hide()
{
    Holder->hide();
    Counter->hide();
    if(Hint != nullptr) Hint->hide();
}
#include <windows.h>
MainPlayer::~MainPlayer()
{
    if(Hint != nullptr) delete Hint;
}

Enemy::Enemy(QWidget *wnd, CardOrientation orient, int x, int y)
{
    Holder = new EnemyCardHolder(orient,wnd);
    Holder->move(x,y);
    Holder->show();
    Counter = new QLabel(wnd);
    Counter->setFixedSize(COUNTER_SIZE,COUNTER_SIZE);
    switch (orient) {
    case CardOrientation::HOR: Counter->move(x+Holder->size().width()/2,y+ENEMY_HOLDER_SIZE_VALUE+COUNTER_SIZE);break;
    case CardOrientation::VER: Counter->move(x+Holder->size().width()/2,y+CARD_HEIGHT+COUNTER_SIZE);break;
    }
    Counter->show();
    Person::UpdateCounter();
}

void Enemy::AddCard(const Card *card)
{
    Enemy::Person::AddCard(card);
    Holder->AddCard();
    Person::UpdateCounter();
}

vector<const Card *> Enemy::PlaceCards()
{
    vector<int> indexes;
    switch (dif) {
    case Difficulty::EASY: indexes = Ai.PrimitveDecide(Hand,*OpenSuit);break;
    default: indexes = Ai.Decide(&Hand,&NextCards,&PossibleNextCards,*OpenSuit);

    }
    if(Hand[indexes[0]]->Suit == *OpenSuit)
    {
        std::swap(indexes[0], indexes[1]);
    }
    vector<const Card*> result;
    for(size_t i = 0; i < indexes.size();++i)
    {
        if(Hand.size() <= VISIBLE_CARDS_IN_HAND)
            Holder->ExtractCard();
        result.push_back(Hand[indexes[i]]);
        Hand[indexes[i]] = nullptr;
    }
    for(size_t i = 0; i < Hand.size();++i)
    {
        if(Hand[i] == nullptr)
        {
            Hand.erase(Hand.begin()+i);
            --i;
        }
    }

    Person::UpdateCounter();
    return result;
}

void Enemy::SetDequeSuit(CardSuit *suit)
{
    Person::OpenSuit = suit;
}

void Enemy::Clear()
{
    Holder->ExtractAllCards();
    NextCards.clear();
    PossibleNextCards.clear();
    Hand.clear();
    Person::UpdateCounter();
}

void Enemy::Show()
{
    Holder->show();
    Counter->show();
}

void Enemy::Hide()
{
    Holder->hide();
    Counter->hide();
}

void Enemy::SetDifficulty(Difficulty dif)
{
    this->dif = dif;
}
