#include "enemycardholder.h"
#include <QPainter>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "cardmaker.h"

using Constants::CARD_HEIGHT;
using Constants::CARD_WIDTH;
using Constants::VISIBLE_CARDS_SPACING;
using Constants::ENEMY_HOLDER_SIZE_VALUE;
EnemyCardDisplayer::EnemyCardDisplayer(CardOrientation orient, QWidget *parent) : QWidget(parent), Orientation(orient)
{
    SetOrientation(orient);
}

void  EnemyCardDisplayer::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    if(Orientation == CardOrientation::HOR)
    {
        painter.translate(0,CARD_WIDTH);
        painter.rotate(-90);
    }
    painter.drawPixmap(0,0,CARD_WIDTH, CARD_HEIGHT,*CardMaker::GetCover());
    painter.end();

}

void EnemyCardDisplayer::SetOrientation(CardOrientation orient)
{
    Orientation = orient;
    switch (Orientation) {
    case CardOrientation::HOR : this->setFixedSize(CARD_HEIGHT, CARD_WIDTH);break;
    case CardOrientation::VER : this->setFixedSize(CARD_WIDTH, CARD_HEIGHT);break;
    }
}

EnemyCardHolder::EnemyCardHolder(CardOrientation orient, QWidget *parent) : Orientation(orient), QWidget(parent)
{
    switch (Orientation) {
    case CardOrientation::HOR :
        Layout = new QVBoxLayout;
        this->setFixedSize(CARD_HEIGHT,ENEMY_HOLDER_SIZE_VALUE);
        break;
    case CardOrientation::VER :
        Layout = new QHBoxLayout;
        this->setFixedSize(ENEMY_HOLDER_SIZE_VALUE, CARD_HEIGHT);
        break;
    }

    Layout->setSpacing(VISIBLE_CARDS_SPACING);
    Layout->setContentsMargins(0,0,0,0);
    for (int i = 0; i < VISIBLE_CARDS_IN_HAND ;++i )
    {
        VisibleCards[i].SetOrientation(this->Orientation);
        VisibleCards[i].hide();
        Layout->addWidget(VisibleCards+i);
    }
    VisibleCardsIndex = -1;
    this->setLayout(Layout);
}

void EnemyCardHolder::AddCard()
{
    if(VisibleCardsIndex + 1 >= VISIBLE_CARDS_IN_HAND) return;
    VisibleCards[++VisibleCardsIndex].show();
}

void EnemyCardHolder::ExtractCard()
{
    if(VisibleCardsIndex < 0) return;
    VisibleCards[VisibleCardsIndex--].hide();

}

void EnemyCardHolder::ExtractAllCards()
{
    for(int i = 0; i < VisibleCardsIndex;++i)
    {
        VisibleCards[i].hide();
    }
    VisibleCardsIndex = -1;
}
