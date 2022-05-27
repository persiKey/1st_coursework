#include "nextcardsdisplayer.h"

NextCardsDisplayer::NextCardsDisplayer(deque<Card*>* DisplCards, CardMaker* maker, QWidget *parent) : QWidget(parent) , Maker(maker)
{
    Layout.setAlignment(Qt::AlignRight);
    this->setLayout(&Layout);
    for(int i = 0; i < 13; ++i)
    {
        Layout.insertWidget(0,&Cards[i],0,Qt::AlignRight);
    }
    NextCards = DisplCards;
    UpdateNextCards();
}

void NextCardsDisplayer::UpdateNextCards()
{
    for(size_t i = 0; i < 13 && i < NextCards->size();++i)
    {
        Cards[i].updatePix(Maker->GetCard(*(*NextCards)[i]));
        Cards[i].show();
    }
    for(size_t i = NextCards->size(); i < 13;++i)
        Cards[i].hide();
    this->update();
}
