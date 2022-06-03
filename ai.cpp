#include "ai.h"
#include <limits.h>
#include <algorithm>
#include <map>

using Constants::NUM_OF_SUITS;

AI::AI(){}

int AI::GetLenght(deque<const Card *> &Cards, CardValue Value)
{
    for(int i = 0; i < Cards.size();++i)
    {
        if(Cards[i]->Value == Value)
            return  i;
    }
    return INT_MAX;
}

void AI::GetPopularSuits(CardSuit *res,const vector<Element> &Suitable)
{
    typedef std::pair<const CardSuit,int> SuitFrequense ;

    std::map<CardSuit,int> freq;
    for(int i = 0; i < Suitable.size();++i)
    {
        freq[Suitable[i].Slots[0]->Suit]++;
    }
    CardSuit max_el;
    for(int i = 0; i < freq.size() && i < 2;++i)
    {
        max_el = std::max_element(freq.begin(), freq.end(),
                [](SuitFrequense& A, SuitFrequense &B){return A.second < B.second;})->first;
        res[i] = max_el;
        freq.erase(max_el);
    }
}

int AI::DetermineSuitIndex(CardSuit value, CardSuit Popularity[])
{
    int suit = 2;
    if(value == Popularity[0])
        suit = 0;
    else if(value == Popularity[1] )
        suit = 1;
    return  suit;
}

Element AI::FindBetter(vector<Element> &Elements,int comp_el_index, CardSuit OpenSuit)
{
    vector<Element> Suitable;
    if(Elements[comp_el_index].Slots.size() == 1) Suitable.push_back(Elements[comp_el_index]);
    for(int k = comp_el_index+1; k < Elements.size(); ++k)
    {
        if(Elements[comp_el_index].lenght != Elements[k].lenght)
            break;
        if(Elements[k].Slots.size() == 1 && Elements[k].Slots[0]->Suit != OpenSuit )
            Suitable.push_back(Elements[k]);
    }
    if(Suitable.size() == 0)
        return Elements[comp_el_index];
    else if (Suitable.size() == 1)
        return Suitable[0];

    CardSuit PopularSuits[2];
    GetPopularSuits(PopularSuits,Suitable);
    int min_index = 0;
    int min_suit;
    if(Elements[comp_el_index].Slots.size() == 1) min_suit = DetermineSuitIndex(Elements[comp_el_index].Slots[0]->Suit,PopularSuits);
    else min_suit = NUM_OF_SUITS+1;
    for(int k = 0; k < Suitable.size();++k)
    {
        int el_suit = DetermineSuitIndex(Suitable[k].Slots[0]->Suit,PopularSuits);
        if( el_suit < min_suit)
        {
            min_index = k;
            min_suit = el_suit;
        }
    }
    return Suitable[min_index];
}

Element AI::GetChoosenElement(vector<Element> &Elements, CardSuit OpenSuit)
{

    for(int i = 0; i < Elements.size();++i)
    {
        if(Elements[i].Slots.size() == 1)
        {
            if(Elements[i].Slots[0]->Suit != OpenSuit)
            {
                return FindBetter(Elements,i,OpenSuit);
            }
            else
                continue;
        }
        else
        {
            return FindBetter(Elements,i,OpenSuit);
        }
    }
}

vector<int> AI::Decide(const vector<const Card *> *Hand,const deque<const Card *> *NextCards,const deque<const Card*>* PossibleNextCards, CardSuit OpenSuit)
{
    vector<Element> Elements;
    deque<const Card*> AllNextCards;
    AllNextCards.assign(NextCards->begin(),NextCards->end());
    AllNextCards.insert(AllNextCards.end(), PossibleNextCards->begin(),PossibleNextCards->end());

    vector<const Card*> HandCopy = *Hand;

    Element el;
    for(int i = 0; i < HandCopy.size(); ++i)
    {
        el.Slots.clear();
        el.Slots.push_back(HandCopy[i]);
        for(int k = i + 1; k < HandCopy.size();++k)
        {
            if(HandCopy[i]->Value == HandCopy[k]->Value)
            {
                el.Slots.push_back(HandCopy[k]);
                HandCopy.erase(HandCopy.begin()+k);
                --k;
            }
        }
        HandCopy.erase(HandCopy.begin()+i);
        --i;
        Elements.push_back(el);
    }

    for(int i = 0; i < Elements.size();++i)
    {
        Elements[i].lenght = GetLenght(AllNextCards,Elements[i].Slots[0]->Value);
    }
    std::sort(Elements.begin(),Elements.end(),[](Element &A, Element &B){return A.lenght > B.lenght;});

    Element choosenEl = GetChoosenElement(Elements,OpenSuit);

    vector<int> choosenIndexes;
    for(int i = 0; i < choosenEl.Slots.size();++i)
    {
        choosenIndexes.push_back(std::find(Hand->begin(),Hand->end(),choosenEl.Slots[i]) - Hand->begin());
    }

    return choosenIndexes;
}

vector<int> AI::PrimitveDecide(const vector<const Card *> &Hand, CardSuit OpenSuit)
{
    std::map<CardValue,int> freq;
    for(auto Card : Hand)
      freq[Card->Value]++;

    int max = 0;
    CardValue Cardvalue;

    for(auto i : freq)
    {
        if(max < i.second)
        {
            max = i.second;
            Cardvalue = i.first;
        }
    }

    if(max == 1)
    {
        for(int i = 0; i < Hand.size();++i)
        {
            if(Hand[i]->Suit != OpenSuit)
            {
                return vector<int>{i};
            }
        }
    }
    vector<int> indexes;
    for(int i = 0; i < Hand.size();++i)
    {
        if(Hand[i]->Value == Cardvalue)
            indexes.push_back(i);
    }

    return indexes;
}
