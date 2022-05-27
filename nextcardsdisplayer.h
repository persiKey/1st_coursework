#ifndef NEXTCARDSDISPLAYER_H
#define NEXTCARDSDISPLAYER_H

#include <QWidget>
#include <deque>
#include <constants.h>
#include <QHBoxLayout>
#include <playercarddisplayer.h>
#include <cardmaker.h>

using std::deque;

class NextCardsDisplayer : public QWidget
{
    Q_OBJECT
    deque<Card*>* NextCards;
    QHBoxLayout Layout;
    PlayerCardDisplayer Cards[13];
    CardMaker* Maker;
public:
    explicit NextCardsDisplayer(deque<Card*>* DisplCards,CardMaker* maker,QWidget *parent = nullptr);
    void UpdateNextCards();
signals:

};

#endif // NEXTCARDSDISPLAYER_H
