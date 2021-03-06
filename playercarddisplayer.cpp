#include "playercarddisplayer.h"
#include <QPainter>
#include<QMouseEvent>

#include "constants.h"
#include "cardmaker.h"

using Constants::CARD_WIDTH;
using Constants::CARD_HEIGHT;

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

void PlayerCardDisplayer::printSelection(QColor color)
{
    QPainter painter(PixCard);
    painter.setPen(color);
    CardMaker::DrawCardBorder(painter);
    painter.end();
    this->update();
}

void PlayerCardDisplayer::unprintSelection()
{
    QPainter painter(PixCard);
    painter.setPen(Qt::black);
    CardMaker::DrawCardBorder(painter);
    painter.end();
    this->update();
}
