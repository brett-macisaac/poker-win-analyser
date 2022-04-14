#pragma once

#include<vector>
#include<ostream>
#include<string>
#include<sstream>

#include"UtilityFunctions.h"
#include"PokerCard.h" // Suit enum

class PokerCards;

enum HandType
{
    HighCard = 0,
    OnePair,
    TwoPair,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    Quads,
    StraightFlush
};

class HandValue
{

private:

    HandType f_hand_type;

    std::vector<int> f_hand_magnitude;

    // The suit corresponding to the flush or straight-flush.
    Suit f_suit;

    // The maximum number of cards in a hand.   
    static const int S_SIZE_HAND_MAX = 5;


public:

    HandValue();

    HandValue(PokerCards& a_cards, bool a_select_cards = false);

    HandValue(const HandValue& a_hand);

    void Set(PokerCards& a_cards, bool a_select_cards = false);

    HandType GetHandType() const;

    const std::vector<int>& GetHandMagnitude() const;

    std::string ToString() const;

    bool IsSet() const;

    void Unset();



    bool operator==(const HandValue& a_hand) const;

    bool operator!=(const HandValue& a_hand) const;

    bool operator<(const HandValue& a_hand) const;

    bool operator>(const HandValue& a_hand) const;

    bool operator>=(const HandValue& a_hand) const;

    bool operator<=(const HandValue& a_hand) const;

    HandValue& operator=(const HandValue& a_hand);

    friend std::ostream& operator<<(std::ostream& a_ostream, const HandValue& a_hand);


private:

    /* Auxiliary of Set
    */
    void SetMagnitude(PokerCards& a_cards, int* a_value_tallies);

    /* Auxiliary of Set
    */
    void SetHandType(HandType a_type, int a_num_cards);

    /* Auxiliary of SetHandType
    */
    void SetNumOfMagnitudes(int a_num_cards);

    /* Auxiliary of Set
        * This method sets the f_is_selected field of each card in a_cards that forms part of the hand.
        * If a_cards.size() is less than 5, it will be all of them.
    */
    void SelectCards(PokerCards& a_cards);


public:

    static const char* HandTypeToString(HandType a_type);

    static bool Comparator_Ascending(const HandValue& a_rhs, const HandValue& a_lhs);

    static bool Comparator_Descending(const HandValue& a_rhs, const HandValue& a_lhs);

};
