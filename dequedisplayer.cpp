#include "dequedisplayer.h"
#include "constants.h"
#include <QPainter>

#include <random>
#include <time.h>

DequeDisplayer::DequeDisplayer(QWidget *parent) : QWidget(parent), deque(DEQUE_WIDTH, DEQUE_HEIGHT)
{
    srand(time(NULL));
    this->setFixedSize(DEQUE_WIDTH,DEQUE_HEIGHT);
    DisplayedCardsCount = -1;
    ClearDeque();
}

void DequeDisplayer::ClearDeque()
{
    deque.fill(Qt::darkGreen);
}

void DequeDisplayer::DrawCoverCards()
{
    if(DisplayedCardsCount < 0) return;
    int offset = 0;
    QPainter painter(&deque);
    for(int i = 0; i < DisplayedCardsCount;++i)
    {
        //painter.drawPixmap(offset,0,50, CARD_HEIGHT,*cover,0,0,CARD_WIDTH,CARD_HEIGHT);
        painter.drawPixmap(offset,0,CARD_WIDTH,CARD_HEIGHT,*cover);
        offset += 5;
    }
    painter.drawPixmap(offset,0,CARD_WIDTH,CARD_HEIGHT,*cover);
    painter.end();
}

void DequeDisplayer::AddCard()
{
    if(DisplayedCardsCount >= 4) return;
    ++DisplayedCardsCount;
    DrawCoverCards();
    this->update();
}

void DequeDisplayer::ExtractCard()
{
    if(DisplayedCardsCount < 0) return;
    --DisplayedCardsCount;
    ClearDeque();
    DrawCoverCards();
    this->update();
}

void DequeDisplayer::SetCover(QPixmap * cov)
{
    this->cover = cov;
}

void DequeDisplayer::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,DEQUE_WIDTH,DEQUE_HEIGHT,deque);
    painter.end();
}

OpenDequeDisplayer::OpenDequeDisplayer(QWidget *parent, CardMaker *maker) : QWidget(parent), maker(maker), deque(DEQUE_WIDTH, DEQUE_HEIGHT)
{
    this->setFixedSize(DEQUE_WIDTH,DEQUE_HEIGHT);
    ClearDeque();
}

void OpenDequeDisplayer::SetCardMaker(CardMaker *maker)
{
    this->maker = maker;
}

void OpenDequeDisplayer::ClearDeque()
{
    deque.fill(Qt::darkGreen);
    this->update();
}

void OpenDequeDisplayer::PrintCardOver(Card card)
{
    QPixmap* PixCard = maker->GetCard(card);
    QPainter painter(&deque);
    int offset = rand() % 20;
    painter.drawPixmap(offset,0,CARD_WIDTH,CARD_HEIGHT,*PixCard);
    painter.end();
    this->update();
}

void OpenDequeDisplayer::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,DEQUE_WIDTH,DEQUE_HEIGHT,deque);
    painter.end();
}
