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
    // Орієнтація карти
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
    // Розміщення елементів
    QLayout* Layout;
    // Відображувачі карт
    EnemyCardDisplayer VisibleCards[VISIBLE_CARDS_IN_HAND];
    // Орієнтація
    CardOrientation Orientation;
    // Індекс карт, що відображуються
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
