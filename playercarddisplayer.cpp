#include "playercarddisplayer.h"
#include <QPainter>
#include<QMouseEvent>

#include "constants.h"

PlayerCardDisplayer::PlayerCardDisplayer(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(CARD_WIDTH,CARD_HEIGHT);
}

void PlayerCardDisplayer::updatePix(QPixmap *Pix)
{
    PixCard = Pix;
}

void PlayerCardDisplayer::setIndex(int ind)
{
    index = ind;
}


void PlayerCardDisplayer::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,CARD_WIDTH, CARD_HEIGHT,*PixCard);
    painter.end();
}
void PlayerCardDisplayer::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::MouseButton::LeftButton)
    {
        emit Choosen(index);
    }
}

void DrawCardBorder(QPainter *painter)
{
    painter->drawLine(0,0,CARD_WIDTH-1,0);
    painter->drawLine(0,0,0,CARD_HEIGHT-1);
    painter->drawLine(CARD_WIDTH-1,0,CARD_WIDTH-1, CARD_HEIGHT-1);
    painter->drawLine(0,CARD_HEIGHT-1,CARD_WIDTH-1, CARD_HEIGHT-1);
}

void PlayerCardDisplayer::printSelection()
{
    QPainter painter(PixCard);
    painter.setPen(Qt::green);
    DrawCardBorder(&painter);
    painter.end();
    this->update();
}

void PlayerCardDisplayer::unprintSelection()
{
    QPainter painter(PixCard);
    painter.setPen(Qt::black);
    DrawCardBorder(&painter);
    painter.end();
    this->update();
}
