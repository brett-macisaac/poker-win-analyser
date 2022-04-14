
#include"HandValue.h"
#include"PokerCards.h"

HandValue::HandValue()
    : f_hand_type(HandType::HighCard), f_suit(Suit::Heart)
{
    Unset();
}

HandValue::HandValue(PokerCards& a_cards, bool a_select_cards /* = false */)
    : f_suit(Suit::Heart)
{
    Unset();
    Set(a_cards);
}

HandValue::HandValue(const HandValue& a_hand)
    : f_hand_type(a_hand.f_hand_type), f_suit(Suit::Heart)
{
    for (int i : a_hand.f_hand_magnitude)
    {
        f_hand_magnitude.push_back(i);
    }

}



void HandValue::Set(PokerCards& a_cards, bool a_select_cards /* = false */)
{
    int l_num_cards = a_cards.GetSize();

    if (l_num_cards == 0)
    { return; }

    const int l_num_of_values = PokerCard::S_MAX_VALUE - PokerCard::S_MIN_VALUE + 1; // 13.

    // A tally of each card value.
    int l_value_tallies[l_num_of_values + 2] = { 0 }; // + 2 so that it's 0 to 14 (makes things easier).
    a_cards.SetValueTallies(l_value_tallies, false);

    int l_num_quads = a_cards.NumOfNples(4);

    int l_num_trips = a_cards.NumOfNples(3);

    int l_num_pairs = a_cards.NumOfNples(2);

    // The number of values in a_cards. This is useful to calculate because if it's below 5 then flushes/straights/straight-flushes aren't possible.
    int l_num_values = l_num_quads + l_num_trips + l_num_pairs + (a_cards.GetSize() - (4 * l_num_quads + 3 * l_num_trips + 2 * l_num_pairs));

    bool l_is_full_house = l_num_trips >= 2 || (l_num_trips == 1 && l_num_pairs != 0);

    // Set the hand type.
    if (l_num_values < 5)
    {
        if (l_num_quads != 0)
        {
            SetHandType(HandType::Quads, l_num_cards);
        }
        else if (l_is_full_house)
        {
            SetHandType(HandType::FullHouse, l_num_cards);
        }
        else if (l_num_trips == 1)
        {
            SetHandType(HandType::ThreeOfAKind, l_num_cards);
        }
        else if (l_num_pairs >= 2)
        {
            SetHandType(HandType::TwoPair, l_num_cards);
        }
        else
        {
            SetHandType(HandType::OnePair, l_num_cards);
        }

    }
    else
    {
        bool l_is_flush = a_cards.GetHighestAmountOfSuits() >= 5;

        if (l_is_flush)
        {
            int l_straight_flush = a_cards.IsNstraightFlush(5, &f_suit);

            bool l_is_straight_flush = l_straight_flush != -1;

            if (l_is_straight_flush)
            {
                SetHandType(HandType::StraightFlush, l_num_cards);
                f_hand_magnitude[0] = l_straight_flush;

                return;
            }

        }

        // A variable for the value of the (potential) straight.
        int l_straight = -1;

        // There's no point checking for a straight if a higher hand has already been identified.
        if (l_num_quads == 0 && !l_is_flush && !l_is_full_house)
        {
            l_straight = a_cards.IsNstraight(5);
        }

        bool l_is_straight = l_straight != -1;

        if (l_num_quads != 0)
        {
            SetHandType(HandType::Quads, l_num_cards);
        }
        else if (l_is_full_house)
        {
            SetHandType(HandType::FullHouse, l_num_cards);
        }
        else if (l_is_flush)
        {
            /* Problems
                * If there's 10 or more cards, there could be more than one flush.
            */

            SetHandType(HandType::Flush, l_num_cards);
        }
        else if (l_is_straight)
        {
            SetHandType(HandType::Straight, l_num_cards);
            f_hand_magnitude[0] = l_straight;
        }
        else if (l_num_trips == 1)
        {
            SetHandType(HandType::ThreeOfAKind, l_num_cards);
        }
        else if (l_num_pairs >= 2)
        {
            SetHandType(HandType::TwoPair, l_num_cards);
        }
        else if (l_num_pairs == 1)
        {
            SetHandType(HandType::OnePair, l_num_cards);
        }
        else // hand must be high-card.
        {
            SetHandType(HandType::HighCard, l_num_cards);
        }

    }

    // Set the hand's magnitude.
    SetMagnitude(a_cards, l_value_tallies);

    if (a_select_cards)
    {
        SelectCards(a_cards);
    }
}

