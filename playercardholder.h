#ifndef PLAYERCARDHOLDER_H
#define PLAYERCARDHOLDER_H

#include <QObject>
#include <QWidget>
#include <QPushButton>

#include "playercarddisplayer.h"
#include "constants.h"
#include "cardmaker.h"
#include <vector>
using std::vector;



class PlayerCardHolder : public QWidget
{
    Q_OBJECT
    vector<Card*> AllCards;
    vector<int> ChoosenCardsIndexes;
    PlayerCardDisplayer VisibleCards[VISIBLE_CARDS_IN_HAND];
    QLayout* Layout;
    QPushButton CtrlLeft;
    QPushButton CtrlRight;
    int display_pos;
    CardMaker *cardMaker;

    void UpdateVisibleCards();
    void ShowCtrlButtons();
    void HideCtrlButtons();
public:
    explicit PlayerCardHolder(QWidget *parent = nullptr, CardMaker* maker = nullptr);
    void AddCard(Card *card);
    void ExtractCards();
private slots:
    void CheckLeft();
    void CheckRight();
public slots:
    void CardChoosen(int);
};

#endif // PLAYERCARDHOLDER_H
