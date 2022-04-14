#pragma once

#include<fstream>
#include<iostream>
#include<vector>

#include"Combination.h"
#include"PokerCards.h"

namespace Tests
{
    /* Test of class PokerCards/PokerCard
        * This function tests the ability of the PokerCards and PokerCard classes to be set using strings.
        * This functionality is important for efficient, readable testing of other functionality.
    */
    void SetCardsFromString();

    /* Test of class PokerCards
        * This function tests the PokerCards class' ability to recognise every type of poker hand when the hand
          is the best 5-card hand from a group of 5 cards.
    */
    void HandRecognition_From5Cards();

    /* Test of class PokerCards
        * This function tests the PokerCards class' ability to recognise every type of poker hand when the hand
          is the best 5-card hand from a group of 6 cards.
    */
    void HandRecognition_From6Cards();

    /* Test of class PokerCards
        * This function tests the PokerCards class' ability to recognise every type of poker hand when the hand
          is the best 5-card hand from a group of 7 cards.
    */
    void HandRecognition_From7Cards();

    /* Auxiliary of the 'HandMagnitudeComparison_X' functions
    */
    void HandComparison(std::vector<PokerCards>& a_cards);

    /* Test of class PokerFiveCardHand
        * This function tests whether or not PokerFiveCardHand objects of different HandType can be accurately compared 
          with one another.
            e.g. recognising that a straight is lower than a flush.
    */
    void HandTypeComparison();

    /* Test of class PokerFiveCardHand
        * This function tests whether or not PokerFiveCardHand objects of HandType HighCard can be accurately compared
          with one another.
    */
    void HandMagnitudeComparison_HighCard();

    /* Test of class PokerFiveCardHand
        * This function tests whether or not PokerFiveCardHand objects of HandType OnePair can be accurately compared
          with one another.
            e.g. recognising that |Ad||Ac||4d||6c||7d| is a higher pair than |Kd||Kc||4d||6c||7d|.
    */
    void HandMagnitudeComparison_OnePair();

    /* Test of class PokerFiveCardHand
        * This function tests whether or not PokerFiveCardHand objects of HandType TwoPair can be accurately compared
          with one another.
    */
    void HandMagnitudeComparison_TwoPair();

    /* Test of class PokerFiveCardHand
        * This function tests whether or not PokerFiveCardHand objects of HandType ThreeOfaKind can be accurately compared
          with one another.
    */
    void HandMagnitudeComparison_TOAK();

    /* Test of class PokerFiveCardHand
        * This function tests whether or not PokerFiveCardHand objects of HandType Straight can be accurately compared
          with one another.
    */
    void HandMagnitudeComparison_Straight();

    /* Test of class PokerFiveCardHand
        * This function tests whether or not PokerFiveCardHand objects of HandType Flush can be accurately compared
          with one another.
    */
    void HandMagnitudeComparison_Flush();

    /* Test of class PokerFiveCardHand
        * This function tests whether or not PokerFiveCardHand objects of HandType FullHouse can be accurately compared
          with one another.
    */
    void HandMagnitudeComparison_FullHouse();

    /* Test of class PokerFiveCardHand
        * This function tests whether or not PokerFiveCardHand objects of HandType Quads can be accurately compared
          with one another.
    */
    void HandMagnitudeComparison_Quads();

    /* Test of class PokerFiveCardHand
        * This function tests whether or not PokerFiveCardHand objects of HandType StraightFlush can be accurately compared
          with one another.
    */
    void HandMagnitudeComparison_StraightFlush();

    /* Test of class PokerCards
        * This function tests whether or not PokerCards objects can identify the highest 5-straight when the given
          cards form a 6 or 7-straight.
    */
    void IdentifyHighestStraight();

    /* Test of class PokerCards
        * This function tests whether or not PokerCards objects can identify a straight-flush.
    */
    void IdentifyStraightFlush();
}
