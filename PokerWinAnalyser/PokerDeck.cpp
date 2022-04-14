
#include"PokerDeck.h"

PokerDeck::PokerDeck() 
    : PokerCards(0)
{
    // Populate the deck with all 52 cards.

    for (int suit = 0; suit < PokerCard::S_NUM_OF_SUITS; ++suit)
    {
        for (int value = PokerCard::S_MIN_VALUE; value <= PokerCard::S_MAX_VALUE; ++value)
        {
            f_cards.push_back(PokerCard(value, (Suit)suit));
        }

    }

}