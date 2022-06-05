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
    int GetLenght(const deque<const Card*> &Cards, CardValue Value);
    CardSuit GetPopularSuits(const vector<Element> &Suitable);
    Element FindBetter(const vector<Element>& Elements,int el_index, CardSuit OpenSuit);
    Element GetChoosenElement(const vector<Element>& Elements, CardSuit OpenSuit,bool is_real);
    void FindElementsInHand(vector<Element>& Elements, vector<const Card *> Hand);
public:
    AI();
    vector<int> Decide(const vector<const Card*>* Hand,const deque<const Card*>* NextCards,const deque<const Card*>* PossibleNextCards, CardSuit OpenSuit);
    vector<int> PrimitveDecide(const vector<const Card*>& Hand,const CardSuit OpenSuit);
};

#endif // AI_H
