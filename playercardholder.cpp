#include "playercardholder.h"
#include <QVBoxLayout>

#include <QDebug>

using namespace Constants;

PlayerCardHolder::PlayerCardHolder(QWidget *parent, CardMaker *maker,const vector<const Card*>* Cards) : QWidget(parent), cardMaker(maker), HandCards(Cards)
{
    this->setFixedSize(PLAYER_HOLDER_WIDTH,CARD_HEIGHT);
    this->show();
    display_pos = 0;

    Layout = new QHBoxLayout;
    Layout->setSpacing(VISIBLE_CARDS_SPACING);
    Layout->setContentsMargins(0,0,0,0);
    CtrlLeft.setText("<");
    CtrlRight.setText(">");
    CtrlLeft.setFixedSize(CARD_WIDTH/4, CARD_HEIGHT);
    CtrlRight.setFixedSize(CARD_WIDTH/4, CARD_HEIGHT);

    Layout->addWidget(&CtrlLeft);
    for(int i = 0; i < VISIBLE_CARDS_IN_HAND;++i)
    {
        Layout->addWidget(VisibleCards+i);
        VisibleCards[i].setIndex(i);
        VisibleCards[i].hide();
        QObject::connect(VisibleCards+i,SIGNAL(Choosen(int)),this,SLOT(CardChoosen(int)));
    }
    Layout->addWidget(&CtrlRight);
    this->setLayout(Layout);
    QObject::connect(&CtrlLeft,SIGNAL(clicked()),this,SLOT(CheckLeft()));
    QObject::connect(&CtrlRight,SIGNAL(clicked()),this,SLOT(CheckRight()));
    HideCtrlButtons();
}

void PlayerCardHolder::AddCard()
{
    if(HandCards->size() > VISIBLE_CARDS_IN_HAND)
    {
        ShowCtrlButtons();
        CheckRight();
    }
    else
    {
        VisibleCards[HandCards->size()-1].updatePix(cardMaker->GetCard(*(*HandCards).back()));
        VisibleCards[HandCards->size()-1].show();
    }
}

void PlayerCardHolder::UpdateVisibleCards()
{
    for(int i = 0;i < VISIBLE_CARDS_IN_HAND;++i)
    {
        VisibleCards[i].updatePix(cardMaker->GetCard(*(*HandCards)[i+display_pos]));
        VisibleCards[i].update();
    }
}

void PlayerCardHolder::ShowCtrlButtons()
{
    CtrlLeft.show();
    CtrlRight.show();
}

void PlayerCardHolder::HideCtrlButtons()
{
    CtrlLeft.hide();
    CtrlRight.hide();
}

void PlayerCardHolder::CheckLeft()
{
    if(display_pos < 1) return;
    display_pos--;
    UpdateVisibleCards();
}

void PlayerCardHolder::CheckRight()
{
    if(display_pos +1 > HandCards->size()-VISIBLE_CARDS_IN_HAND) return;
    display_pos++;
    UpdateVisibleCards();
}

void PlayerCardHolder::UpdateExtractedCards()
{
    int size = HandCards->size();
    if(size <= VISIBLE_CARDS_IN_HAND)
    {
        for(int i = 0; i < size;++i)
        {
            VisibleCards[i].updatePix(cardMaker->GetCard(*(*HandCards)[i]));
            VisibleCards[i].update();
        }
        for(int i = size; i < VISIBLE_CARDS_IN_HAND;++i)
        {
            VisibleCards[i].hide();
        }
        display_pos = 0;
        HideCtrlButtons();
    }
    else
    {
        if(display_pos + 1>size-VISIBLE_CARDS_IN_HAND)
        {
            display_pos = size-VISIBLE_CARDS_IN_HAND;
        }
        UpdateVisibleCards();
    }
}
vector<int> PlayerCardHolder::GetIndexes()
{
    for(size_t i = 0; i < ChoosenCardsIndexes.size();++i)
    {
        PlayerCardDisplayer Card;
        Card.updatePix(cardMaker->GetCard(*(*HandCards)[ChoosenCardsIndexes[i]]));
        Card.unprintSelection();
    }
    return ChoosenCardsIndexes;
}

void PlayerCardHolder::ClearIndexes()
{
    ChoosenCardsIndexes.clear();
}
void PlayerCardHolder::ExtractCards()
{
    UpdateExtractedCards();
    ChoosenCardsIndexes.clear();
}

void PlayerCardHolder::UpdateDequeSuit(CardSuit *suit)
{
    DequeSuit = suit;
}

void PlayerCardHolder::CardChoosen(int index)
{
    int allCardIndex = index + display_pos;
    auto pos = std::find(ChoosenCardsIndexes.begin(), ChoosenCardsIndexes.end(),allCardIndex);
    if(pos == ChoosenCardsIndexes.end() )
    {
        if(ChoosenCardsIndexes.size() == 0 && (*HandCards)[allCardIndex]->Suit != *DequeSuit)
        {
            VisibleCards[index].printSelection();
            ChoosenCardsIndexes.push_back(allCardIndex);
            SelectedValue = (*HandCards)[allCardIndex]->Value;
        }
        else if(SelectedValue == (*HandCards)[allCardIndex]->Value)
        {
            if(ChoosenCardsIndexes.size() == 0 && (*HandCards)[allCardIndex]->Suit == *DequeSuit) return;
            VisibleCards[index].printSelection();
            ChoosenCardsIndexes.push_back(allCardIndex);
        }
    }
    else
    {
        VisibleCards[index].unprintSelection();
        ChoosenCardsIndexes.erase(pos);
        if(ChoosenCardsIndexes.size() == 1)
        {
            if((*HandCards)[ChoosenCardsIndexes[0]]->Suit == *DequeSuit)
            {
                PlayerCardDisplayer Card;
                Card.updatePix(cardMaker->GetCard(*(*HandCards)[ChoosenCardsIndexes[0]]));
                Card.unprintSelection();
                ChoosenCardsIndexes.pop_back();
                this->update();
                SelectedValue = CardValue(-1);
            }
        }
    }
}
