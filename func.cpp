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

void Check(const QString& str)
{
    if(!QFile::exists(str))
    {
        char message[50] = "File not found: ";
        strcpy(message,str.toStdString().c_str());
        MessageBoxA(GetActiveWindow(),"Error!",message,MB_ICONERROR);
        exit(-1);
    }
}


void PrepareAppToStart()
{
    if(QFontDatabase::addApplicationFont("src\\Hoyle Playing Cards.ttf" ) == -1)
    {
        MessageBoxA(GetActiveWindow(),"Error!","Font not found",MB_ICONERROR);
        exit(-1);
    }

    Check("src\\hearts.png");
    Check("src\\tiles.png");
    Check("src\\clovers.png");
    Check("src\\pikes.png");
    Check("src\\cover.png");

}

void SetUpWnd(QWidget* Wnd)
{
    Wnd->move((QGuiApplication::primaryScreen()->geometry().width() - Constants::WINDOW_WIDTH)/2,
                 QGuiApplication::primaryScreen()->geometry().height() - Constants::WINDOW_HEIGHT - 40);
    Wnd->setFixedSize(Constants::WINDOW_WIDTH,Constants::WINDOW_HEIGHT);
    Wnd->setWindowTitle("Карткова гра \"Курка\" - persiKey");
}
