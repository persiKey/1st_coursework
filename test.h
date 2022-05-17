#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include <QObject>

#include "constants.h"
#include "cardmaker.h"
class Test : public QWidget
{
    Q_OBJECT
    QPixmap Pm;
    CardMaker maker;
    CardSuit SuitCouter;
    CardValue ValueCounter;
public:
    explicit Test(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent* e);
    void mousePressEvent(QMouseEvent *event);
};

#endif // TEST_H
