#include "game.h"

void Game::ShowGameElements()
{
    Desk->show();
    PauseButton->show();
    if(difficulty != Difficulty::HARD) HintButton->show();
    Move->show();
    Player->Show();
    for(int i = 0; i < players-1;++i)
        Enemies[i]->Show();
    Deque->Show();
    OpenDeque->Show();
}

void Game::HideGameElements()
{
    Desk->hide();
    PauseButton->hide();
    if(difficulty != Difficulty::HARD) HintButton->hide();
    Move->hide();
    Player->Hide();
    for(int i = 0; i < players-1;++i)
        Enemies[i]->Hide();
    Deque->Hide();
    OpenDeque->Hide();
}

void Game::HideMenuElements()
{
    Text->hide();
    ResumeButton->hide();
    RestartButton->hide();
    MainMenuButton->hide();
}

void Game::ShowMenuElements()
{
    Text->show();
    ResumeButton->show();
    RestartButton->show();
    MainMenuButton->show();
}

void Game::SetEnabledControlElements(bool f)
{
    PauseButton->setEnabled(f);
    Move->setEnabled(f);
    if(HintButton != nullptr) HintButton->setEnabled(f);
}

void Game::FreeResourses()
{
    if( Desk != nullptr) {delete  Desk; Desk = nullptr;}
    if( PauseButton != nullptr) {delete  PauseButton; PauseButton = nullptr;}
    if( HintButton != nullptr) {delete  HintButton; HintButton = nullptr;}
    if (Helper != nullptr) {delete Helper; Helper = nullptr;}
    if (Move != nullptr){ delete Move; Move = nullptr;}
    if( Player != nullptr ) {delete Player; Player = nullptr;}
    if(Enemies != nullptr)
    {
        for(int i = 0; i < players-1;++i)
            delete Enemies[i];
        delete[] Enemies; Enemies = nullptr;
    }
    if (Deque != nullptr){ delete Deque; Deque = nullptr;}
    if(OpenDeque != nullptr) {delete OpenDeque; OpenDeque = nullptr;}
    if(Maker != nullptr){ delete Maker; Maker = nullptr;}
    DeleteMenuElements();
}

void Game::Restart()
{
    Player->Clear();
    for(int i = 0; i < players-1;++i)
        Enemies[i]->Clear();
    OpenDeque->Clear();
    Deque->Clear();
    Deque->RandomCardGen(Cards);
    GiveCardsToPlayers();
    game_started = clock();
    active_player = 0;
    GiveOneCardFromDequeToPlayer(Player);
    ClearHintCards();
    SetEnabledControlElements(true);
}

void Game::InitMenuElements()
{
    Layout = dynamic_cast<QGridLayout*>(Wnd->layout());
    Text = new QLabel;
    Text->setAlignment(Qt::AlignmentFlag::AlignCenter | Qt::AlignmentFlag::AlignTop);
    Text->setStyleSheet("font: 50px;");
    ResumeButton = new QPushButton("Продовжити");
    ResumeButton->setFixedSize(200,100);
    QObject::connect(ResumeButton,SIGNAL(clicked()),this,SLOT(ResumeGame()));
    RestartButton = new QPushButton("Заново");
    QObject::connect(RestartButton,SIGNAL(clicked()),this,SLOT(RestartGame()));
    RestartButton->setFixedSize(200,100);
    MainMenuButton = new QPushButton("Головне меню");
    QObject::connect(MainMenuButton,SIGNAL(clicked()),this,SLOT(EnterMainMenu()));
    MainMenuButton->setFixedSize(200,100);
    Layout->addWidget(Text,0,0,1,3);
    Layout->addWidget(ResumeButton,1,1);
    Layout->addWidget(RestartButton,2,1);
    Layout->addWidget(MainMenuButton,3,1);

    HideMenuElements();
}

void Game::DeleteMenuElements()
{
    if(Text != nullptr){ delete Text; Text = nullptr;}
    if(ResumeButton != nullptr){ delete ResumeButton; ResumeButton = nullptr;}
    if(RestartButton != nullptr){ delete RestartButton; RestartButton = nullptr;}
    if(MainMenuButton != nullptr){ delete MainMenuButton; MainMenuButton = nullptr;}
}

void Game::PauseGame()
{
    HideGameElements();
    Text->setText("Пауза");
    ShowMenuElements();
}

void Game::ResumeGame()
{
    ShowGameElements();
    HideMenuElements();
}

void Game::RestartGame()
{
    HideMenuElements();
    Restart();
    ShowGameElements();
}
void Game::EnterMainMenu()
{
    HideGameElements();
    HideMenuElements();
    FreeResourses();
    emit MainMenu();
}

void Game::DisplayWinLoose(QString msg)
{
    Text->setText(msg);
    HideGameElements();
    ShowMenuElements();
    ResumeButton->hide();
}
