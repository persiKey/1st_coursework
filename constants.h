#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr int CARD_WIDTH = 110;
constexpr int CARD_HEIGHT = 170;

constexpr int NUM_OF_SUITS = 4;
constexpr int NUM_OF_VALUES = 9;

constexpr int SUIT_SIZE = 30;
constexpr int CENTER_SUIT_SIZE = 50;
constexpr int VALUE_FONT= 35;

enum class CardSuit
{
    HEARTS = 0,
    TILES,
    CLOVERS,
    PIKES
};

enum class CardValue
{
    _6 = 0,
    _7,
    _8,
    _9,
    _10,
    JACK,
    QUEEN,
    KING,
    ACE
};

#endif // CONSTANTS_H
