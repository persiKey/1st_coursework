#include "cardmaker.h"
#include <QDebug>

QPixmap* CardMaker::CachedCover;

using namespace Constants;

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
    for(int i =0 ; i < NUM_OF_SUITS; ++i)
    {
        for(int k = 0; k < NUM_OF_VALUES; ++k)
        {
            assert(true);
            if(CachedCards[i][k] != nullptr){}
              delete CachedCards[i][k];
        }
    }
    for(int i = 0; i < NUM_OF_SUITS; ++i)
    {
        delete[] CachedCards[i];
    }
    delete [] CachedCards;
    if(CachedCover != nullptr) {delete CachedCover; CachedCover = nullptr;}
}
char CardMaker::GetPrintValue(CardValue value)
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
void CardMaker::SetSuit(QPixmap& PixSuit, CardSuit suit)
{
    switch (suit)
    {
    case CardSuit::HEARTS : PixSuit.load("src\\hearts.png"); break;
    case CardSuit::TILES : PixSuit.load("src\\tiles.png"); break;
    case CardSuit::CLOVERS : PixSuit.load("src\\clovers.png"); break;
    case CardSuit::PIKES : PixSuit.load("src\\pikes.png"); break;
    }

}
void CardMaker::DrawCardBorder(QPainter &painter)
{
    painter.drawLine(0,0,CARD_WIDTH-1,0);
    painter.drawLine(0,0,0,CARD_HEIGHT-1);
    painter.drawLine(CARD_WIDTH-1,0,CARD_WIDTH-1, CARD_HEIGHT-1);
    painter.drawLine(0,CARD_HEIGHT-1,CARD_WIDTH-1, CARD_HEIGHT-1);
}

void CardMaker::MakeAce(QPainter& painter, QPixmap& PixSuit)
{
    int offset = QFontMetrics(painter.font()).width('f')/2-1;
    // ACE TOP
    painter.drawText(CARD_WIDTH/2-offset,VALUE_FONT,QString('f'));
    // SUIT CENTER
    painter.drawPixmap(CARD_WIDTH/2-CENTER_SUIT_SIZE*1.4/2,
                       CARD_HEIGHT/2-CENTER_SUIT_SIZE*1.4/2,
                       CENTER_SUIT_SIZE*1.4, CENTER_SUIT_SIZE*1.4,PixSuit);

    painter.translate(CARD_WIDTH, CARD_HEIGHT);
    painter.rotate(180);

    // ACE REVRSE DOWN
    painter.drawText(CARD_WIDTH/2-offset,VALUE_FONT,QString('f'));
    painter.end();
}


QPixmap *CardMaker::CreateCard(CardSuit suit, CardValue value)
{
    QPixmap* Card = new QPixmap(CARD_WIDTH, CARD_HEIGHT);
    Card->fill(Qt::white);

    QPainter painter(Card);
    painter.setFont(this->Font);

    DrawCardBorder(painter);
    if(suit < CardSuit::CLOVERS)
        painter.setPen(Qt::red);
    else
        painter.setPen(Qt::black);

    QPixmap PixSuit; SetSuit(PixSuit, suit);
    if(value == CardValue::ACE)
    {
        MakeAce(painter,PixSuit);
        CachedCards[(int)suit][(int)value] = Card;
        return Card;
    }

    char printVal = GetPrintValue(value);
    // UP-LEFT VALUE
    painter.drawText(5,VALUE_FONT,QString(printVal));

    // UP-LEFT SUIT
    painter.drawPixmap(3,VALUE_FONT,SUIT_SIZE, SUIT_SIZE,PixSuit);

    // CENTER SUIT
    painter.drawPixmap(CARD_WIDTH/2-CENTER_SUIT_SIZE/2,
                       CARD_HEIGHT/2-CENTER_SUIT_SIZE/2,
                       CENTER_SUIT_SIZE, CENTER_SUIT_SIZE,PixSuit);

    painter.translate(CARD_WIDTH, CARD_HEIGHT);
    painter.rotate(180);
    // DOWN-RIGHT REVERSE SUIT
     painter.drawPixmap(3,VALUE_FONT,SUIT_SIZE, SUIT_SIZE,PixSuit);
    // DOWN-RIGHT REVERSE VALUE
    painter.drawText(5,VALUE_FONT,QString(printVal));
    // BORDER
    //DrawCardBorder(painter);
    painter.end();
    CachedCards[(int)suit][(int)value] = Card;
    return Card;
}

QPixmap* CardMaker::GetCard(CardSuit suit, CardValue value)
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

QPixmap *CardMaker::GetCard(const Card &card)
{
    return GetCard(card.Suit, card.Value);
}

QPixmap* CardMaker::GetCover()
{
    if(CachedCover == nullptr)
    {
        CachedCover = new QPixmap(CARD_WIDTH, CARD_HEIGHT);
        QPixmap tmp("src\\cover.png");
        QPainter painter(CachedCover);
        painter.drawPixmap(0,0,CARD_WIDTH,CARD_HEIGHT,tmp);
        DrawCardBorder(painter);
        painter.end();
    }

    return CachedCover;
}
