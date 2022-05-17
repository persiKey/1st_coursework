#include "cardmaker.h"
#include <QDebug>


CardMaker::CardMaker() : Font("Hoyle Playing Cards", VALUE_FONT, QFont::Normal)
{
    CachedCards = new QPixmap**[NUM_OF_SUITS];
    for(int i = 0; i < NUM_OF_SUITS; ++i)
    {
        CachedCards[i] = new QPixmap*[NUM_OF_VALUES];
    }

    for(int i =0 ; i < NUM_OF_SUITS; ++i)
    {
        for(int k = 0; k < NUM_OF_VALUES; ++k)
        {
            CachedCards[i][k] = nullptr;
        }
    }

}

CardMaker::~CardMaker()
{
    for(int i = 0; i < NUM_OF_SUITS; ++i)
    {
        delete[] CachedCards[i];
    }
    delete [] CachedCards;

    for(int i =0 ; i < NUM_OF_SUITS; ++i)
    {
        for(int k = 0; k < NUM_OF_VALUES; ++k)
        {
            if(CachedCards[i][k] != nullptr)
                delete CachedCards[i][k];
        }
    }
}
char GetPrintValue(CardValue value)
{
    if(value < CardValue::_10)
    {
        return (int)value + '0' + 6;
    }
    switch (value)
    {
    case CardValue::_10 : return '0' ; break;
    case CardValue::JACK : return 'a'; break;
    case CardValue::QUEEN : return 's'; break;
    case CardValue::KING : return 'd'; break;
    case CardValue::ACE : return 'f'; break;
    default: return '%';
    }
}
void SetSuit(QPixmap& PixSuit, CardSuit suit)
{
    switch (suit)
    {
    case CardSuit::HEARTS : PixSuit.load("src\\hearts.png"); break;
    case CardSuit::TILES : PixSuit.load("src\\tiles.png"); break;
    case CardSuit::CLOVERS : PixSuit.load("src\\clovers.png"); break;
    case CardSuit::PIKES : PixSuit.load("src\\pikes.png"); break;
    }

}
QPixmap *CardMaker::CreateCard(CardSuit suit, CardValue value)
{
    qDebug() << "Card was created" ;
    //CachedCards[(int)suit][(int)value] = new QPixmap(CARD_WIDTH, CARD_HEIGHT);
    QPixmap* Card = new QPixmap(CARD_WIDTH, CARD_HEIGHT);
    Card->fill(Qt::white);

    char printVal = GetPrintValue(value);
    qDebug() << printVal;
    QPainter painter(Card);
    painter.setFont(this->Font);
    if(suit < CardSuit::CLOVERS)
        painter.setPen(Qt::red);
    else
        painter.setPen(Qt::black);
    // UP-LEFT VALUE
    painter.drawText(5,VALUE_FONT,QString(printVal));

    // UP-LEFT SUIT
    QPixmap PixSuit; SetSuit(PixSuit, suit);
    painter.drawPixmap(3,VALUE_FONT,SUIT_SIZE, SUIT_SIZE,PixSuit);

    // CENTER SUIT

    // DOWN-RIGHT REVERSE SUIT
    // DOWN-RIGHT REVERSE VALUE
    painter.end();
    CachedCards[(int)suit][(int)value] = Card;
    return Card;
}

const QPixmap* CardMaker::GetCard(CardSuit suit, CardValue value)
{
    if(CachedCards[(int)suit][(int)value] != nullptr)
    {
        return CachedCards[(int)suit][(int)value];
    }
    else
    {
        return CreateCard(suit, value);
    }
}
