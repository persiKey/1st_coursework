#include "menu.h"
#include <sstream>
#include <iomanip>

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

void Menu::Start(PlayerStat prof)
{
    delete Login;
    Profile = prof;
    Wnd->setLayout(&Layout);
    MainMenu();
}

void Menu::MainMenu()
{

    Title.setText("Головне меню");
    Title.setStyleSheet("font: 50px;");
    FuncButton1.setText("Почати");
    FuncButton1.setFixedSize(200,100);
    FuncButton2.setText("Переглянути\nстатистику");
    FuncButton2.setFixedSize(200,100);
    FuncButton3.setText("Вихід");
    FuncButton3.setFixedSize(200,100);
    Layout.addWidget(&Title,0,0,1,3); Title.show();
    Layout.addWidget(&FuncButton1,1,1); FuncButton1.show();
    Layout.addWidget(&FuncButton2,2,1); FuncButton2.show();
    Layout.addWidget(&FuncButton3,3,1); FuncButton3.show();

    QObject::connect(&FuncButton1,SIGNAL(clicked()),this,SLOT(PlayersMenu()));
    QObject::connect(&FuncButton2,SIGNAL(clicked()),this,SLOT(StatMenu()));
    QObject::connect(&FuncButton3,SIGNAL(clicked()),this, SLOT(Exit()));
}

void Menu::PlayersMenu()
{
    QObject::disconnect(&FuncButton1,SIGNAL(clicked()),this,SLOT(PlayersMenu()));
    QObject::disconnect(&FuncButton2,SIGNAL(clicked()),this,SLOT(StatMenu()));
    QObject::disconnect(&FuncButton3, SIGNAL(clicked()),this, SLOT(Exit()));

    Title.setText("Виберіть кількість гравців");
    FuncButton1.setText("2");
    FuncButton2.setText("3");
    FuncButton3.setText("4");


    Layout.addWidget(&Title,0,0,1,3);
    Layout.addWidget(&FuncButton1,1,0);
    Layout.addWidget(&FuncButton2,1,1);
    Layout.addWidget(&FuncButton3,1,2);

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

    Layout.addWidget(&Title,0,0,1,3);
    Layout.addWidget(&FuncButton1,1,1);
    Layout.addWidget(&FuncButton2,2,1);
    Layout.addWidget(&FuncButton3,3,1);

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
    emit StartGame(players, difficulty, &Profile);
}

void Menu::StatMenu()
{
    QObject::disconnect(&FuncButton2,SIGNAL(clicked()),this,SLOT(StatMenu()));
    Title.setText("Статистика");
    FuncButton1.hide();
    FuncButton3.hide();
    FuncButton2.setText("Назад");
    QObject::connect(&FuncButton2,SIGNAL(clicked()),this,SLOT(Back()));

    QFont f1;
    f1.setPointSize(20);
    std::wstring name(Profile.name);
    std::stringstream InSt;
    InSt << "Ім'я: " << std::string(name.begin(), name.end());
    InSt << "<br/>Зіграно ігор: " << Profile.games_played
        << "<br/>Коефіцієнт виграшу: " << std::setprecision(2) << std::showpoint << Profile.win_rate
        << "<br/>Остання гра виграна: " << (Profile.last_game_win ? "Так" : "Ні")
        << "<br/>Тривалість останньої гри(с): " << Profile.last_game_duration;
    StatInfo = new QTextBrowser;

    StatInfo->setText(QString::fromStdString(InSt.str()));
    StatInfo->setFont(f1);
    StatInfo->setAlignment(Qt::AlignHCenter);
    StatInfo->setFixedSize(Constants::WINDOW_WIDTH/2,Constants::WINDOW_HEIGHT/3.5);
    Layout.addWidget(StatInfo,1,1);
    Layout.addWidget(&FuncButton2,2,1,Qt::AlignCenter);

}

void Menu::Back()
{
    QObject::disconnect(&FuncButton2,SIGNAL(clicked()),this,SLOT(Back()));
    Layout.removeWidget(StatInfo);
    delete StatInfo;
    MainMenu();
}

void Menu::Exit()
{
    QApplication::quit();
}
