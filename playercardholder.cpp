#include "playercardholder.h"
#include <QVBoxLayout>

#include <QDebug>
PlayerCardHolder::PlayerCardHolder(QWidget *parent, CardMaker *maker) : QWidget(parent), cardMaker(maker)
{
    this->move(100,100);
    this->setFixedSize(900,500);
    this->show();
    display_pos = 0;

    Layout = new QHBoxLayout;
    Layout->setSpacing(10);

    CtrlLeft.setText("<");
    CtrlRight.setText(">");
    CtrlLeft.setFixedSize(CARD_WIDTH/4, CARD_HEIGHT);
    CtrlRight.setFixedSize(CARD_WIDTH/4, CARD_HEIGHT);

    Layout->addWidget(&CtrlLeft);
    for(int i = 0; i < VISIBLE_CARDS_IN_HAND;++i)
    {
        //VisibleCards[i].setParent(this);
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

void PlayerCardHolder::AddCard(Card *card)
{
    AllCards.push_back(card);
    if(AllCards.size() > VISIBLE_CARDS_IN_HAND)
    {
        ShowCtrlButtons();
        CheckRight();
    }
    else
    {
        VisibleCards[AllCards.size()-1].updatePix(cardMaker->GetCard(*card));
        VisibleCards[AllCards.size()-1].show();
    }
}
void PlayerCardHolder::UpdateVisibleCards()
{
    for(int i = 0;i < VISIBLE_CARDS_IN_HAND;++i)
    {
        VisibleCards[i].updatePix(cardMaker->GetCard(*AllCards[i+display_pos]));
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
    if(display_pos +1 > AllCards.size()-VISIBLE_CARDS_IN_HAND) return;
    display_pos++;
    UpdateVisibleCards();
}

void PlayerCardHolder::ExtractCards()
{
    for(size_t i = 0; i < ChoosenCardsIndexes.size();++i)
    {
        AllCards[ChoosenCardsIndexes[i]] = nullptr;
    }
    for(size_t i = 0; i < AllCards.size();++i)
    {
        if(AllCards[i] == nullptr)
        {
            AllCards.erase(AllCards.begin()+i);
            --i;
        }
    }
    int size = AllCards.size();
    if(size <= VISIBLE_CARDS_IN_HAND)
    {
        for(int i = 0; i < size;++i)
        {
            VisibleCards[i].updatePix(cardMaker->GetCard(*AllCards[i]));
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
        qDebug() << "display pos " <<  display_pos;
        qDebug() << "Coosen size: " << ChoosenCardsIndexes.size()
                 << "All size: " << size;
        //display_pos -= ChoosenCardsIndexes.size();
        qDebug() << "af display pos " <<  display_pos;
//        if(display_pos - size < 0)
//        {
//            display_pos =0;
//        }
        if(display_pos + 1>size-VISIBLE_CARDS_IN_HAND)
        {
            display_pos = size-VISIBLE_CARDS_IN_HAND;
        }
        assert(display_pos >= 0);
        UpdateVisibleCards();
    }
    ChoosenCardsIndexes.clear();
}
void PlayerCardHolder::CardChoosen(int index)
{
    qDebug() << "Come ind: " << index << "Indexes: ";
    for(auto ind : ChoosenCardsIndexes)
    {
        qDebug() << ind << ' ';
    }
    qDebug() << "Display pos: " << display_pos;
    auto pos = std::find(ChoosenCardsIndexes.begin(), ChoosenCardsIndexes.end(),index+display_pos);
    if(pos == ChoosenCardsIndexes.end())
    {

        VisibleCards[index].printSelection();
        ChoosenCardsIndexes.push_back(index+display_pos);
    }
    else
    {
        VisibleCards[index].unprintSelection();
        ChoosenCardsIndexes.erase(pos);
    }
    qDebug() << "Indexes: ";
    for(auto index : ChoosenCardsIndexes)
    {
        qDebug() << index << ' ';
    }
    qDebug() << "Display pos: " << display_pos;
}
