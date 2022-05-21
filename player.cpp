#include "player.h"

Player::Player()
{

}

void Player::AddCard(Card * card)
{
    Hand.push_back(card);
}


MainPlayer::MainPlayer(QWidget *wnd, CardMaker *maker)
{
    Holder = new PlayerCardHolder(wnd,maker,&Hand);
    Holder->move(190,720-170);
    Holder->show();
}

void MainPlayer::AddCard(Card *card)
{
    Player::AddCard(card);
    Holder->AddCard();
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
    return ExtractedCards;
}

void MainPlayer::SetDequeSuit(CardSuit suit)
{
    Holder->UpdateDequeSuit(suit);
}

Enemy::Enemy(QWidget *wnd, CardOrientation orient, int x, int y)
{
    Holder = new EnemyCardHolder(orient,wnd);
    Holder->move(x,y);
    Holder->show();
}

void Enemy::AddCard(Card *card)
{
    Enemy::Player::AddCard(card);
    Holder->AddCard();
}

vector<Card *> Enemy::PlaceCards()
{
    Holder->ExtractCard();
    Card* res = Hand.back();
    Hand.pop_back();
    return vector<Card*>{res};
}