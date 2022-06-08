#ifndef DEQUEDISPLAYER_H
#define DEQUEDISPLAYER_H

#include <QWidget>
#include <QPixmap>
#include <cardmaker.h>

class DequeDisplayer : public QWidget
{
    Q_OBJECT
    // Текстура колоди
    QPixmap deque;
    // Кількість відображуваних один на одному карт
    int DisplayedCardsCount;

    //Очистити текстуру колоди
    void ClearDeque();
    //Намалювати карти в колоді один на одному
    void DrawCoverCards();
public:
    explicit DequeDisplayer(QWidget *parent = nullptr);
    //Візуально додати карту в колоду
    void AddCard();
    //Візуально видалити карту з колоди
    void ExtractCard();
    //Очистити від карт
    void Clear();
    //Подія, що викликається при малюванні колоди
    void paintEvent(QPaintEvent *e);
signals:

};

class OpenDequeDisplayer : public QWidget
{
    Q_OBJECT
    // Текстура колоди
    QPixmap deque;
    // Інструмент, що робить та зберігає текстури карт
    CardMaker* maker;
public:
    explicit OpenDequeDisplayer(QWidget *parent = nullptr, CardMaker* maker = nullptr);
    //Очистити текстуру відкритої колоди
    void ClearDeque();
    //Намалювати карту поверх відкритої колоди
    void PrintCardOver(const Card* card);
    //Подія, що викликається при малюванні колоди
    void paintEvent(QPaintEvent *e);
};

#endif // DEQUEDISPLAYER_H
