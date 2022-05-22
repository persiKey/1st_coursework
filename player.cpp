#include "player.h"

Player::Player(){ }

void Player::AddCard(Card * card)
{
    Hand.push_back(card);
}

vector<Card *> Player::PlaceCards()
{
    return vector<Card*>{};
}

void Player::SetDequeSuit(CardSuit*){}

void Player::Clear(){}

void Player::Show(){}

void Player::Hide(){}

void Player::UpdateCounter()
{
    Counter->setText(QString::number(Hand.size()));
}

Player::~Player(){delete Counter;}


MainPlayer::MainPlayer(QWidget *wnd, CardMaker *maker)
{
    Holder = new PlayerCardHolder(wnd,maker,&Hand);
    Holder->move(190,720-170);
    Holder->show();
    Counter = new QLabel(wnd);
    Counter->setFixedSize(20,20);
    Counter->move(1300/2,720-170-30);
    Counter->show();
    Player::UpdateCounter();
}

void MainPlayer::AddCard(Card *card)
{
    Player::AddCard(card);
    Holder->AddCard();
    Player::UpdateCounter();
}

vector<Card *> MainPlayer::PlaceCards()
{
    vector<int> CardsIndexes = Holder->GetIndexes();
    vector<Card*> ExtractedCards;
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
    Player::UpdateCounter();
    return ExtractedCards;
}

void MainPlayer::SetDequeSuit(CardSuit *suit)
{
    Player::OpenSuit = suit;
    Holder->UpdateDequeSuit(suit);
}

void MainPlayer::Clear()
{
    Holder->GetIndexes();
    Hand.clear();
    Holder->ExtractCards();
    Player::UpdateCounter();
}

void MainPlayer::Show()
{
    Holder->show();
    Counter->show();
}

void MainPlayer::Hide()
{
    Holder->hide();
    Counter->hide();
}

Enemy::Enemy(QWidget *wnd, CardOrientation orient, int x, int y)
{
    Holder = new EnemyCardHolder(orient,wnd);
    Holder->move(x,y);
    Holder->show();
    Counter = new QLabel(wnd);
    Counter->setFixedSize(20,20);
    switch (orient) {
    case CardOrientation::HOR: Counter->move(x,y+710+20);break;
    case CardOrientation::VER: Counter->move(x,y+170+20);break;
    }
    Counter->show();
    Player::UpdateCounter();
}

void Enemy::AddCard(Card *card)
{
    Enemy::Player::AddCard(card);
    Holder->AddCard();
    Player::UpdateCounter();
}

vector<Card *> Enemy::PlaceCards()
{
    Holder->ExtractCard();
    Card* res = Hand.back();
    Hand.pop_back();
    Player::UpdateCounter();
    return vector<Card*>{res};
}

void Enemy::SetDequeSuit(CardSuit *suit)
{
    Player::OpenSuit = suit;
}

void Enemy::Clear()
{
    Holder->ExtractAllCards();
    Hand.clear();
    Player::UpdateCounter();
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
