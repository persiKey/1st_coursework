#ifndef PLAYERCARDDISPLAYER_H
#define PLAYERCARDDISPLAYER_H

#include <QObject>
#include <QWidget>
#include <QPixmap>

class PlayerCardDisplayer : public QWidget
{
    Q_OBJECT
    QPixmap* PixCard;
    int index;
public:
    explicit PlayerCardDisplayer(QWidget *parent = nullptr);
    void updatePix(QPixmap* Pix);
    void setIndex(int ind);
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void printSelection();
    void unprintSelection();

signals:
    void Choosen(int);
};

#endif // PLAYERCARDDISPLAYER_H
