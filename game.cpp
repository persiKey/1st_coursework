#include "game.h"
// 11:17
#include "QDebug"

#include "constants.h"

#include <thread>
Game::Game(QObject *parent) : QObject(parent)
{

}

void Game::setWnd(QWidget *wnd)
{
    this->Wnd = wnd;
    qDebug() << this->Wnd;
}
#include <QApplication>
void Game::OneGameTact()
{
    vector<Card*> moveCards = Player->PlaceCards();
    if(moveCards.empty()) return;
    OpenDeque->PlaceCards(moveCards);
    QApplication::processEvents();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    last = moveCards.back()->Suit;
    Player->AddCard(Deque->TakeCard());
    for(int i = 0; i < players-1;++i)
    {
        qDebug() << players << " h " << i;
        moveCards = Enemies[i]->PlaceCards();
        OpenDeque->PlaceCards(moveCards);
        last = moveCards.back()->Suit;
        Enemies[i]->AddCard(Deque->TakeCard());
        QApplication::processEvents();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    Player->SetDequeSuit(last);
}

void Game::GenerateCards()
{
    for(int i = 0; i < NUM_OF_SUITS;++i )
    {
        for(int k = 0; k < NUM_OF_VALUES;++k)
        {
            Cards[i*NUM_OF_VALUES+k].Suit = CardSuit(i);
            Cards[i*NUM_OF_VALUES+k].Value = CardValue(k);
        }
    }
}


void Game::GiveCardsToPlayers()
{
    for(int i =0; i < 5;++i)
    {
        Player->AddCard(Deque->TakeCard());
        for(int k =0; k < players-1;++k)
        {
            Enemies[k]->AddCard(Deque->TakeCard());
        }
    }

}
void Game::MainLoop()
{

    while(true)
    {

        qDebug() << "yes";
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
}

void Game::Init(int pl, int dif)
{
    Move = new QPushButton("Зробити хід", Wnd);
    Move->move(800,400);
    Move->show();
    QObject::connect(Move,SIGNAL(clicked()),this,SLOT(OneGameTact()));
    this->players = pl;
    this->difficulty = dif;
    qDebug() << players << " " << difficulty << "\n";
    Maker = new CardMaker;
    Player = new MainPlayer(Wnd,Maker);

    Enemies = new Enemy*[players-1];
    int counter = players-2;
    switch (players) {
    case 4:
        Enemies[counter] = new Enemy(Wnd,CardOrientation::HOR,1280-170,5);
        --counter;
    case 3:
        Enemies[counter] = new Enemy(Wnd,CardOrientation::VER,285,0);
        --counter;
    case 2:
        Enemies[counter] = new Enemy(Wnd,CardOrientation::HOR,0,5);
    }
    Deque = new CardDeque(Wnd,Cards);
    OpenDeque = new OpenCardDeque(Wnd,Maker);
    GenerateCards();
    std::thread a(&Game::MainLoop,std::ref(*this));
    a.detach();
    GiveCardsToPlayers();

}