HandType HandValue::GetHandType() const
{
    return f_hand_type;
}

const std::vector<int>& HandValue::GetHandMagnitude() const
{
    return f_hand_magnitude;
}

std::string HandValue::ToString() const
{
    std::stringstream l_ss;
    l_ss << HandValue::HandTypeToString(f_hand_type);
    l_ss << " of magnitude ";
    l_ss << Utils::IntVectorToString(f_hand_magnitude);

    std::string l_str = l_ss.str();

    return l_str;
}

bool HandValue::IsSet() const
{
    return f_hand_magnitude[0] != 0;
}

void HandValue::Unset()
{
    // Given that a hand-magnitude value of 0 is impossible, this is a good value to use to indicate the hand not yet being set.
    if (f_hand_magnitude.size() == 0)
    {
        f_hand_magnitude.push_back(0);
    }
    else
    {
        f_hand_magnitude[0] = 0;
    }

}



bool HandValue::operator==(const HandValue& a_hand) const
{
    bool l_is_type_equal = f_hand_type == a_hand.f_hand_type;

    if (!l_is_type_equal)
    {
        return false;
    }

    for (int i = 0; i < f_hand_magnitude.size(); ++i)
    {
        if (f_hand_magnitude[i] != a_hand.f_hand_magnitude[i])
        {
            return false;
        }

    }

    return true;
}

bool HandValue::operator!=(const HandValue& a_hand) const
{
    return !(*this == a_hand);
}

bool HandValue::operator<(const HandValue& a_hand) const
{
    // Compare the hands' types.
    if (f_hand_type < a_hand.f_hand_type)
    {
        return true;
    }
    else if (f_hand_type > a_hand.f_hand_type)
    {
        return false;
    }

    // The hands are of the same type.

    // Compare the hands' magnitudes.
    for (int i = 0; i < f_hand_magnitude.size(); ++i)
    {
        if (f_hand_magnitude[i] < a_hand.f_hand_magnitude[i])
        {
            return true;
        }
        else if (f_hand_magnitude[i] > a_hand.f_hand_magnitude[i])
        {
            return false;
        }

    }

    // The hands are identical; therefore, *this is not less than a_hand.
    return false;
}

bool HandValue::operator>(const HandValue& a_hand) const
{
    // Compare the hands' types.
    if (f_hand_type > a_hand.f_hand_type)
    {
        return true;
    }
    else if (f_hand_type < a_hand.f_hand_type)
    {
        return false;
    }

    // The hands are of the same type.

    // Compare the hands' magnitudes.
    for (int i = 0; i < f_hand_magnitude.size(); ++i)
    {
        if (f_hand_magnitude[i] > a_hand.f_hand_magnitude[i])
        {
            return true;
        }
        else if (f_hand_magnitude[i] < a_hand.f_hand_magnitude[i])
        {
            return false;
        }

    }

    // The hands are identical; therefore, *this is not greater than a_hand.
    return false;
}

bool HandValue::operator>=(const HandValue& a_hand) const
{
    return (*this == a_hand) || (*this > a_hand);
}

bool HandValue::operator<=(const HandValue& a_hand) const
{
    return (*this == a_hand) || (*this < a_hand);
}

