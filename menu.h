#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QtWidgets>
#include "constants.h"
#include "login.h"

using Types::Difficulty;

class Menu : public QObject
{
    Q_OBJECT
    // Віджет заходу в профіль
    LoginWidget* Login;
    // Вікно, на якому все буде відображуватися
    QWidget* Wnd;
    // Головний напис
    QLabel Title;
    // Розміщення елментів
    QGridLayout Layout;
    // Текстове поле, де буде відображено статистику
    QTextBrowser* StatInfo;
    // Кнопка управління
    QPushButton FuncButton1;
    // Кнопка управління
    QPushButton FuncButton3;
    // Кнопка управління
    QPushButton FuncButton2;
    // Кількість обраних гравців
    int players;
    // Обрана складність
    Difficulty Diff;
    // Профіль
    PlayerStat Profile;

private slots:
    //Меню вибору гравців
    void PlayersMenu();
    //Меню вибору складності
    void DifficultyMenu();
    //Встановлює кількість вибраних гравців
    void SetPlayers();
    //Встановлює обрану складність
    void SetDifficulty();
    //Відображає статистику профілю
    void StatMenu();
    //Обробник кнопки "Назад"
    void Back();
    //Обробник кнопки "Вихід"
    void Exit();
public slots:
    // Пустий обробник, що може бути викликаний щоб відобразити голвне меню
    void MainMenu();
    //Обробник події, коли створено або вибрано профіль
    void Start(PlayerStat);
signals:
    void StartGame(int pl, Difficulty dif, PlayerStat*);

public:
    Menu(QWidget* parent = nullptr);
    //Встановлює вікно на якому буде відображатися меню
    void setWnd(QWidget* wnd);

};

#endif // MENU_H
