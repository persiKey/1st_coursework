#include "playerstat.h"
#include <string>
#include <vector>
#include <fstream>
#include "windows.h"

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;

using Constants::SAVES_DIR_NAME;

void GetFileList(vector<string> &file_list)
{
    file_list.clear();
    string path = SAVES_DIR_NAME + string("\\*.save");

    WIN32_FIND_DATAA findData;
    HANDLE findFile = FindFirstFileA(path.c_str(), &findData);
    if (findFile == INVALID_HANDLE_VALUE)
    {
        FindClose(findFile);
        return;
    }
    do
    {
        file_list.push_back(findData.cFileName);
    } while (FindNextFileA(findFile, &findData));

    FindClose(findFile);

}


LoginWidget::LoginWidget(QWidget* parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(Constants::WINDOW_WIDTH/4,0, Constants::WINDOW_WIDTH/4,0);

    mainText = new QLabel("Вітаю!");
    mainText->setStyleSheet("font: 30px;");
    mainText->setAlignment(Qt::AlignmentFlag::AlignCenter);

    subLayout = new QHBoxLayout;

    profileSelector = new QComboBox;
    vector<string> files;
    GetFileList(files);
    for(auto file : files)
        profileSelector->addItem(file.substr(0,file.rfind('.')).c_str());

    funcButton1 = new QPushButton("Вибрати профіль");
    funcButton1->setMinimumWidth(135);
    QObject::connect(funcButton1,SIGNAL(clicked()),this,SLOT(ChooseProfileClicked()));

    subLayout->addWidget(profileSelector);
    subLayout->addWidget(funcButton1);

    funcButton2 = new QPushButton("Створити новий профіль");
    QObject::connect(funcButton2,SIGNAL(clicked()),this, SLOT(CreateNewProfileClicked()));

    mainLayout->setAlignment(Qt::AlignmentFlag::AlignCenter);
    mainLayout->addWidget(mainText);
    mainLayout->addLayout(subLayout);
    mainLayout->addWidget(funcButton2);

    this->setFixedSize(parent->size());
    this->setLayout(mainLayout);

}


void LoginWidget::ChooseProfileClicked()
{
    if(profileSelector->currentText().isEmpty())
        return;
    ifstream file(SAVES_DIR_NAME + string("\\") + profileSelector->currentText().toStdString() + string(".save"), std::ios_base::binary);
    PlayerStat player;
    file.read((char*)&player, sizeof(PlayerStat));
    emit ProfileEntered(player);
}

void LoginWidget::CreateNewProfileClicked()
{
    profileSelector->hide();
    funcButton2->hide();
    mainText->setText("Введіть ім'я нового профілю");
    profileNameEdit = new QLineEdit;


    QObject::disconnect(funcButton1,SIGNAL(clicked()),this,SLOT(ChooseProfileClicked()));
    funcButton1->setText("Створити");
    QObject::connect(funcButton1,SIGNAL(clicked()),this,SLOT(CreateProfile()));

    subLayout->addWidget(profileNameEdit);
    subLayout->addWidget(funcButton1);

    subText = new QLabel("*ім'я не може бути довшим за 20 символів та містити щось окрім латинських букв та цифр");

    mainLayout->addWidget(subText);
}

bool LoginWidget::ValidateName(QString name)
{
    if(name.isEmpty()){return false;}
    for (int i = 0; i < name.size() ; ++i)
    {
        if(!((name[i] >= '0' && name[i] < '0' + 10) ||
                (name[i] > 'a' && name[i] < 'a' + 26) ||
                (name[i] > 'A' && name[i] < 'A' + 26)))
            return false;
    }
    return true;
}

void LoginWidget::CreateProfile()
{
    if(profileNameEdit->text().size() > 20 || !ValidateName(profileNameEdit->text())) return;
    std::string path = SAVES_DIR_NAME + string("\\") + profileNameEdit->text().toStdString() + string(".save");
    if(ifstream(path).is_open()) return;
    if(CreateDirectoryA(SAVES_DIR_NAME, NULL) || GetLastError() == ERROR_ALREADY_EXISTS)
    {
        ofstream file(path, std::ios_base::binary);
        PlayerStat player; std::fill(player.name,player.name+20,0);
        profileNameEdit->text().toWCharArray(player.name);
        player.games_played = 0;
        player.win_rate = 0;
        player.last_game_win = false;
        player.last_game_duration = 0;
        file.write((char*)&player, sizeof(player));
        emit ProfileEntered(player);
        file.close();
    }
}
