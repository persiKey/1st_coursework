#ifndef CARDMAKER_H
#define CARDMAKER_H

#include "constants.h"
#include <QPixmap>
#include <QPainter>

using Types::CardValue;
using Types::CardSuit;
using Types::Card;

class CardMaker
{
    QPixmap*** CachedCards;
    static QPixmap* CachedCover;
    QFont Font;
    QPixmap* CreateCard(CardSuit suit, CardValue value);
public:
    CardMaker();
    ~CardMaker();

    QPixmap* GetCard(CardSuit suit, CardValue value);
    QPixmap* GetCard(Card &card);
    static QPixmap* GetCover();
};
void DrawCardBorder(QPainter&);
#endif // CARDMAKER_H
