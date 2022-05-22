#include "game.h"
#include "QDebug"

#include "constants.h"

#include <thread>
#include <QApplication>

void ProcessAndPause(int msec)
{
    QApplication::processEvents();
    std::this_thread::sleep_for(std::chrono::milliseconds(msec));
}

Game::Game(QObject *parent) : QObject(parent)
{
    GenerateCards();
}

void Game::setWnd(QWidget *wnd)
{
    this->Wnd = wnd;
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


void Game::Init(int pl, int dif)
{
    Move = new QPushButton("Зробити хід", Wnd);
    Move->move(800,400);
    QObject::connect(Move,SIGNAL(clicked()),this,SLOT(OneGameTact()));

    PauseButton = new QPushButton("||", Wnd);
    PauseButton->move(900,400); PauseButton->setFixedSize(30,30);
    QObject::connect(PauseButton,SIGNAL(clicked()),this,SLOT(PauseGame()));

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

    GiveCardsToPlayers();
    last  = CardSuit(-1);
    Player->SetDequeSuit(&last);
    for(int i =0; i < players-1;++i)
    {
        Enemies[i]->SetDequeSuit(&last);
        Enemies[i]->dif = difficulty;
    }

    ShowGameElements();
    InitMenuElements();
}

bool Game::CheckMovesAvailable(class Player* pl)
{
    for(auto card : pl->Hand)
    {
        if(card->Suit != last)
            return true;
    }
    return false;
}

void Game::TakeAllOpenCards(class Player *pl)
{

    while(!OpenDeque->Cards.empty())
    {
        pl->AddCard(OpenDeque->Cards.back());
        ProcessAndPause(80);
        OpenDeque->Cards.pop_back();
    }
    OpenDeque->Clear();

}

bool Game::CheckIfWin(class Player *pl)
{
    if(pl->Hand.empty())
        return true;
    return false;
}

void Game::RenewDeque()
{
    Card* last_open = OpenDeque->Cards.back();
    OpenDeque->Cards.pop_back();

    for(size_t i = 0; i < OpenDeque->Cards.size();++i)
    {
        Deque->Cards.push_back(OpenDeque->Cards.back());
        OpenDeque->Cards.pop_back();
        Deque->Displayer->AddCard();
        --i;
    }
    OpenDeque->Clear();
    OpenDeque->PlaceCard(last_open);
}

int Game::OnePlayerTact(class Player *pl)
{
    if(!CheckMovesAvailable(pl))
    {
        TakeAllOpenCards(pl);
        return -2;
    }
    vector<Card*> moveCards = pl->PlaceCards();
    if(moveCards.empty()) return -1;
    OpenDeque->PlaceCards(moveCards);
    last = moveCards.back()->Suit;
    if(CheckIfWin(pl)) return 1;

    if(Deque->Cards.empty()) RenewDeque();
    pl->AddCard(Deque->TakeCard());
    ProcessAndPause(1000);
    return false;
}

void Game::OneGameTact()
{

    switch (OnePlayerTact(Player)) {
    case 1: DisplayWinLoose("Ви виграли!");return;
    case -1: return;
    }
    for(int i = 0; i < players-1;++i)
    {
        if(OnePlayerTact(Enemies[i]) == 1)
        {
            ProcessAndPause(2000);
            DisplayWinLoose("Ви програли!");
        }
    }
}