HandValue& HandValue::operator=(const HandValue& a_hand)
{
    f_hand_type = a_hand.f_hand_type;

    f_hand_magnitude.resize(a_hand.f_hand_magnitude.size());

    for (int i = 0; i < a_hand.f_hand_magnitude.size(); ++i)
    {
        f_hand_magnitude[i] = a_hand.f_hand_magnitude[i];
    }

    f_suit = a_hand.f_suit;

    return *this;
}



/* Auxiliary of SetHand
*/
void HandValue::SetMagnitude(PokerCards& a_cards, int* a_value_tallies)
{
    if (f_hand_type == HandType::StraightFlush || f_hand_type == HandType::Straight)
    { return; }

    if (f_hand_type == HandType::HighCard)
    {
        // Sort the cards (descending order).
        a_cards.Sort(false);

        for (int i = 0; i < f_hand_magnitude.size(); ++i)
        {
            f_hand_magnitude[i] = a_cards[i].GetValue();
        }

    }
    else if (f_hand_type == HandType::OnePair)
    {
        std::vector<int> l_kickers;

        for (int i = PokerCard::S_MIN_VALUE; i <= PokerCard::S_MAX_VALUE; ++i)
        {
            if (a_value_tallies[i] == 2) // If i is the value of the TOAK.
            {
                f_hand_magnitude[0] = i;
            }
            else if (a_value_tallies[i] == 1) // If i is a kicker.
            {
                l_kickers.push_back(i);
            }

        }

        // Sort the kickers in ascending order.
        std::stable_sort(l_kickers.begin(), l_kickers.end());

        for (int i = 1; i < f_hand_magnitude.size(); ++i)
        {
            f_hand_magnitude[i] = l_kickers[l_kickers.size() - i];
        }

    }
    else if (f_hand_type == HandType::TwoPair)
    {
        std::vector<int> l_kickers;
        std::vector<int> l_pairs;

        for (int i = PokerCard::S_MIN_VALUE; i <= PokerCard::S_MAX_VALUE; ++i)
        {
            if (a_value_tallies[i] == 2)
            {
                l_pairs.push_back(i);
            }
            else if (a_value_tallies[i] == 1) // If i is a kicker.
            {
                l_kickers.push_back(i);
            }

        }

        // Sort the pairs in ascending order.
        std::stable_sort(l_pairs.begin(), l_pairs.end());

        f_hand_magnitude[0] = l_pairs[l_pairs.size() - 1];
        f_hand_magnitude[1] = l_pairs[l_pairs.size() - 2];

        // If there's three pairs, a card from the third lowest pair might be the highest kicker.
        if (l_pairs.size() >= 3)
        {
            l_kickers.push_back(l_pairs[l_pairs.size() - 3]);
        }

        // Sort the kickers in ascending order.
        std::stable_sort(l_kickers.begin(), l_kickers.end());

        if (l_kickers.size() != 0)
        {
            f_hand_magnitude[2] = l_kickers.back();
        }

    }
    else if (f_hand_type == HandType::ThreeOfAKind)
    {
        std::vector<int> l_kickers;

        for (int i = PokerCard::S_MIN_VALUE; i <= PokerCard::S_MAX_VALUE; ++i)
        {
            if (a_value_tallies[i] == 3) // If i is the value of the TOAK.
            {
                f_hand_magnitude[0] = i;
            }
            else if (a_value_tallies[i] == 1) // If i is a kicker.
            {
                l_kickers.push_back(i);
            }

        }

        // Sort the kickers in ascending order.
        std::stable_sort(l_kickers.begin(), l_kickers.end());

        for (int i = 1; i < f_hand_magnitude.size(); ++i)
        {
            f_hand_magnitude[i] = l_kickers[l_kickers.size() - i];
        }

    }
    else if (f_hand_type == HandType::Flush)
    {
        // Sort the cards (descending order).
        a_cards.Sort(false);

        std::vector<int> l_flush_magnitude(f_hand_magnitude.size());

        // Record the highest flush.
        for (int l_suit_int = 0; l_suit_int < PokerCard::S_NUM_OF_SUITS; ++l_suit_int) // For each suit.
        {
            Suit l_suit = (Suit)l_suit_int;

            // The number of cards with the suit.
            int l_num_of_suit = a_cards.GetAmountOfSuit(l_suit);

            // If there's less than 5, there can't possible be a flush with them.
            if (l_num_of_suit < 5)
            {
                continue;
            }

            // Set the magnitude (remember, the cards are sorted).
            int l_num_cards_set = 0;
            for (int i = 0; i < a_cards.GetSize(); ++i)
            {
                if (a_cards[i].GetSuit() == l_suit)
                {
                    l_flush_magnitude[l_num_cards_set++] = a_cards[i].GetValue();
                }

                if (l_num_cards_set == 5)
                {
                    break;
                }
            }

            if (l_suit_int == 0) // If on the first suit.
            {
                Utils::CopyVectorAToB<int>(l_flush_magnitude, f_hand_magnitude);
                f_suit = l_suit;
            }
            else
            {
                int l_compare_magnitudes = Utils::CompareVectors<int>(l_flush_magnitude, f_hand_magnitude);

                if (l_compare_magnitudes == 1) // If l_flush_magnitude is greater than f_hand_magnitude.
                {
                    Utils::CopyVectorAToB<int>(l_flush_magnitude, f_hand_magnitude);
                    f_suit = l_suit;
                }
            }

        }

    }
    else if (f_hand_type == HandType::FullHouse)
    {
        std::vector<int> l_trips;
        std::vector<int> l_kickers; // i.e. pairs.

        for (int i = PokerCard::S_MIN_VALUE; i <= PokerCard::S_MAX_VALUE; ++i)
        {
            if (a_value_tallies[i] == 3)
            {
                l_trips.push_back(i);
            }
            else if (a_value_tallies[i] == 2)
            {
                l_kickers.push_back(i);
            }

        }

        // Sort the trips in ascending order.
        std::stable_sort(l_trips.begin(), l_trips.end());

        f_hand_magnitude[0] = l_trips.back();

        // If there's more than one trips, a pair from the second lowest trips might be the highest kicker.
        if (l_trips.size() > 1)
        {
            l_kickers.push_back(l_trips[l_trips.size() - 2]);
        }

        // Sort the pairs/kickers in ascending order.
        std::stable_sort(l_kickers.begin(), l_kickers.end());

        f_hand_magnitude[1] = l_kickers.back();
    }
    else if (f_hand_type == HandType::Quads)
    {
        std::vector<int> l_kickers;
        std::vector<int> l_quads;

        for (int i = PokerCard::S_MIN_VALUE; i <= PokerCard::S_MAX_VALUE; ++i)
        {
            if (a_value_tallies[i] == 4)
            {
                l_quads.push_back(i);
            }
            else if (a_value_tallies[i] > 0)// If i is a kicker.
            {
                l_kickers.push_back(i);
            }

        }

        // Sort the pairs in ascending order.
        std::stable_sort(l_quads.begin(), l_quads.end());

        f_hand_magnitude[0] = l_quads[l_quads.size() - 1];

        // If there's more than one quads, a card from the second lowest quads might be the highest kicker.
        if (l_quads.size() > 1)
        {
            l_kickers.push_back(l_quads[l_quads.size() - 2]);
        }

        // Sort the kickers in ascending order.
        std::stable_sort(l_kickers.begin(), l_kickers.end());

        f_hand_magnitude[1] = l_kickers.back();
    }

}

