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
    const deque<const Card*>* NextCards;
    const deque<const Card*>* PossibleNextCards;
    QHBoxLayout Layout;
    PlayerCardDisplayer Cards[Constants::MAX_NEXT_CARDS];
    CardMaker Maker;
public:
    explicit NextCardsDisplayer(const deque<const Card*>* DisplCards,const deque<const Card*>* PossibleCards,QWidget *parent = nullptr);
    void UpdateNextCards();
signals:

};

#endif // NEXTCARDSDISPLAYER_H
