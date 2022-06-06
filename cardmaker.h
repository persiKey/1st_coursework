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

    //Створити карту "Туз"
    void MakeAce(QPainter &painter, QPixmap &PixSuit);
    //Завантажує текстуру відповідної масті
    void SetSuit(QPixmap &PixSuit, CardSuit suit);
    //Визначає символ, що позначає значення карти
    char GetPrintValue(CardValue value);
    //Створює нову карту
    QPixmap* CreateCard(CardSuit suit, CardValue value);
public:
    CardMaker();
    ~CardMaker();

    //Отримати текстуру карти
    QPixmap* GetCard(CardSuit suit, CardValue value);
    QPixmap* GetCard(const Card &card);
    //Отримати текстуру рубашки карти
    static QPixmap* GetCover();
    //Намалювати по краям карти
    static void DrawCardBorder(QPainter&);
};
#endif // CARDMAKER_H
