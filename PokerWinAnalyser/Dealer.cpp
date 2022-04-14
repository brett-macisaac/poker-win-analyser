
#include"Dealer.h"

// Default 'dealing mode' is texas hold'em
Dealer::Dealer()
    : f_index_deck(0)
{
}

void Dealer::Shuffle()
{
    f_deck.Shuffle();

    f_index_deck = 0;
}

/* Deal Method
    
    * Notes:
*/
void Dealer::DealToPlayers(std::vector<PokerCards>& a_player_hands, int a_small_blind, int a_cards_per_player /* = -1 */, 
                           bool a_remove_from_deck /* = false */)
{   
    // Determine the number of cards to deal. This is used both to validate before dealing and to determine when to stop dealing.
    int l_num_cards_to_deal = 0;
    if (a_cards_per_player != -1)
    {
        l_num_cards_to_deal = a_player_hands.size() * a_cards_per_player;
    }
    else
    {
        // If the caller didn't specify an amount of cards to deal, then each player will receive a number of cards
        // equal to their hands' size.
        for (PokerCards h : a_player_hands)
        {
            l_num_cards_to_deal += h.GetSize();
        }

    }

    // Guard to avoid trying to deal more cards than the (remaining) deck's size.
    if (l_num_cards_to_deal > NumRemainingCards())
    { 
        // return; 
        throw std::runtime_error("There aren't enough cards left in the deck to deal this many.");
    }

    if (a_cards_per_player != -1)
    {
        for (PokerCards h : a_player_hands)
        {
            if (h.GetSize() < a_cards_per_player)
            {
                throw std::runtime_error("This player doesn't have enough cards (container is too small to be dealt to).");
            }

        }

    }

    // The index of players' hands at which the next card is dealt.
    int l_index_hands = 0;

    // The number of cards dealt; this is used to determine when to stop dealing.
    int l_num_cards_dealt = 0;

    // The player who will receive the next card.
    int l_index_recipient = a_small_blind;

    while (1) // Each iteration represents all (or some) of the players being dealt their l_index_hands^th card (ith card).
    {

        // Deal each player their next card.
        do
        {
            if (a_player_hands[l_index_recipient].GetSize() - 1 >= l_index_hands) // If there's enough room in the player's hand.
            {
                a_player_hands[l_index_recipient][l_index_hands] = f_deck[f_index_deck++];
                ++l_num_cards_dealt;
            }

            // Go to the next index/player.
            l_index_recipient = (l_index_recipient + 1) % a_player_hands.size();

        } while (l_index_recipient != a_small_blind); // If this condition is false (dealing to small-blind again) this means all player's have been dealt their card.

        // Got to the next hand index.
        ++l_index_hands;

        // If all cards have been dealt, break (i.e. stop dealing).
        if (l_num_cards_dealt == l_num_cards_to_deal)
        {
            break;
        }

    }

    if (a_remove_from_deck)
    {
        // Remove the cards from the deck.
        for (PokerCards& p : a_player_hands)
        {
            f_deck.RemoveCards(p);
        }

    }


    // This is the old version that doesn't take into account a lot of the new additions (isn't flexible)
    // Deal players' cards. If implemented in a game would have to adjust for the position of the SB, which of course isn't always at index 0.

    //for (int card_index = 0; card_index < f_cards_per_player; ++card_index) // for each card to deal (1st, 2nd, 3rd ...)
    //{
    //    for (int hand_index = 0; hand_index < a_player_hands.size(); ++hand_index) // for each player's hand.
    //    {
    //        a_player_hands[hand_index][card_index] = f_deck[hand_index + a_player_hands.size() * card_index];
    //    }

    //}

}

void Dealer::DealToEntity(PokerCards& a_cards_entity, int a_index_start /* = 0 */, bool a_remove_from_deck /* = false */)
{
    // Guard for when a_index_start isn't within valid bounds.
    if (a_index_start + 1 > a_cards_entity.GetSize())
    { return; }

    // A guard to prevent dealing too many cards.
    if (a_cards_entity.GetSize() - a_index_start > NumRemainingCards())
    { return; }

    // Deal the community cards.
    for (int i = a_index_start; i < a_cards_entity.GetSize(); ++i)
    {
        a_cards_entity[i] = f_deck[f_index_deck++];
    }

    if (a_remove_from_deck)
    {
        for (int i = a_index_start; i < a_cards_entity.GetSize(); ++i)
        {
            f_deck.RemoveCard(a_cards_entity[i]);
        }

    }

}

void Dealer::RetrievePlayersCards(std::vector<PokerCards>& a_player_hands)
{
    // If the deck is already full, don't add the cards (i.e. they were never removed, so don't add them back).
    if (f_deck.GetSize() == PokerDeck::S_NUM_CARDS_FULL_DECK)
    {
        return;
    }

    for (PokerCards& p : a_player_hands)
    {
        f_deck.AddCards(p);
    }

}

void Dealer::RetrievePlayerCards(PokerCards& a_player_hand)
{
    // If the deck is already full, don't add the cards (i.e. they were never removed, so don't add them back).
    if (f_deck.GetSize() == PokerDeck::S_NUM_CARDS_FULL_DECK)
    {
        return;
    }

    f_deck.AddCards(a_player_hand);
}

const PokerCard& Dealer::GetNextCard()
{
    return f_deck[f_index_deck++];
}

void Dealer::ResetDeckIndex()
{
    f_index_deck = 0;
}

void Dealer::RemoveCardsFromDeck(const PokerCards& a_cards)
{
    for (const PokerCard& p : a_cards)
    {
        f_deck.RemoveCard(p);
    }

}

void Dealer::RemoveCardsFromDeck(std::vector<PokerCards>& a_cards)
{
    // Remove the cards from the deck.
    for (PokerCards& p : a_cards)
    {
        f_deck.RemoveCards(p);
    }
}

PokerDeck& Dealer::GetDeck()
{
    return f_deck;
}

PokerCard& Dealer::operator[](int a_index)
{
    return f_deck[a_index];
}

int Dealer::NumRemainingCards() const
{
    return PokerDeck::S_NUM_CARDS_FULL_DECK - f_index_deck;
}