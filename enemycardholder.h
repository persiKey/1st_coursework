#ifndef ENEMYCARDHOLDER_H
#define ENEMYCARDHOLDER_H

#include "constants.h"
#include <QWidget>
#include <QPixmap>
class EnemyCardDisplayer : public QWidget
{
    Q_OBJECT
    QPixmap* cover;
    CardOrientation Orientation;

public:
    EnemyCardDisplayer(CardOrientation orient = CardOrientation::VER, QWidget *parent = nullptr );
    void paintEvent(QPaintEvent *e);
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

public slots:
    void AddCard();
    void ExtractCard();

};

#endif // ENEMYCARDHOLDER_H
