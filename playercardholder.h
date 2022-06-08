#ifndef PLAYERCARDHOLDER_H
#define PLAYERCARDHOLDER_H

#include <QObject>
#include <QWidget>
#include <QPushButton>

#include "playercarddisplayer.h"
#include "constants.h"
#include "cardmaker.h"
#include <vector>
using std::vector;

using Constants::VISIBLE_CARDS_IN_HAND;
using Types::Card;
using Types::CardSuit;
using Types::CardValue;

class PlayerCardHolder : public QWidget
{
    Q_OBJECT
    // Розміщення елементів
    QLayout* Layout;
    // Кнопка для пролистування карт вліво
    QPushButton CtrlLeft;
    // Кнопка для пролистування карт вправо
    QPushButton CtrlRight;

    // Інструмент для створення та збереження текстур карт
    CardMaker *cardMaker;
    // Форми, в яких будуть малюватися текстури карт
    PlayerCardDisplayer VisibleCards[VISIBLE_CARDS_IN_HAND];
    // Зміщення відображуваних карт
    int display_pos;

    // Карти в руці
    const vector<const Card*>* HandCards;
    // Індекси обраних карт
    vector<int> ChoosenCardsIndexes;
    // Масть відкритої карти
    CardSuit *DequeSuit;
    // Значення вже обраної карти
    CardValue SelectedValue;

    //Оновити карти, які відображаються в руці
    void UpdateVisibleCards();
    // Оновити карти, які вибули
    void UpdateExtractedCards();
    // Показати кнопки для пролистування карт
    void ShowCtrlButtons();
    // Сховати кнопки для пролистування карт
    void HideCtrlButtons();

public:
    explicit PlayerCardHolder(QWidget *parent = nullptr, CardMaker* maker = nullptr,const vector<const Card*>* Cards= nullptr);
    // Показати візуально додавання нової карти
    void AddCard();
    // Показати візуально видалення карт
    void ExtractCards();
    // Отримати індекси карт, що були вибрані
    vector<int> GetIndexes();
    // Очистити індекси карт, що були вибрані
    void ClearIndexes();
    // Оновити масть відкритої карти
    void UpdateDequeSuit(CardSuit *suit);

private slots:
    //Метод, що викликаєтсься, коли натиснуто та ітерфейсну кнопку для пролистування вліво
    void CheckLeft();
    //Метод, що викликаєтсься, коли натиснуто та ітерфейсну кнопку для пролистування вправо
    void CheckRight();

public slots:
    //Метод, що викликається, коли на якусь карту натуснуто
    void CardChoosen(int);
};

#endif // PLAYERCARDHOLDER_H
