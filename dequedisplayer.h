#ifndef DEQUEDISPLAYER_H
#define DEQUEDISPLAYER_H

#include <QWidget>
#include <QPixmap>
#include <cardmaker.h>

class DequeDisplayer : public QWidget
{
    Q_OBJECT
    QPixmap deque;
    int DisplayedCardsCount;

    void ClearDeque();
    void DrawCoverCards();
public:
    explicit DequeDisplayer(QWidget *parent = nullptr);
    void AddCard();
    void ExtractCard();
    void paintEvent(QPaintEvent *e);
signals:

};

class OpenDequeDisplayer : public QWidget
{
    Q_OBJECT
    QPixmap deque;
    CardMaker* maker;
public:
    explicit OpenDequeDisplayer(QWidget *parent = nullptr, CardMaker* maker = nullptr);
    void SetCardMaker(CardMaker* maker);
    void ClearDeque();
    void PrintCardOver(Card card);
    void paintEvent(QPaintEvent *e);
};

#endif // DEQUEDISPLAYER_H
