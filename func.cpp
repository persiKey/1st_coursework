#include "func.h"
#include <QApplication>
#include <QFontDatabase>
#include <QFile>
#include <QScreen>
#include <thread>
#include <fstream>
#include "constants.h"
#include "windows.h"

using std::string;
using Constants::SAVES_DIR_NAME;
using Types::PlayerStat;

void saveStat(PlayerStat *stat)
{
    std::wstring Name(stat->name);
    std::string path = SAVES_DIR_NAME + string("\\")+ string(Name.begin(),Name.end()) + string(".save");
    std::ofstream file(path, std::ios_base::binary);
    file.write((char*)stat, sizeof(*stat));
    file.close();
}

void ProcessAndPause(int msec)
{
    QApplication::processEvents();
    std::this_thread::sleep_for(std::chrono::milliseconds(msec));
}
#pragma comment(lib, "user32.lib")
void Check(const QString& str)
{
    if(!QFile::exists(str))
    {
        char message[50] = "File not found: ";
        strcat_s(message,str.toStdString().c_str());
        MessageBoxA(GetActiveWindow(),message,"Error!",MB_ICONERROR);
        exit(-1);
    }
}


void PrepareAppToStart(QApplication(&a))
{
    if(QFontDatabase::addApplicationFont("src\\Hoyle Playing Cards.ttf" ) == -1)
    {
        MessageBoxA(GetActiveWindow(),"Font not found","Error!",MB_ICONERROR);
        exit(-1);
    }

    Check("src\\hearts.png");
    Check("src\\tiles.png");
    Check("src\\clovers.png");
    Check("src\\pikes.png");
    Check("src\\cover.png");
    a.setStyleSheet("QPushButton{"
                    "font: 16px;"
                    "background-color:lightgray;"
                    "border-radius:15%;"
                    "border: 1.5px solid black;}"
                    "QPushButton:hover{background-color:white;"
                    "border: 2px dashed gray}");
}

void SetUpWnd(QWidget* Wnd)
{
    Wnd->setObjectName("Back");
    Wnd->move((QGuiApplication::primaryScreen()->geometry().width() - Constants::WINDOW_WIDTH)/2,
                 QGuiApplication::primaryScreen()->geometry().height() - Constants::WINDOW_HEIGHT - 40);
    Wnd->setFixedSize(Constants::WINDOW_WIDTH,Constants::WINDOW_HEIGHT);
    Wnd->setWindowTitle("Карткова гра \"Курка\" - persiKey");
}
