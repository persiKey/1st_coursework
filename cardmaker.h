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

    const QPixmap* GetCard(CardSuit suit, CardValue value);
};

#endif // CARDMAKER_H
