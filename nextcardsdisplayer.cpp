#include "nextcardsdisplayer.h"
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
NextCardsDisplayer::NextCardsDisplayer(const deque<const Card*>* DisplCards,const deque<const Card*>* PossibleCards, QWidget *parent) : QWidget(parent)
{
    Layout.setAlignment(Qt::AlignRight);
    Layout.setMargin(0);
    this->setLayout(&Layout);
    this->setWindowTitle("Наступні карти");
    this->setWindowFlags(Qt::Window | Qt::Tool);
    for(int i = 0; i < MAX_NEXT_CARDS; ++i)
    {
        Layout.insertWidget(0,&Cards[i],0,Qt::AlignRight);
        Cards[i].hide();
    }
    NextCards = DisplCards;
    PossibleNextCards = PossibleCards;
    UpdateNextCards();
}

void NextCardsDisplayer::UpdateNextCards()
{
    this->update();
    if(NextCards->size() == 0 && PossibleNextCards->size() == 0)
    {
        this->hide();
        return;
    }
    else
        this->show();
    for(size_t i = 0; i < MAX_NEXT_CARDS && i < NextCards->size();++i)
    {
        Cards[i].updatePix(Maker.GetCard(*(*NextCards)[i]));
        Cards[i].printSelection(Qt::yellow);
        Cards[i].show();
    }
    for(size_t i = NextCards->size(), c_i = 0; i < MAX_NEXT_CARDS && i < NextCards->size()+PossibleNextCards->size() ;++i,++c_i)
    {
        Cards[i].updatePix(Maker.GetCard(*(*PossibleNextCards)[c_i]));
        Cards[i].printSelection(Qt::cyan);
        Cards[i].show();
    }
    for(size_t i = NextCards->size()+PossibleNextCards->size(); i < MAX_NEXT_CARDS;++i)
        Cards[i].hide();
    this->adjustSize();
    this->move((QGuiApplication::primaryScreen()->geometry().width()-this->size().width())/2,0);
    this->update();
}
