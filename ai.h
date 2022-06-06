#ifndef AI_H
#define AI_H

#include <vector>
#include <deque>
#include "constants.h"

using std::vector;
using std::deque;
using namespace Types;

struct Element
{
    vector<const Card*> Slots;
    size_t lenght;
};


class AI
{
    // Отримати довжину елемента до розширення
    int GetLenght(const deque<const Card*> &Cards, CardValue Value);
    // Отримати найпопулярніше масть серед карт елементів
    CardSuit GetPopularSuits(const vector<Element> &Suitable);
    // Спробувати знайти кращий елемент
    Element FindBetter(const vector<Element>& Elements,int el_index, CardSuit OpenSuit);
    // Отримати елемент, яким варто походити
    Element GetChoosenElement(const vector<Element>& Elements, CardSuit OpenSuit,bool is_real);
    // Визначити елементи в руці
    void FindElementsInHand(vector<Element>& Elements, vector<const Card *> Hand);
public:
    AI();
    // Алгоритм рахування відстані
    vector<int> Decide(const vector<const Card*>* Hand,const deque<const Card*>* NextCards,const deque<const Card*>* PossibleNextCards, CardSuit OpenSuit);
    // Алгоритм скидання карт
    vector<int> PrimitveDecide(const vector<const Card*>& Hand,const CardSuit OpenSuit);
};

#endif // AI_H
