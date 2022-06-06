#include "game.h"
#include "QDebug"

#include "constants.h"
#include "login.h"
#include "func.h"

#include <QApplication>

using namespace Constants;


Game::Game(QObject *parent) : QObject(parent)
{
    Wnd = Desk = Move = PauseButton = HintButton = nullptr;
    Text = nullptr;
    ResumeButton = RestartButton = MainMenuButton = nullptr;
    Helper = nullptr;
    Maker = nullptr;
    Player = nullptr;
    Enemies = nullptr;
    Deque = nullptr;
    OpenDeque = nullptr;
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
    OpenDeque->PlaceCard(Deque->TakeCard());
    last  = OpenDeque->Cards.back()->Suit;
    moves_offset = Deque->Cards.size() % players;
}


void Game::Init(int pl, Difficulty dif, PlayerStat *Prof)
{
    this->players = pl;
    this->difficulty = dif;

    Profile = Prof;

    Desk = new QWidget(Wnd);
    Desk->setFixedSize(PLAYER_HOLDER_WIDTH+CARD_WIDTH/2,WINDOW_HEIGHT/2.5);
    Desk->move((WINDOW_WIDTH - PLAYER_HOLDER_WIDTH - CARD_WIDTH/2)/2, CARD_HEIGHT * 1.5 );
    Desk->setStyleSheet("background-color:green;"
                        "border: 10px solid #CD853F;"
                        "border-radius: 20%;");
    Desk->show();

    Move = new QPushButton("Зробити хід", Wnd);
    Move->move((WINDOW_WIDTH - Move->size().width())/2,WINDOW_HEIGHT - CARD_HEIGHT - COUNTER_SIZE - 10 - SMALL_BUT_SIZE);
    QObject::connect(Move,SIGNAL(clicked()),this,SLOT(OneGameTact()));

    PauseButton = new QPushButton("||", Wnd);
    PauseButton->move((WINDOW_WIDTH - PLAYER_HOLDER_WIDTH)/2,WINDOW_HEIGHT - CARD_HEIGHT - COUNTER_SIZE - 10 - SMALL_BUT_SIZE);
    PauseButton->setFixedSize(SMALL_BUT_SIZE,SMALL_BUT_SIZE);
    QObject::connect(PauseButton,SIGNAL(clicked()),this,SLOT(PauseGame()));

    if(difficulty != Difficulty::HARD)
    {
        Helper = new AI;
        HintButton = new QPushButton("?",Wnd);
        HintButton->setFixedSize(SMALL_BUT_SIZE,SMALL_BUT_SIZE);
        HintButton->move((WINDOW_WIDTH - PLAYER_HOLDER_WIDTH)/2 + PLAYER_HOLDER_WIDTH - SMALL_BUT_SIZE,WINDOW_HEIGHT - CARD_HEIGHT - COUNTER_SIZE - 10 - SMALL_BUT_SIZE);
        HintButton->show();
        QObject::connect(HintButton,SIGNAL(clicked()), this,SLOT(DisplayHint()));
    }

    qDebug() << players << " " << (int)difficulty << "\n";
    Maker = new CardMaker;
    Player = new MainPlayer(Wnd,Maker,difficulty == Difficulty::HARD);

    Enemies = new Enemy*[players-1];
    int counter = players-2;
    switch (players) {
    case 4:
        Enemies[counter] = new Enemy(Wnd,CardOrientation::HOR,WINDOW_WIDTH-CARD_HEIGHT,5);
        --counter;
    case 3:
        Enemies[counter] = new Enemy(Wnd,CardOrientation::VER,(WINDOW_WIDTH - ENEMY_HOLDER_SIZE_VALUE)/2,0);
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
    Player->SetFocus(true);
    Player->SetDequeSuit(&last);
    for(int i =0; i < players-1;++i)
    {
        Enemies[i]->SetDequeSuit(&last);
        Enemies[i]->SetDifficulty(difficulty);
    }

    ShowGameElements();
    InitMenuElements();
}

bool Game::CheckMovesAvailable(Person * pl)
{
    for(auto card : pl->Hand)
    {
        if(card->Suit != last)
            return true;
    }
    return false;
}

void Game::TakeAllOpenCards(Person  *pl)
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
    class Person ** E = new class Person *[players];
    E[0] = Player;
    for(int i = 0; i < players-1;++i)
    {
        E[i+1] = Enemies[i];
    }

    for(int i = Deque->Cards.size() - 1, p_i = active_player; i >= 0;--i)
    {
        E[p_i]->NextCards.push_back(Deque->Cards[i]);
        p_i = (p_i + 1) % players;
    }
    delete[] E;
}
void Game::UpdateNextCards(Person  *pl)
{
    if(pl->NextCards.size() > 0)
        pl->NextCards.pop_front();
}

