#include "test.h"
#include <QPainter>
#include <QMouseEvent>

Test::Test(QWidget *parent) : QWidget(parent), Pm(CARD_WIDTH,CARD_HEIGHT)
{
//    Pm.fill(QColor::fromRgb(255,255,255));
//    //Pm.load("F:\\Projects\\Qt\\Chicken\\card_back.jpg");
//    QFont fn("Hoyle Playing Cards", 28, QFont::Normal);
//    QPixmap m;
//    m.load("F:\\Projects\\Qt\\Chicken\\src\\ace.png");

//    m = m.transformed(QTransform().rotate(180),Qt::SmoothTransformation);
//    QBrush br(Qt::red);
//    QPainter pn;
//    pn.begin(&Pm);
//    pn.setBrush(br);
//    pn.setPen(Qt::red);
//    pn.setFont(fn);


//    pn.drawPixmap(0,0,40,40,m);
//    pn.save();
//    pn.translate(55, 85);
//    pn.rotate(180);
//    pn.drawText(0,0,"f");
//    pn.restore();
//    pn.end();

    SuitCouter = CardSuit::HEARTS;
    ValueCounter = CardValue::ACE;
    Pm = *maker.GetCard(CardSuit::HEARTS, CardValue::ACE);

    this->setFixedSize(110,170);

}

void Test::paintEvent(QPaintEvent *e)
{
    QPainter paint(this);
    paint.drawPixmap(0,0,110,170,Pm);
    paint.end();

}
#include <QDebug>
void Test::mousePressEvent(QMouseEvent *e)
{

    if(e->button() == Qt::MouseButton::LeftButton )
    {
        ValueCounter = CardValue(((int)ValueCounter+1)%9);
        Pm = *maker.GetCard(SuitCouter,ValueCounter);
        qDebug() << "Left mouse button was pressed on a card";
        this->update();
    }
    else if(e->button() == Qt::MouseButton::RightButton )
    {
        SuitCouter = CardSuit(((int)SuitCouter+1)%4);
        Pm = *maker.GetCard(SuitCouter,ValueCounter);
        this->update();
    }
}

