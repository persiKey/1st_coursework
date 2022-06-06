#ifndef FUNC_H
#define FUNC_H

#include <QApplication>
#include "QWidget"
#include "constants.h"
using Types::PlayerStat;

// Перевірити наявінсть усіх файлів та налаштувати програму до старту
void PrepareAppToStart(QApplication& a);
// Записати профіль у файл
void saveStat(PlayerStat*);
// Примусово опрацювати події та зупинити виконання на проміжок часу
void ProcessAndPause(int msec);
// Налаштувати головне вікно
void SetUpWnd(QWidget* wnd);
#endif // FUNC_H
