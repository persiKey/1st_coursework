#include "playercardholder.h"
#include <QVBoxLayout>

#include <QDebug>
PlayerCardHolder::PlayerCardHolder(QWidget *parent, CardMaker *maker, vector<Card*>* Cards) : QWidget(parent), cardMaker(maker), AllCards(Cards)
{
    this->setFixedSize(900,CARD_HEIGHT);
    this->show();
    display_pos = 0;

    Layout = new QHBoxLayout;
    Layout->setSpacing(10);
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
    if(AllCards->size() > VISIBLE_CARDS_IN_HAND)
    {
        ShowCtrlButtons();
        CheckRight();
    }
    else
    {
        VisibleCards[AllCards->size()-1].updatePix(cardMaker->GetCard(*(*AllCards).back()));
        VisibleCards[AllCards->size()-1].show();
    }
}

void PlayerCardHolder::UpdateVisibleCards()
{
    for(int i = 0;i < VISIBLE_CARDS_IN_HAND;++i)
    {
        VisibleCards[i].updatePix(cardMaker->GetCard(*(*AllCards)[i+display_pos]));
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
    if(display_pos +1 > AllCards->size()-VISIBLE_CARDS_IN_HAND) return;
    display_pos++;
    UpdateVisibleCards();
}

void PlayerCardHolder::UpdateExtractedCards()
{
    int size = AllCards->size();
    if(size <= VISIBLE_CARDS_IN_HAND)
    {
        for(int i = 0; i < size;++i)
        {
            VisibleCards[i].updatePix(cardMaker->GetCard(*(*AllCards)[i]));
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
        Card.updatePix(cardMaker->GetCard(*(*AllCards)[ChoosenCardsIndexes[i]]));
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
        if(ChoosenCardsIndexes.size() == 0 && (*AllCards)[allCardIndex]->Suit != *DequeSuit)
        {
            VisibleCards[index].printSelection();
            ChoosenCardsIndexes.push_back(allCardIndex);
            SelectedValue = (*AllCards)[allCardIndex]->Value;
        }
        else if(SelectedValue == (*AllCards)[allCardIndex]->Value)
        {
            if(ChoosenCardsIndexes.size() == 0 && (*AllCards)[allCardIndex]->Suit == *DequeSuit) return;
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
            if((*AllCards)[ChoosenCardsIndexes[0]]->Suit == *DequeSuit)
            {
                PlayerCardDisplayer Card;
                Card.updatePix(cardMaker->GetCard(*(*AllCards)[ChoosenCardsIndexes[0]]));
                Card.unprintSelection();
                ChoosenCardsIndexes.pop_back();
                this->update();
                SelectedValue = CardValue(-1);
            }
        }
    }

}
