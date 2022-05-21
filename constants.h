#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr int CARD_WIDTH = 110;
constexpr int CARD_HEIGHT = 170;

constexpr int NUM_OF_SUITS = 4;
constexpr int NUM_OF_VALUES = 9;

constexpr int SUIT_SIZE = 30;
constexpr int CENTER_SUIT_SIZE = 50;
constexpr int VALUE_FONT= 35;

constexpr int VISIBLE_CARDS_IN_HAND = 6;
constexpr int VISIBLE_CARDS_SPACING = 10;

constexpr int DEQUE_WIDTH = CARD_WIDTH*1.2;
constexpr int DEQUE_HEIGHT = CARD_HEIGHT*1.1;
constexpr int DEQUE_SPACING = 10;
constexpr int DEQUE_OFFSET = 5;
constexpr int MAX_DEQUE_DISPLAYING_CARDS = 4;

enum class GameState
{
    WIN,
    LOSE,
    PAUSE
};

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

struct Card
{
    CardSuit Suit;
    CardValue Value;
};

enum class CardOrientation
{
    HOR,
    VER
};

#endif // CONSTANTS_H
