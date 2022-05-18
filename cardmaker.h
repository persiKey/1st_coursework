#ifndef CARDMAKER_H
#define CARDMAKER_H

#include "constants.h"
#include <QPixmap>
#include <QPainter>

class CardMaker
{
    QPixmap*** CachedCards;
    QFont Font;
    QPixmap* CreateCard(CardSuit suit, CardValue value);
public:
    CardMaker();
    ~CardMaker();

    QPixmap* GetCard(CardSuit suit, CardValue value);
    QPixmap* GetCard(Card &card);
};

#endif // CARDMAKER_H
