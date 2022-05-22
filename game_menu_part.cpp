#include "game.h"

void Game::ShowGameElements()
{
    PauseButton->show();
    Move->show();
    Player->Holder->show();
    for(int i = 0; i < players-1;++i)
        Enemies[i]->Holder->show();
    Deque->Displayer->show();
    OpenDeque->Displayer->show();
}

void Game::HideGameElements()
{
    PauseButton->hide();
    Move->hide();
    Player->Holder->hide();
    for(int i = 0; i < players-1;++i)
        Enemies[i]->Holder->hide();
    Deque->Displayer->hide();
    OpenDeque->Displayer->hide();
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

void Game::FreeResourses()
{
    delete PauseButton;
    delete Move;
    delete Player;
    for(int i = 0; i < players-1;++i)
        delete Enemies[i];
    delete Deque;
    delete OpenDeque;
    delete Maker;
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
}
void Game::InitMenuElements()
{
    Layout = dynamic_cast<QGridLayout*>(Wnd->layout());
    Text = new QLabel;
    Text->setAlignment(Qt::AlignmentFlag::AlignCenter | Qt::AlignmentFlag::AlignTop);
    ResumeButton = new QPushButton("Продовжити");
    ResumeButton->setFixedSize(200,100);
    QObject::connect(ResumeButton,SIGNAL(clicked()),this,SLOT(ResumeGame()));
    RestartButton = new QPushButton("Заново");
    QObject::connect(RestartButton,SIGNAL(clicked()),this,SLOT(RestartGame()));
    RestartButton->setFixedSize(200,100);
    MainMenuButton = new QPushButton("Головне меню");
    QObject::connect(MainMenuButton,SIGNAL(clicked()),this,SLOT(EnterMainMenu()));
    MainMenuButton->setFixedSize(200,100);
    Layout->addWidget(Text,0,0);
    Layout->addWidget(ResumeButton,1,0);
    Layout->addWidget(RestartButton,2,0);
    Layout->addWidget(MainMenuButton,3,0);

    HideMenuElements();
}

void Game::DeleteMenuElements()
{
    delete Text;
    delete ResumeButton;
    delete RestartButton;
    delete MainMenuButton;
}

void Game::PauseGame()
{
    HideGameElements();
    Text->setText("Павза");
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