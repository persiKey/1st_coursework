#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include <QObject>

#include "constants.h"
#include "cardmaker.h"

#include "playercardholder.h"
class Test : public QWidget
{
    Q_OBJECT
    QPixmap Pm;
    CardMaker maker;
    CardSuit SuitCouter;
    CardValue ValueCounter;
    PlayerCardHolder* Hld;
public:
    explicit Test(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent* e);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *e);
    //void moveEvent(QMoveEvent* e);
};

#endif // TEST_H
