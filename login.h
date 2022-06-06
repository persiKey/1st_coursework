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
    QVBoxLayout* mainLayout;
    QHBoxLayout* subLayout;
    QComboBox* profileSelector;
    QLineEdit* profileNameEdit;
    QLabel* mainText;
    QLabel* subText;
    QPushButton* funcButton1;
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
