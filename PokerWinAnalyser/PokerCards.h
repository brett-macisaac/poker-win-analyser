#pragma once

#include<vector>
#include<algorithm> // std::stable_sort
#include<iostream> // std::cout
#include<stdexcept>
#include<stdlib.h> // rand
#include<string>
#include<sstream>

#include"PokerCard.h"
#include"HandValue.h"
#include"UtilityFunctions.h"

/* Adapter of std::vector<PokerCard>

*/
class PokerCards
{

public:

    // If false, only the card values are displayed; the text representation of the value of the hand is omitted in the 'ToString()' method
    static bool s_display_hand_value;


protected:

    std::vector<PokerCard> f_cards;

    HandValue f_value;

    // perhaps a bunch of flags to identify aspects of the cards. e.g. f_contains_5_straight.


public:

    // The initial value should probably be 0. Maybe a child class can have an initial size of 2.
    PokerCards(int a_initial_size = 0, bool a_community_cards = false, bool a_are_face_up = true);

    PokerCards(const PokerCards& a_cards);

    PokerCards(const std::string& a_cards, bool a_set_hand = true, bool a_select_cards = true, 
               bool a_community_cards = false, bool a_are_face_up = true);

    void Shuffle();

    void Sort(bool a_ascending = true);

    std::string ToString() const;

    void ReSize(int a_new_size);

    void RemoveCard(const PokerCard& a_card);

    void RemoveCards(const PokerCards& a_cards);

    void AddCard(const PokerCard& a_card);

    void AddCards(PokerCards& a_cards);

    void CopyCard(const PokerCard& a_card, int a_index = 0);

    void CopyCards(PokerCards& a_cards, int a_index = 0);

    /*
        * This method sets the non-community cards of f_cards equal to those of a_cards. 
    */
    void CopyCards_NonCommunity(PokerCards& a_cards);

    PokerCard& GetTopCard();

    int GetSize() const;

    // e.g. Get number of aces.
    int GetAmountOfValue(int a_value) const;

    int GetAmountOfSuit(Suit a_suit) const;

    int GetHighestValue() const;

    /* Accessor of f_value
    */
    const HandValue& GetValue() const;

    // Maybe this should be a method in a sub-class called Hand.
    bool IsPaired() const;

    // Returns true if one of the card's values match a_value.
    bool ValueMatch(int a_value) const;

    void SetValueTallies(int* a_value_tallies, bool a_reset_array = true) const;

    int NumOfNples(int a_N) const;

    /* Accessor of f_cards
        * This method returns true if f_dice (either the active or selected portion) contains a straight of length a_n.
          e.g. the dice |2|3|4|5|3|6| contains the five-straight 2-3-4-5-6, and so the method will return true.

        * Parameters:
            * a_n: the length of the straight to search for.
        
        * Return Value:
            * If the straight couldn't be found, -1 is returned; if the straight is found, the magnitude of the straight
              is returned: e.g. if the hand is '56789', 9 is returned.         
            * The value of the highest available N-straight is returned: e.g. if the hand is '56789T', then 10 is returned,
              as opposed to 9.
    */
    int IsNstraight(int a_n = 5) const;

    /* Accessor of f_cards
        * The same as IsNstraight except the straight must also be a flush.
    */
    int IsNstraightFlush(int a_n = 5, Suit* a_suit = nullptr) const;

    bool IsDoubleBarrelStrDr(int a_size_straight = 5) const;

    // Returns the highest frequency of a value: e.g. in '555442', the highest frequency is 3 (the 5s).
    int GetHighestAmountOfValue() const;

    int GetHighestAmountOfSuits() const;

    /* Mutator of f_value
        * Sets f_value in accordance with f_cards. 
    */
    void SetValue(bool a_select_cards = true);

    /* Mutator of f_value
        * Sets f_value to a_value.
    */
    void SetValue(const HandValue a_value);

    /* Mutator of f_cards
    */
    void SelectAll();

    /* Mutator of f_cards
    */
    void UnselectAll();

    // Maybe return -1 if it's not there, and if it is, return the value of the highest card in the straight.
    //int IsNstraight(int a_n);

    std::vector<PokerCard>::iterator begin();

    std::vector<PokerCard>::iterator end();

    std::vector<PokerCard>::const_iterator begin() const;

    std::vector<PokerCard>::const_iterator end() const;



    PokerCard& operator[](int a_index);

    friend std::ostream& operator<<(std::ostream& a_ostream, const PokerCards& a_cards);

    PokerCards& operator=(const PokerCards& a_rhs);

    bool operator==(const PokerCards& a_lhs) const;

    bool operator!=(const PokerCards& a_lhs) const;

    bool operator<(const PokerCards& a_lhs) const;

    bool operator>(const PokerCards& a_lhs) const;

    bool operator>=(const PokerCards& a_lhs) const;

    bool operator<=(const PokerCards& a_lhs) const;



    static bool Comparator_Value_Ascending(const PokerCards& a_rhs, const PokerCards& a_lhs);

    static bool Comparator_Value_Descending(const PokerCards& a_rhs, const PokerCards& a_lhs);
};

// Implementation of std::hash<T>, which allows for PokerCards to be used as the key of unordered associative containers
// such as unordered_map.
namespace std
{
    template <>
    class hash<PokerCards>
    {

    public:

        size_t operator()(const PokerCards& a_cards) const
        {
            // The summation of the combination's indexes.
            size_t l_hash = 0;

            for (int i = 0; i < a_cards.GetSize(); ++i)
            {
                l_hash += ( const_cast<PokerCards&>(a_cards)[i].GetValue() + 
                            (int)const_cast<PokerCards&>(a_cards)[i].GetSuit() ) * (i + 1);
            }

            return l_hash;
        }

    };
};
