#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants {

    constexpr int WINDOW_WIDTH = 1280;
    constexpr int WINDOW_HEIGHT = 830;

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

    constexpr int SMALL_BUT_SIZE = 30;
    constexpr int COUNTER_SIZE = 25;
    constexpr int PLAYER_HOLDER_WIDTH = (CARD_WIDTH + VISIBLE_CARDS_SPACING) * VISIBLE_CARDS_IN_HAND + CARD_WIDTH/2 + VISIBLE_CARDS_SPACING ;
    constexpr int ENEMY_HOLDER_SIZE_VALUE = (CARD_WIDTH + VISIBLE_CARDS_SPACING) * VISIBLE_CARDS_IN_HAND - VISIBLE_CARDS_SPACING;

    constexpr char SAVES_DIR_NAME[] = "saves";

    constexpr int MAX_NEXT_CARDS = 13;

    constexpr int TACT_DELAY = 700;
    constexpr int PLACE_DELAY = 300;
}

namespace Types {

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

    struct PlayerStat
    {
        wchar_t name[20];
        int games_played;
        float win_rate;
        bool last_game_win;
        int last_game_duration;
    };

}

#endif // CONSTANTS_H
