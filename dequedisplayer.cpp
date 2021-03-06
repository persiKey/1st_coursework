#include "dequedisplayer.h"
#include "constants.h"
#include <QPainter>

#include <random>
#include <time.h>

using namespace Constants;

DequeDisplayer::DequeDisplayer(QWidget *parent) : QWidget(parent), deque(DEQUE_WIDTH, DEQUE_HEIGHT)
{
    srand(time(NULL));
    this->setFixedSize(DEQUE_WIDTH,DEQUE_HEIGHT);
    Clear();
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
        painter.drawPixmap(offset,0,DEQUE_SPACING, CARD_HEIGHT,*CardMaker::GetCover(),0,0,DEQUE_SPACING,CARD_HEIGHT);
        offset += DEQUE_OFFSET;
    }
    painter.drawPixmap(offset,0,CARD_WIDTH,CARD_HEIGHT,*CardMaker::GetCover());
    painter.end();
}

void DequeDisplayer::AddCard()
{
    if(DisplayedCardsCount >= MAX_DEQUE_DISPLAYING_CARDS-1) return;
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

void DequeDisplayer::Clear()
{
    DisplayedCardsCount = -1;
    ClearDeque();
}


void DequeDisplayer::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,DEQUE_WIDTH,DEQUE_HEIGHT,deque);
    painter.end();
}

//OPEN DEQUE DISPLAYER

OpenDequeDisplayer::OpenDequeDisplayer(QWidget *parent, CardMaker *maker) : QWidget(parent), maker(maker), deque(DEQUE_WIDTH, DEQUE_HEIGHT)
{
    this->setFixedSize(DEQUE_WIDTH,DEQUE_HEIGHT);
    ClearDeque();
}

void OpenDequeDisplayer::ClearDeque()
{
    deque.fill(Qt::darkGreen);
    this->update();
}

void OpenDequeDisplayer::PrintCardOver(const Card *card)
{
    QPixmap* PixCard = maker->GetCard(*card);
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
