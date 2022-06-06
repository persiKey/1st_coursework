#ifndef ENEMYCARDHOLDER_H
#define ENEMYCARDHOLDER_H

#include "constants.h"
#include <QWidget>
#include <QPixmap>

using Types::CardOrientation;
using Constants::VISIBLE_CARDS_IN_HAND;

class EnemyCardDisplayer : public QWidget
{
    Q_OBJECT
    CardOrientation Orientation;

public:
    EnemyCardDisplayer(CardOrientation orient = CardOrientation::VER, QWidget *parent = nullptr );
    //Подія, що викликається при малюванні карти ворога
    void paintEvent(QPaintEvent *e);
    //Встановити орієнтацію карти
    void SetOrientation(CardOrientation orient);
};

class EnemyCardHolder : public QWidget
{
    Q_OBJECT
    QLayout* Layout;
    EnemyCardDisplayer VisibleCards[VISIBLE_CARDS_IN_HAND];
    CardOrientation Orientation;
    int VisibleCardsIndex;

public:
    explicit EnemyCardHolder(CardOrientation orient, QWidget *parent = nullptr);
    // Візуально додати одну карту
    void AddCard();
    // Візуально забрати одну карту
    void ExtractCard();
    // Візуально видалити всі карти з руки ворога
    void ExtractAllCards();

};

#endif // ENEMYCARDHOLDER_H
