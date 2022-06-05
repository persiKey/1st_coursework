#include "ai.h"
#include <limits.h>
#include <algorithm>
#include <map>

AI::AI(){}

int AI::GetLenght(const deque<const Card *> &Cards, CardValue Value)
{
    for(int i = 0; i < Cards.size();++i)
    {
        if(Cards[i]->Value == Value)
            return  i;
    }
    return INT_MAX;
}

CardSuit AI::GetPopularSuits(const vector<Element> &Suitable)
{
    std::map<CardSuit,int> freq;
    for(int i = 0; i < Suitable.size();++i)
    {
        freq[Suitable[i].Slots[0]->Suit]++;
    }
    int max = 0;
    CardSuit max_suit;
    for(auto i : freq)
    {
        if(i.second > max)
        {
            max = i.second;
            max_suit = i.first;
        }
    }
    return max_suit;
}

Element AI::FindBetter(const vector<Element> &Elements,int comp_el_index, CardSuit OpenSuit)
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

    CardSuit PopularSuit = GetPopularSuits(Suitable);
    Element test_el;
    for(auto el : Suitable)
    {
        if(el.Slots[0]->Suit == PopularSuit)
            return el;
    }
}

Element AI::GetChoosenElement(const vector<Element> &Elements, CardSuit OpenSuit, bool is_real)
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
            if(Elements.size() == 2 && Elements[(i+1) % 2].Slots.size() == 1 && Elements[(i+1) % 2].Slots[0]->Suit != OpenSuit && is_real && Elements[(i+1) % 2].lenght)
                    return Elements[(i+1) % 2];

            return FindBetter(Elements,i,OpenSuit);
        }
    }
}

void AI::FindElementsInHand(vector<Element> &Elements, vector<const Card *> Hand)
{
    Element el;
    for(int i = 0; i < Hand.size(); ++i)
    {
        el.Slots.clear();
        el.Slots.push_back(Hand[i]);
        for(int k = i + 1; k < Hand.size();++k)
        {
            if(Hand[i]->Value == Hand[k]->Value)
            {
                el.Slots.push_back(Hand[k]);
                Hand.erase(Hand.begin()+k);
                --k;
            }
        }
        Hand.erase(Hand.begin()+i);
        --i;
        Elements.push_back(el);
    }
}

vector<int> AI::Decide(const vector<const Card *> *Hand,const deque<const Card *> *NextCards,const deque<const Card*>* PossibleNextCards, CardSuit OpenSuit)
{
    vector<Element> Elements;
    deque<const Card*> AllNextCards;
    AllNextCards.assign(NextCards->begin(),NextCards->end());
    AllNextCards.insert(AllNextCards.end(), PossibleNextCards->begin(),PossibleNextCards->end());

    FindElementsInHand(Elements,*Hand);

    for(int i = 0; i < Elements.size();++i)
    {
        Elements[i].lenght = GetLenght(AllNextCards,Elements[i].Slots[0]->Value);
    }
    std::sort(Elements.begin(),Elements.end(),[](Element &A, Element &B){return A.lenght > B.lenght;});

    Element choosenEl = GetChoosenElement(Elements,OpenSuit, !NextCards->empty());

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
