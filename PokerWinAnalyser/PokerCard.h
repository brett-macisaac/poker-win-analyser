#pragma once

#include<algorithm> // std::swap
#include<iostream> // std::cout
#include<string> // std::string

enum Suit
{
    // Note the alphabetical order (s > h > d > c), which is important in some poker games for ranking cards.
    Club = 0,
    Diamond,
    Heart,
    Spade
};

/*
    * Ideas:
        * A boolean field such as 'f_face_up': if true, the card is printed face-up (e.g. |Ah|), but if it's false it's
          printed face-down (perhaps |\\|, |Xy|, |Xx|, etc.).
*/
class PokerCard
{

public:

    // The numerical representation of an ace (the highest valued card).
    static const int S_MAX_VALUE = 14;

    // The numerical representation of the two (the lowest valued card).
    // note: technically the lowest value is an ace when considered to be a 1, though this only applies when forming an AS345 (wheel) straight.
    static const int S_MIN_VALUE = 2;

    // The number of unique suits.
    static const int S_NUM_OF_SUITS = 4;

private:

    // [2, 14] ; [2, ace]
    int f_value;

    Suit f_suit;

    bool f_is_community_card;

    bool f_is_face_up;

    // Could be useful for a video game where you show/indent the winning hand or show the best hand of each player at the showdown.
    bool f_is_selected;

    static const char S_CHAR_CARD_BACK_VALUE = 'X';
    static const char S_CHAR_CARD_BACK_SUIT = 'x';

    // Perhaps a boolean called something like f_in_community, a flag that, when true, indicates that a card is shared by
    // all players.


public:

    PokerCard(int a_value = 14, Suit f_suit = Suit::Heart, bool a_is_community_card = true, bool a_is_face_up = true);

    PokerCard(const PokerCard& a_card);

    PokerCard(const std::string& a_card, bool a_is_community_card = false, bool a_is_face_up = true);

    void SwapValuesWith(PokerCard& a_card);

    std::string ToString() const;

    void SetFromString(const std::string& a_string);

    int GetValue() const;

    Suit GetSuit() const;

    bool IsSelected() const;

    bool IsCommunityCard() const;

    bool IsFaceUp() const;

    void SetCard(int a_value, Suit a_suit);

    void SetValue(int a_value);

    void SetCommunityFlag(bool a_is_community_card = true);

    void SetSelected(bool a_is_selected);

    void SetFaceUp(bool a_is_face_up);

    bool operator==(const PokerCard& a_rhs) const;

    bool operator!=(const PokerCard& a_rhs) const;

    bool operator<(const PokerCard& a_rhs) const;

    bool operator>(const PokerCard& a_rhs) const;

    bool operator>=(const PokerCard& a_rhs) const;

    bool operator<=(const PokerCard& a_rhs) const;

    /* = (assignment) Operator (l-value)
        * Assigns the fields of *this to those of a_die.
    */
    PokerCard& operator=(const PokerCard& a_card);

    friend std::ostream& operator<<(std::ostream& a_ostream, const PokerCard& a_card);

    // Perhaps a static function called SuitToChar
    static char SuitToChar(Suit a_suit);

    static char IntToCardVal(int a_card_val);

    static Suit CharToSuit(char a_char);

    static int CardValToInt(char a_char);

    static bool Comparator_Ascending_Value(const PokerCard& a_lhs, const PokerCard& a_rhs);

    static bool Comparator_Descending_Value(const PokerCard& a_lhs, const PokerCard& a_rhs);

};