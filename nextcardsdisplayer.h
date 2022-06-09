#ifndef NEXTCARDSDISPLAYER_H
#define NEXTCARDSDISPLAYER_H

#include <QWidget>
#include <deque>
#include <constants.h>
#include <QHBoxLayout>
#include <playercarddisplayer.h>
#include <cardmaker.h>

using std::deque;
using Constants::MAX_NEXT_CARDS;
class NextCardsDisplayer : public QWidget
{
    Q_OBJECT
    // Наступні карти для показу
    const deque<const Card*>* NextCards;
    // Можливі наступні карти для показу
    const deque<const Card*>* PossibleNextCards;
    // Розміщення елеметів
    QHBoxLayout Layout;
    // Форми, які будуть показувати текстури карт
    PlayerCardDisplayer Cards[MAX_NEXT_CARDS];
    // Інструмент для створення та збереження текстур карт
    CardMaker Maker;
public:
    explicit NextCardsDisplayer(const deque<const Card*>* DisplCards,const deque<const Card*>* PossibleCards,QWidget *parent = nullptr);
    //Оновити наступні та можливі наступні карти
    void UpdateNextCards();
signals:

};

#endif // NEXTCARDSDISPLAYER_H
