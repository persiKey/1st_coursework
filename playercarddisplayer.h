#ifndef PLAYERCARDDISPLAYER_H
#define PLAYERCARDDISPLAYER_H

#include <QObject>
#include <QWidget>
#include <QPixmap>

class PlayerCardDisplayer : public QWidget
{
    Q_OBJECT
    // Текстура карти
    QPixmap* PixCard;
    // Індекс карти
    int index;
public:
    explicit PlayerCardDisplayer(QWidget *parent = nullptr);
    //Оновити текстуру
    void updatePix(QPixmap* Pix);
    //Встановити  індекс
    void setIndex(int ind);
    // Подія, що викликаєтсья при малюванні карти
    void paintEvent(QPaintEvent *e);
    // Подія, що викликається, коли на карту натиснули мишою
    void mousePressEvent(QMouseEvent *e);
    // Виділіти карту певним кольором
    void printSelection(QColor color = Qt::green);
    //Прибрати виділення
    void unprintSelection();
signals:
    void Choosen(int);
};

#endif // PLAYERCARDDISPLAYER_H
