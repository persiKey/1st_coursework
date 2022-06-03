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
    vector<int> indexes;
    size_t lenght;
};


class AI
{
    int GetLenght(deque<const Card*> &Cards, CardValue Value);
    void GetPopularSuits(CardSuit *res, const vector<Element> &Suitable);
    int DetermineSuitIndex(CardSuit value,CardSuit Popularity[2]);
    Element FindBetter(vector<Element>& Elements,int el_index, CardSuit OpenSuit);
    Element GetChoosenElement(vector<Element>& Elements, CardSuit OpenSuit);
public:
    AI();
    vector<int> Decide(const vector<const Card*>* Hand,const deque<const Card*>* NextCards,const deque<const Card*>* PossibleNextCards, CardSuit OpenSuit);
    vector<int> PrimitveDecide(const vector<const Card*>& Hand,const CardSuit OpenSuit);
};

#endif // AI_H
