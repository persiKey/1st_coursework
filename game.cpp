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


void Game::Init(int pl, int dif, PlayerStat *Prof)
{
    this->players = pl;
    this->difficulty = dif;

    Profile = Prof;
    Move = new QPushButton("Зробити хід", Wnd);
    Move->move(800,400);
    QObject::connect(Move,SIGNAL(clicked()),this,SLOT(OneGameTact()));

    PauseButton = new QPushButton("||", Wnd);
    PauseButton->move(900,400); PauseButton->setFixedSize(30,30);
    QObject::connect(PauseButton,SIGNAL(clicked()),this,SLOT(PauseGame()));

    if(difficulty < 3)
    {
        Helper = new AI;
        HintButton = new QPushButton("?",Wnd);
        HintButton->setFixedSize(30,30);
        HintButton->move(950,400);
        HintButton->show();
        QObject::connect(HintButton,SIGNAL(clicked()), this,SLOT(DisplayHint()));
    }

    qDebug() << players << " " << difficulty << "\n";
    Maker = new CardMaker;
    Player = new MainPlayer(Wnd,Maker,difficulty == 3);

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
    game_started = clock();
    GiveCardsToPlayers();
    GiveOneCardFromDequeToPlayer(Player);
    active_player = 0;
    last  = CardSuit(-1);
    Player->SetDequeSuit(&last);
    for(int i =0; i < players-1;++i)
    {
        Enemies[i]->SetDequeSuit(&last);
        Enemies[i]->SetDifficulty(difficulty);
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
    last = CardSuit(-1);
    OpenDeque->Clear();

}

void Game::UpdateNextCards()
{
    class Player** E = new class Player*[players];
    for(int i = 0; i < players; ++i)
    {
        if((active_player + i) % players == 0 )
            E[i] = Player;
        else
            E[i] = Enemies[(active_player + i) % players - 1];

        E[i]->NextCards.clear();
    }

    for(int i = Deque->Cards.size() - 1, p_i = 0; i >= 0;--i)
    {
        E[p_i]->NextCards.push_back(Deque->Cards[i]);
        p_i = (p_i +1) % players;
    }
}
void Game::UpdateNextCards(class Player *pl)
{
    if(pl->NextCards.size() > 0)
        pl->NextCards.pop_front();
}

void Game::UpdatePosibleNextCards(class Player *pl)
{
    pl->PossibleNextCards.clear();
    for(int i = Deque->Cards.size() % (active_player+1); i < OpenDeque->Cards.size(); i+= players)
    {
        pl->PossibleNextCards.push_back(OpenDeque->Cards[i]);
    }
}
void Game::FillPlayerStat(bool win)
{
    Profile->last_game_duration = (clock() - game_started)/CLOCKS_PER_SEC;
    int games_won = Profile->win_rate * Profile->games_played;
    Profile->games_played++;
    Profile->last_game_win = win;
    Profile->win_rate = float(games_won + win)/Profile->games_played;
    saveStat(Profile);
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

    UpdateNextCards();
}
void Game::GiveOneCardFromDequeToPlayer(class Player* pl)
{
    if(Deque->Cards.empty()) RenewDeque();
    pl->AddCard(Deque->TakeCard());
}
int Game::OnePlayerTact(class Player *pl)
{
    UpdatePosibleNextCards(pl);
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
    active_player = (active_player + 1) % players;

    ProcessAndPause(1000);
    return false;
}

void Game::OneGameTact()
{
    for(int i = 0 ; i < lastHintIndexes.size();++i)
    {
        PlayerCardDisplayer card;
        card.updatePix(Maker->GetCard(*Player->Hand[lastHintIndexes[i]]));
        card.unprintSelection();
    }
    lastHintIndexes.clear();
    qDebug() << "Player's move Activ: " << active_player;
    switch (OnePlayerTact(Player)) {
    case 1: FillPlayerStat(true); DisplayWinLoose("Ви виграли!");return;
    case -1: return;
    }

    Player->UpdateHint();
    for(int i = 0; i < players-1;++i)
    {
        GiveOneCardFromDequeToPlayer(Enemies[i]);
        UpdateNextCards(Enemies[i]);
            qDebug() << "Enemy's "<< i <<" move Activ: " << active_player;
        if(OnePlayerTact(Enemies[i]) == 1)
        {
            FillPlayerStat(false);
            ProcessAndPause(1000);
            DisplayWinLoose("Ви програли!");
            return;
        }
    }
    GiveOneCardFromDequeToPlayer(Player);
    UpdateNextCards(Player);
    UpdatePosibleNextCards(Player);
    Player->UpdateHint();

}

void Game::DisplayHint()
{
    Player->ResetChoosenCards();
    lastHintIndexes = Helper->Decide(&Player->Hand,&Player->NextCards,&Player->PossibleNextCards,last);
    PlayerCardDisplayer card;
    for(int i = 0 ; i < lastHintIndexes.size();++i)
    {
        card.updatePix(Maker->GetCard(*Player->Hand[lastHintIndexes[i]]));
        card.printSelection(Qt::red);
    }
    Player->UpdateHolder();
}
