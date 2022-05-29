#ifndef AI_H
#define AI_H

#include <vector>
#include <deque>
#include "constants.h"

using std::vector;
using std::deque;


struct Element
{
    vector<Card*> Slots;
    vector<int> indexes;
    size_t lenght;
};


class AI
{
    int GetLenght(deque<Card*> &Cards, CardValue Value);
    void GetPopularSuits(CardSuit *res, vector<Element> &Suitable);
    int DetermineSuitIndex(CardSuit value,CardSuit Popularity[2]);
    Element FindBetter(vector<Element>& Elements,int el_index, CardSuit OpenSuit);
    Element GetChoosenElement(vector<Element>& Elements, CardSuit OpenSuit);
public:
    AI();
    vector<int> Decide(vector<Card*>* Hand, deque<Card*>* NextCards,deque<Card*>* PossibleNextCards, CardSuit OpenSuit);

};

#endif // AI_H
