#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QtWidgets>

class Game : public QObject
{
    Q_OBJECT
    int players;
    int difficulty;
    QWidget* Wnd;
    QGridLayout Layout;
public:
    explicit Game(QObject *parent = nullptr);
    void setWnd(QWidget* wnd);
public slots:
    void Init(int pl, int dif);
signals:

};

#endif // GAME_H
