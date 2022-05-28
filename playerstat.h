#ifndef PLAYERSTAT_H
#define PLAYERSTAT_H

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>

struct PlayerStat
{
    wchar_t name[20];
    int games_played;
    float win_rate;
    bool last_game_win;
    int last_game_duration;
};

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
    bool ValidateName(QString );

private slots:
    void ChooseProfileClicked();
    void CreateNewProfileClicked();
    void CreateProfile();

public:
    explicit LoginWidget(QWidget* parent);

signals:
    void ProfileEntered(PlayerStat player);
};
void saveStat(PlayerStat*);
#endif // PLAYERSTAT_H