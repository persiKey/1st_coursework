#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include "constants.h"

using Types::PlayerStat;

class LoginWidget : public QWidget
{
    Q_OBJECT
    // Розміщенні головних елементів
    QVBoxLayout* mainLayout;
    // Розміщення побічних елементів
    QHBoxLayout* subLayout;
    // Випадаючий список з іменами профілю
    QComboBox* profileSelector;
    // Поле вводу імені профілю
    QLineEdit* profileNameEdit;
    // Головний напис
    QLabel* mainText;
    // Рядок-підказка, куди будуть виведені помилки
    QLabel* subText;
    // Кнопка управілння
    QPushButton* funcButton1;
    // Кнопка управління
    QPushButton* funcButton2;
private:
    //Відобразити помилку
    void DisplayError(const QString&);
    //Перевірити логічну допустимість імені та існування вже такого профілю
    bool ValidAll(std::string& );
    //Перевірити ім'я на доупустимі символи
    bool ValidateName(QString );

private slots:
    //Натиснуто на кнопку "Обрати профіль"
    void ChooseProfileClicked();
    //Натиснуто на кнопку "Створити новий профіль"
    void CreateNewProfileClicked();
    //Натиснуто на кнопку "Створити" у вікні сворення
    void CreateProfile();

public:
    explicit LoginWidget(QWidget* parent);

signals:
    void ProfileEntered(PlayerStat player);
};

#endif // LOGIN_H
