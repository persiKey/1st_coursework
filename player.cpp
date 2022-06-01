#include "player.h"

using namespace Constants;
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

#include <QDebug>
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
    Player::UpdateCounter();
}

void MainPlayer::UpdateHint()
{
    if(Hint != nullptr)
        Hint->UpdateNextCards();
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
    NextCards.clear();
    PossibleNextCards.clear();
    Hint->UpdateNextCards();
    Holder->ExtractCards();
    Player::UpdateCounter();
}

void MainPlayer::Show()
{
    Holder->show();
    Counter->show();
    if(Hint != nullptr) Hint->show();
}

void MainPlayer::Hide()
{
    Holder->hide();
    Counter->hide();
    if(Hint != nullptr) Hint->hide();
}

MainPlayer::~MainPlayer()
{
    delete Hint;
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
    vector<int> indexes;
    switch (dif) {
    case 1: indexes = Ai.PrimitveDecide(Hand,*OpenSuit);break;
    default: indexes = Ai.Decide(&Hand,&NextCards,&PossibleNextCards,*OpenSuit);

    }
    if(Hand[indexes[0]]->Suit == *OpenSuit)
    {
        std::swap(indexes[0], indexes[1]);
    }
    vector<Card*> result;
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

    Player::UpdateCounter();
    return result;
}

void Enemy::SetDequeSuit(CardSuit *suit)
{
    Player::OpenSuit = suit;
}

void Enemy::Clear()
{
    Holder->ExtractAllCards();
    NextCards.clear();
    PossibleNextCards.clear();
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

void Enemy::SetDifficulty(int dif)
{
    this->dif = dif;
}