/* Auxiliary of SetHand
*/
void HandValue::SetHandType(HandType a_type, int a_num_cards)
{
    f_hand_type = a_type;

    SetNumOfMagnitudes(a_num_cards);
}

/* Auxiliary of SetHandType
*/
void HandValue::SetNumOfMagnitudes(int a_num_cards)
{
    int l_num_of_magnitudes = 0;

    if (f_hand_type == HandType::HighCard)
    {
        // Value of the 5 (or less) highest cards in descending order.
        l_num_of_magnitudes = std::min(a_num_cards, S_SIZE_HAND_MAX);
    }
    else if (f_hand_type == HandType::OnePair)
    {
        int l_num_kickers = std::min(a_num_cards, S_SIZE_HAND_MAX) - 2;

        // Value of the pair plus any kickers.
        l_num_of_magnitudes = 1 + l_num_kickers;
    }
    else if (f_hand_type == HandType::TwoPair)
    {
        int l_num_kickers = std::min(a_num_cards, S_SIZE_HAND_MAX) - 4;

        // Value of each pair plus any kickers.
        l_num_of_magnitudes = 2 + l_num_kickers;
    }
    else if (f_hand_type == HandType::ThreeOfAKind)
    {
        int l_num_kickers = std::min(a_num_cards, S_SIZE_HAND_MAX) - 3;

        // Value of the pair plus any kickers.
        l_num_of_magnitudes = 1 + l_num_kickers;
    }
    else if (f_hand_type == HandType::Straight)
    {
        // Value of the highest card in the straight.
        l_num_of_magnitudes = 1;
    }
    else if (f_hand_type == HandType::Flush)
    {
        // Values of the 5 highest cards of a specific suit in descending order.
        l_num_of_magnitudes = 5;
    }
    else if (f_hand_type == HandType::FullHouse)
    {
        // Value of the trips and the value of the pair.
        l_num_of_magnitudes = 2;
    }
    else if (f_hand_type == HandType::Quads)
    {
        int l_num_kickers = std::min(a_num_cards, S_SIZE_HAND_MAX) - 4;

        // Value of each pair plus any kickers.
        l_num_of_magnitudes = 1 + l_num_kickers;
    }
    else if (f_hand_type == HandType::StraightFlush)
    {
        // Value of the highest card in the straight-flush.
        l_num_of_magnitudes = 1;
    }

    f_hand_magnitude.resize(l_num_of_magnitudes);

    // Reset the magnitude to 0;
    for (int& i : f_hand_magnitude)
    { i = 0; }
}