void Game::UpdatePosibleNextCards(Person  *pl)
{
    pl->PossibleNextCards.clear();
    int val = active_player-moves_offset;
    for(int i = val >= 0 ? val : val + players; i < OpenDeque->Cards.size(); i+= players)
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
bool Game::CheckIfWin( Person  *pl)
{
    if(pl->Hand.empty())
        return true;
    return false;
}

void Game::RenewDeque()
{
    if(OpenDeque->Cards.size() == 0) return;
    const Card* last_open = OpenDeque->Cards.back();
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

    moves_offset = (moves_offset + Deque->Cards.size() % players) % players;
    UpdateNextCards();
}
void Game::GiveOneCardFromDequeToPlayer(Person * pl)
{
    if(Deque->Cards.empty()) RenewDeque();
    pl->AddCard(Deque->TakeCard());
}
int Game::OnePlayerTact( Person  *pl)
{
    UpdatePosibleNextCards(pl);
    if(!CheckMovesAvailable(pl))
    {
        active_player = (active_player + 1) % players;
        TakeAllOpenCards(pl);
        return -2;
    }
    vector<const Card*> moveCards = pl->PlaceCards();
    if(moveCards.empty()) return -1;
    OpenDeque->PlaceCards(moveCards);
    last = moveCards.back()->Suit;
    if(CheckIfWin(pl)) return 1;
    active_player = (active_player + 1) % players;

    ProcessAndPause(1000);
    return false;
}

void Game::ClearHintCards()
{
    for(int i = 0 ; i < lastHintIndexes.size();++i)
    {
        PlayerCardDisplayer card;
        card.updatePix(Maker->GetCard(*Player->Hand[lastHintIndexes[i]]));
        card.unprintSelection();
    }
    lastHintIndexes.clear();
}

void Game::OneGameTact()
{
    SetEnabledControlElements(false);
    Player->SetFocus(false);
    ClearHintCards();
    switch (OnePlayerTact(Player)) {
    case 1: FillPlayerStat(true); DisplayWinLoose("Ви виграли!");return;
    case -1: SetEnabledControlElements(true);Player->SetFocus(true);return;
    }

    Player->UpdateHint();
    for(int i = 0; i < players-1;++i)
    {
        Enemies[i]->SetFocus(true);
        GiveOneCardFromDequeToPlayer(Enemies[i]);
        UpdateNextCards(Enemies[i]);
        if(OnePlayerTact(Enemies[i]) == 1)
        {
            FillPlayerStat(false);
            ProcessAndPause(Constants::TACT_DELAY);
            DisplayWinLoose("Ви програли!");
            return;
        }
        Enemies[i]->SetFocus(false);
    }
    GiveOneCardFromDequeToPlayer(Player);
    UpdateNextCards(Player);
    UpdatePosibleNextCards(Player);
    Player->UpdateHint();
    Player->SetFocus(true);
    SetEnabledControlElements(true);
}

void Game::DisplayHint()
{
    if(!CheckMovesAvailable(Player)) return;
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

Game::~Game()
{
    FreeResourses();
}
