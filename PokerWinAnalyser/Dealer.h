#pragma once

#include<vector>
#include<stdexcept>

#include"PokerDeck.h"
#include"PokerCards.h"


class Dealer
{

private:

    // The index corresponding to the next card to be dealt.
    int f_index_deck;

    PokerDeck f_deck;


public:

    // Default 'dealing mode' is texas hold'em
    Dealer();

    void Shuffle();

    void DealToPlayers(std::vector<PokerCards>& a_player_hands, int a_small_blind, int a_cards_per_player = -1, 
                       bool a_remove_from_deck = false);

    void DealToEntity(PokerCards& a_cards_entity, int a_index_start = 0, bool a_remove_from_deck = false);

    void RetrievePlayersCards(std::vector<PokerCards>& a_player_hands);

    void RetrievePlayerCards(PokerCards& a_player_hand);

    const PokerCard& GetNextCard();

    void ResetDeckIndex();

    void RemoveCardsFromDeck(const PokerCards& a_cards);

    void RemoveCardsFromDeck(std::vector<PokerCards>& a_cards);

    PokerDeck& GetDeck();

    PokerCard& operator[](int a_index);

private:

    int NumRemainingCards() const;

};