/* Auxiliary of Set
*/
void HandValue::SelectCards(PokerCards& a_cards)
{
    if (a_cards.GetSize() <= S_SIZE_HAND_MAX)
    {
        a_cards.SelectAll();
        return;
    }
    else
    {
        // Make sure that no cards are selected from a prior process.
        a_cards.UnselectAll();
    }

    // The cards for these hands must be set in a different way.
    if (f_hand_type == HandType::Straight || f_hand_type == HandType::StraightFlush)
    {
        // Sort the cards in ascending order.
        a_cards.Sort();

        // The value of the highest card in the straight.
        int l_straight_highest_card = f_hand_magnitude[0];

        // The value of the lowest card in the straight.
        // note: if the highest card is a 5, the lowest card should be set to 2, which is because the 'lowest' card is 
        // an ace, which actually has a value of 14.
        int l_straight_lowest_card = (l_straight_highest_card != 5) ? f_hand_magnitude[0] - 4 : 2;

        // The current card of the straight to find (in other words, the value of the next card to assign to f_cards).
        int l_current_card = l_straight_lowest_card;

        for (PokerCard& p : a_cards)
        {
            if (p.GetValue() != l_current_card)
            {
                continue;
            }

            // If it's a straight-flush, the suit must also be considered.
            if (f_hand_type == HandType::StraightFlush && p.GetSuit() != f_suit)
            {
                continue;
            }

            // The card is the one being searched for; therefore, select it.
            p.SetSelected(true);

            if (l_current_card > l_straight_highest_card)
            {
                // If the highest card is a 5, this means the 'lowest' card is actually an ace (which has a value of 14).
                if (l_straight_highest_card == 5)
                {
                    l_straight_highest_card = 14;
                    l_current_card = 14;
                }
                else
                {
                    break;
                }
            }

        }

        return;
    }

    // This container stores the number of each card value in f_hand_magnitude that are required in f_cards.
    std::vector<int> l_magnitude_quantities(f_hand_magnitude.size());

    // Assign the appropriate values to l_magnitude_quantities.
    if (f_hand_type == HandType::HighCard)
    {
        for (int& i : l_magnitude_quantities)
        {
            i = 1;
        }
    }
    else if (f_hand_type == HandType::OnePair)
    {
        l_magnitude_quantities[0] = 2;

        for (int i = 1; i < l_magnitude_quantities.size(); ++i)
        {
            l_magnitude_quantities[i] = 1;
        }
    }
    else if (f_hand_type == HandType::TwoPair)
    {
        l_magnitude_quantities[0] = 2;
        l_magnitude_quantities[1] = 2;

        if (f_hand_magnitude.size() == 3)
        {
            l_magnitude_quantities[2] = 1;
        }
    }
    else if (f_hand_type == HandType::ThreeOfAKind)
    {
        l_magnitude_quantities[0] = 3;

        for (int i = 1; i < l_magnitude_quantities.size(); ++i)
        {
            l_magnitude_quantities[i] = 1;
        }
    }
    else if (f_hand_type == HandType::Flush)
    {
        for (int& i : l_magnitude_quantities)
        {
            i = 1;
        }
    }
    else if (f_hand_type == HandType::FullHouse)
    {
        l_magnitude_quantities[0] = 3;
        l_magnitude_quantities[1] = 2;
    }
    else if (f_hand_type == HandType::Quads)
    {
        l_magnitude_quantities[0] = 4;

        if (f_hand_magnitude.size() == 2)
        {
            l_magnitude_quantities[1] = 1;
        }
    }

    // Populate f_cards with the appropriate cards from a_cards.
    int l_num_assigned = 0;
    for (PokerCard& c : a_cards)
    {
        // If it's a flush, the suit must match.
        if (f_hand_type == HandType::Flush && f_suit != c.GetSuit())
        {
            continue;
        }

        int l_card_val = c.GetValue();

        // The index of f_hand_magnitude corresponding to l_card_val.
        int l_index_magnitude = -1;

        // Determine l_index_magnitude.
        for (int i = 0; i < f_hand_magnitude.size(); ++i)
        {
            if (f_hand_magnitude[i] == l_card_val)
            {
                l_index_magnitude = i;
                break;
            }

        }

        if (l_index_magnitude == -1) // If the value l_card_val isn't in f_hand_magnitude.
        {
            continue;
        }
        else if (l_magnitude_quantities[l_index_magnitude] == 0) // If all of the required cards of value l_card_val have already been assigned.
        {
            continue;
        }

        c.SetSelected(true);
        --l_magnitude_quantities[l_index_magnitude];

        // If all 5 cards have been assigned.
        if (++l_num_assigned == 5)
        {
            break;
        }

    }

}



const char* HandValue::HandTypeToString(HandType a_type)
{
    switch (a_type)
    {
    case HighCard:
        return "High Card";

    case OnePair:
        return "One Pair";

    case TwoPair:
        return "Two Pair";

    case ThreeOfAKind:
        return "Three of a Kind";

    case Straight:
        return "Straight";

    case Flush:
        return "Flush";

    case FullHouse:
        return "Full House";

    case Quads:
        return "Quads";

    case StraightFlush:
        return "Straight Flush";

    default:
        return "[Unknown HandType]";
    }

}

bool HandValue::Comparator_Ascending(const HandValue& a_rhs, const HandValue& a_lhs)
{
    return a_rhs < a_lhs;
}

bool HandValue::Comparator_Descending(const HandValue& a_rhs, const HandValue& a_lhs)
{
    return a_rhs > a_lhs;
}
