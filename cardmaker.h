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

    void MakeAce(QPainter &painter, QPixmap &PixSuit);
    void SetSuit(QPixmap &PixSuit, CardSuit suit);
    char GetPrintValue(CardValue value);
    QPixmap* CreateCard(CardSuit suit, CardValue value);
public:
    CardMaker();
    ~CardMaker();

    QPixmap* GetCard(CardSuit suit, CardValue value);
    QPixmap* GetCard(const Card &card);
    static QPixmap* GetCover();
    static void DrawCardBorder(QPainter&);
};
#endif // CARDMAKER_H
