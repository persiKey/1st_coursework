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

using Constants::VISIBLE_CARDS_IN_HAND;
using Types::Card;
using Types::CardSuit;
using Types::CardValue;

class PlayerCardHolder : public QWidget
{
    Q_OBJECT
    QLayout* Layout;
    QPushButton CtrlLeft;
    QPushButton CtrlRight;

    CardMaker *cardMaker;
    PlayerCardDisplayer VisibleCards[VISIBLE_CARDS_IN_HAND];
    int display_pos;

    const vector<const Card*>* HandCards;
    vector<int> ChoosenCardsIndexes;
    CardSuit *DequeSuit;
    CardValue SelectedValue;

    void UpdateVisibleCards();
    void UpdateExtractedCards();
    void ShowCtrlButtons();
    void HideCtrlButtons();

public:
    explicit PlayerCardHolder(QWidget *parent = nullptr, CardMaker* maker = nullptr,const vector<const Card*>* Cards= nullptr);
    void AddCard();

    void ExtractCards();
    vector<int> GetIndexes();
    void ClearIndexes();
    void UpdateDequeSuit(CardSuit *suit);

private slots:
    void CheckLeft();
    void CheckRight();

public slots:
    void CardChoosen(int);
};

#endif // PLAYERCARDHOLDER_H
