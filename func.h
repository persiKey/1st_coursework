#ifndef FUNC_H
#define FUNC_H

#include <QApplication>
#include "QWidget"
#include "constants.h"
using Types::PlayerStat;

void PrepareAppToStart(QApplication& a);
void saveStat(PlayerStat*);
void ProcessAndPause(int msec);
void SetUpWnd(QWidget* wnd);
#endif // FUNC_H
