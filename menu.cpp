#include "menu.h"

Menu::Menu(QWidget* parent) : QObject(parent)
{
    Title.setAlignment(Qt::AlignmentFlag::AlignCenter | Qt::AlignmentFlag::AlignTop);
    Layout.setAlignment(Qt::AlignmentFlag::AlignCenter);
    Layout.setSpacing(40);
}

void Menu::setWnd(QWidget *wnd)
{
    this->Wnd = wnd;
    Login = new LoginWidget(wnd);
    QObject::connect(Login,SIGNAL(ProfileEntered(PlayerStat)),this,SLOT(Start(PlayerStat)));
    Wnd->show();

}

void Menu::MainMenu()
{

    Title.setText("Головне меню");
    FuncButton1.setText("Start");
    FuncButton1.setFixedSize(200,100);
    FuncButton2.setText("Exit");
    FuncButton2.setFixedSize(200,100);

    Layout.addWidget(&Title,0,0); Title.show();
    Layout.addWidget(&FuncButton1,1,0); FuncButton1.show();
    Layout.addWidget(&FuncButton2,2,0); FuncButton2.show();

    QObject::connect(&FuncButton1,SIGNAL(clicked()),this,SLOT(PlayersMenu()));
    QObject::connect(&FuncButton2, SIGNAL(clicked()),this, SLOT(Exit()));
}

void Menu::Exit()
{
    QApplication::quit();
}

void Menu::PlayersMenu()
{
    QObject::disconnect(&FuncButton1,SIGNAL(clicked()),this,SLOT(PlayersMenu()));
    QObject::disconnect(&FuncButton2, SIGNAL(clicked()),this, SLOT(Exit()));

    Title.setText("Виберіть кількість гравців");
    FuncButton1.setText("2");
    FuncButton2.setText("3");
    FuncButton3.setText("4");
    FuncButton3.setFixedSize(200,100);

    Layout.addWidget(&Title,0,0,1,3);
    Layout.addWidget(&FuncButton1,1,0);
    Layout.addWidget(&FuncButton2,1,1);
    Layout.addWidget(&FuncButton3,1,2); FuncButton3.show();

    QObject::connect(&FuncButton1,SIGNAL(clicked()),this,SLOT(SetPlayers()));
    QObject::connect(&FuncButton2,SIGNAL(clicked()),this,SLOT(SetPlayers()));
    QObject::connect(&FuncButton3,SIGNAL(clicked()),this,SLOT(SetPlayers()));
}

void Menu::SetPlayers()
{
    QPushButton *s = dynamic_cast<QPushButton*>(QObject::sender());
    players = s->text().toInt();

    QObject::disconnect(&FuncButton1,SIGNAL(clicked()),this,SLOT(SetPlayers()));
    QObject::disconnect(&FuncButton2,SIGNAL(clicked()),this,SLOT(SetPlayers()));
    QObject::disconnect(&FuncButton3,SIGNAL(clicked()),this,SLOT(SetPlayers()));
    DifficultyMenu();
}

void Menu::DifficultyMenu()
{
    Title.setText("Виберіть рівень складності");
    FuncButton1.setText("Легкий");
    FuncButton2.setText("Середній");
    FuncButton3.setText("Важкий");

    Layout.addWidget(&Title,0,0);
    Layout.addWidget(&FuncButton1,1,0);
    Layout.addWidget(&FuncButton2,2,0);
    Layout.addWidget(&FuncButton3,3,0);

    QObject::connect(&FuncButton1,SIGNAL(clicked()),this,SLOT(SetDifficulty()));
    QObject::connect(&FuncButton2,SIGNAL(clicked()),this,SLOT(SetDifficulty()));
    QObject::connect(&FuncButton3,SIGNAL(clicked()),this,SLOT(SetDifficulty()));
}


void Menu::SetDifficulty()
{
    QPushButton *s = dynamic_cast<QPushButton*>(QObject::sender());
    QString dif = s->text();

    if(dif == "Легкий")
        difficulty = 1;
    else if(dif == "Середній")
        difficulty = 2;
    else
        difficulty = 3;


    qDebug() << dif << ' ' << difficulty;
    QObject::disconnect(&FuncButton1,SIGNAL(clicked()),this,SLOT(SetDifficulty()));
    QObject::disconnect(&FuncButton2,SIGNAL(clicked()),this,SLOT(SetDifficulty()));
    QObject::disconnect(&FuncButton3,SIGNAL(clicked()),this,SLOT(SetDifficulty()));

    Title.hide();
    FuncButton1.hide();
    FuncButton3.hide();
    FuncButton2.hide();
    emit StartGame(players, difficulty);
}

void Menu::Start(PlayerStat prof)
{
    delete Login;
    Profile = prof;
    Wnd->setLayout(&Layout);
    MainMenu();
}
