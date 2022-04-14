
#include"PokerCards.h"


PokerCards::PokerCards(int a_initial_size /* = 0 */, bool a_community_cards /* = false */, bool a_are_face_up /* = true */)
{
    // Add a_initial_size cards to the vector.
    for (int i = 0; i < a_initial_size; ++i)
    {
        f_cards.push_back(PokerCard(14, Suit::Heart, a_community_cards, a_are_face_up));
    }

}

PokerCards::PokerCards(const PokerCards& a_cards)
    : f_value(a_cards.f_value)
{
    for (int i = 0; i < a_cards.GetSize(); ++i)
    {
        f_cards.push_back(const_cast<PokerCards&>(a_cards)[i]);
    }

}

PokerCards::PokerCards(const std::string& a_cards, bool a_set_hand /* = true */, bool a_select_cards /* = true */, 
                       bool a_community_cards /* = false */, bool a_are_face_up /* = true */)
{
    // The format is assumed to be |Ab||Cd||Ef||Gh||Ij|, where upper-case letters are the values and the lower-case letters are the suits.

    // The number of letters is the number of cards multiplied by 4 (suit + value + two pipes)
    int l_num_cards = a_cards.length() / 4;

    for (int i = 0; i < l_num_cards; ++i)
    {
        // The index of the value of the ith card.
        int l_index_ith_value = 4 * i + 1;

        std::string l_ith_card = a_cards.substr(l_index_ith_value, 2);

        f_cards.push_back(PokerCard(l_ith_card, a_community_cards, a_are_face_up));
    }

    if (a_set_hand)
    {
        SetValue(a_select_cards);
    }

}

bool PokerCards::s_display_hand_value = false;



void PokerCards::Sort(bool a_ascending /* = true */)
{
    std::stable_sort(f_cards.begin(), f_cards.end(), a_ascending ? PokerCard::Comparator_Ascending_Value : PokerCard::Comparator_Descending_Value);
}

void PokerCards::Shuffle()
{
    int l_random_card = 0;

    for (int i = 0; i < f_cards.size(); ++i)
    {
        // Get random number between 0 (min index) and f_cards.size() - 1 (max index).
        l_random_card = Utils::GetRandomBetween(0, f_cards.size() - 1);

        // 'Swap' cards at indexes i and l_random_num.
        f_cards[i].SwapValuesWith(f_cards[l_random_card]);
    }

}

std::string PokerCards::ToString() const
{
    std::stringstream l_ss;

    bool l_is_set = f_value.IsSet();

    for (const PokerCard& c : f_cards)
    {
        if (l_is_set)
        {
            if (c.IsSelected())
            {
                l_ss << c.ToString();
            }
        }
        else
        {
            l_ss << c.ToString();
        }
    }

    if (s_display_hand_value && l_is_set)
    { l_ss << ": " << f_value.ToString(); }

    std::string l_str = l_ss.str();

    return l_str;
}

void PokerCards::RemoveCard(const PokerCard& a_card)
{
    for (int i = 0; i < f_cards.size(); ++i)
    {
        if (f_cards[i] == a_card)
        {
            f_cards.erase(f_cards.begin() + i);
            return;
        }
    }

    f_value.Unset();
}

void PokerCards::RemoveCards(const PokerCards& a_cards)
{
    for (const PokerCard& p : a_cards)
    {
        RemoveCard(p);
    }

    f_value.Unset();
}

void PokerCards::AddCard(const PokerCard& a_card)
{
    f_cards.push_back(a_card);

    f_value.Unset();
}

void PokerCards::AddCards(PokerCards& a_cards)
{
    for (int i = 0; i < a_cards.GetSize(); ++i)
    {
        AddCard(const_cast<PokerCards&>(a_cards)[i]);
    }

    f_value.Unset();
}

void PokerCards::CopyCard(const PokerCard& a_card, int a_index /* = 0 */)
{
    if (a_index < 0 || a_index > f_cards.size() - 1)
    { return; }

    f_cards[a_index] = a_card;

    f_value.Unset();
}

void PokerCards::CopyCards(PokerCards& a_cards, int a_index /* = 0 */)
{
    if (a_index < 0)
    { return; }

    // The index of the element to copy.
    int a_index_cards = 0;

    for (int i = a_index; i < f_cards.size() && a_index_cards < a_cards.GetSize(); ++i)
    {
        f_cards[i] = a_cards[a_index_cards++];
    }

    f_value.Unset();
}

/*
    * This method sets the non-community cards of f_cards equal to those of a_cards.
*/
void PokerCards::CopyCards_NonCommunity(PokerCards& a_cards)
{
    int a_num_set = 0;
    for (PokerCard& c : f_cards)
    {
        if (a_num_set == a_cards.GetSize())
        { break; }

        if (!c.IsCommunityCard())
        { c = a_cards[a_num_set++]; }
    }

    f_value.Unset();
}

void PokerCards::ReSize(int a_new_size)
{
    f_cards.resize(a_new_size);
    f_value.Unset();
}

PokerCard& PokerCards::GetTopCard()
{
    return f_cards.back();
    f_value.Unset();
}

int PokerCards::GetSize() const
{
    return f_cards.size();
}

// e.g. Get number of aces.
int PokerCards::GetAmountOfValue(int a_value) const
{
    int a_num = 0;

    for (int i = 0; i < f_cards.size(); ++i)
    {
        if (f_cards[i].GetValue() == a_value)
        {
            ++a_num;
        }

    }

    return a_num;
}

int PokerCards::GetAmountOfSuit(Suit a_suit) const
{
    int a_amount = 0;

    for (int i = 0; i < f_cards.size(); ++i)
    {
        if (f_cards[i].GetSuit() == a_suit)
        {
            ++a_amount;
        }

    }

    return a_amount;
}

int PokerCards::NumOfNples(int a_N) const
{
    int l_num_of_nples = 0;

    for (int l_value = PokerCard::S_MIN_VALUE; l_value <= PokerCard::S_MAX_VALUE; ++l_value) // For each possible card value.
    {
        if (GetAmountOfValue(l_value) == a_N) // If there are a_N cards of value l_value.
        {
            ++l_num_of_nples;
        }

    }

    return l_num_of_nples;
}

int PokerCards::IsNstraight(int a_n /* = 5 */) const
{
    // Return -1 immediately if there aren't enough cards to make the straight.
    if (f_cards.size() < a_n)
    { return -1; }

    // Sort the cards in ascending order of value.
    //Sort();

    // Get the values of the cards (exclude any duplicate values).
    std::vector<int> l_card_values;
    for (int i = 0; i < f_cards.size(); ++i)
    {
        // Prevent duplicates from being entered, which stuffs up the algorithm.
        if (i != 0 && Utils::IsValInVector(f_cards[i].GetValue(), l_card_values))
        {
            continue;
        }

        l_card_values.push_back(f_cards[i].GetValue());
    }

    if (l_card_values.size() < a_n)
    { return -1; }

    // Sort the values in ascending order.
    std::stable_sort(l_card_values.begin(), l_card_values.end());

    // The algorithm should return the value of the highest N-straight.
    int l_highest_straight = -1;

    // The first iteration treats aces as 14s, while the second one treats them as 1s.
    for (int i = 0; i < 2; ++i)
    {
        if (i == 1) // if on the second iteration.
        {
            if (l_card_values.back() != PokerCard::S_MAX_VALUE || 
                l_highest_straight != -1) // If the highest card isn't an ace or a straight was already found (which is guaranteed to be higher than any straight when considering an ace to be 1).
            {
                break;
            }

            // Change the 14 to a 1.
            l_card_values[l_card_values.size() - 1] = 1;

            // Sort the values in ascending order.
            std::stable_sort(l_card_values.begin(), l_card_values.end());
        }

        // Search for a sequence of a_n consecutive numbers in l_card_values.
        int l_max_index;
        for (int l_min_index = 0; l_min_index < l_card_values.size(); ++l_min_index)
        {
            l_max_index = l_min_index + a_n - 1; // e.g. 0 to 4 for checking for a five straight (when l_min_index is 0)

            if (l_max_index >= l_card_values.size()) // If max index to check is greater than the highest valid index.
            {
                break;
            }

            // Iterate over the segment of l_card_values (l_min_index to l_max_index) to check for an a_n straight.
            for (int j = l_min_index; j < l_max_index; ++j)
            {
                if (l_card_values[j] + 1 != l_card_values[j + 1]) // If current and next values aren't consecutive
                {
                    break;
                }
                else if (j == l_max_index - 1) // if on last iteration; therefore, there is an n-straight.
                {
                    l_highest_straight = l_card_values[l_max_index];
                    //return l_card_values[l_max_index];
                }

            }

        }

    }

    return l_highest_straight;
}

/* Accessor/Mutator of f_cards
*/
int PokerCards::IsNstraightFlush(int a_n /* = 5 */, Suit* a_suit /* = nullptr */) const
{
    // Return -1 immediately if there aren't enough cards to make the straight.
    if (f_cards.size() < a_n)
    { return -1; }

    // Container to store the cards of each suit.
    std::vector<PokerCards> l_cards_hdcs(4);

    for (const PokerCard& p : f_cards)
    {
        l_cards_hdcs[(int)p.GetSuit()].AddCard(p);
    }

    // Sort the cards in ascending order.
    for (PokerCards& ps : l_cards_hdcs)
    { ps.Sort(); }

    // The size of the highest straight-flush corresponding to f_cards.
    int l_size_highest_straight_flush = -1;

    for (int l_suit_int = 0; l_suit_int < PokerCard::S_NUM_OF_SUITS; ++l_suit_int)
    {
        Suit l_suit = (Suit)l_suit_int;

        PokerCards& l_cards_curr_suit = l_cards_hdcs[l_suit];

        // If there's not at least 5 cards, there cannot be a flush.
        if (l_cards_curr_suit.GetSize() < 5)
        { continue; }

        // The size of the highest straight-flush corresponding to l_cards_curr_suit.
        int l_size_straight_flush = -1;

        // The first iteration treats aces as 14s, while the second one treats them as 1s.
        for (int i = 0; i < 2; ++i)
        {
            if (i == 1) // if on the second iteration.
            {
                bool l_is_top_card_an_ace = l_cards_curr_suit.GetTopCard().GetValue() == PokerCard::S_MAX_VALUE;

                bool l_has_str_flush_been_found = l_size_straight_flush != -1;

                // If the highest card isn't an ace or a straight was already found (which is guaranteed to be higher than any straight when considering an ace to be 1).
                if (!l_is_top_card_an_ace || l_has_str_flush_been_found)
                {
                    break;
                }

                // Change the 14 to a 1.
                l_cards_curr_suit.GetTopCard().SetValue(1);

                // Sort the values in ascending order.
                l_cards_curr_suit.Sort();
            }

            // Search for a sequence of a_n consecutive numbers in l_card_values.
            int l_max_index;
            for (int l_min_index = 0; l_min_index < l_cards_curr_suit.GetSize(); ++l_min_index)
            {
                l_max_index = l_min_index + a_n - 1; // e.g. 0 to 4 for checking for a five straight (when l_min_index is 0)

                if (l_max_index >= l_cards_curr_suit.GetSize()) // If max index to check is greater than the highest valid index.
                {
                    break;
                }

                // Iterate over the segment of l_card_values (l_min_index to l_max_index) to check for an a_n straight.
                for (int j = l_min_index; j < l_max_index; ++j)
                {
                    if (l_cards_curr_suit[j].GetSuit() != l_cards_curr_suit[j + 1].GetSuit()) // If the suits of the consecutive cards aren't the same.
                    {
                        break;
                    }
                    else if (l_cards_curr_suit[j].GetValue() + 1 != l_cards_curr_suit[j + 1].GetValue()) // If the values of the consecutive cards aren't consecutive.
                    {
                        break;
                    }
                    else if (j == l_max_index - 1) // if on the last iteration; therefore, there is an n-straight.
                    {
                        l_size_straight_flush = l_cards_curr_suit[l_max_index].GetValue();
                    }

                }

            }

        }

        // If the straight-flush corresponding to l_suit is higher than any previous one.
        if (l_size_straight_flush > l_size_highest_straight_flush)
        {
            // Assign both the straight-flush's size and its suit.
            l_size_highest_straight_flush = l_size_straight_flush;
            *a_suit = l_suit;
        }

    }

    return l_size_highest_straight_flush;
}

bool PokerCards::IsDoubleBarrelStrDr(int a_size_straight /* = 5 */) const
{
    // Return -1 immediately if there aren't enough cards to make the straight-draw (must be at least 5 cards).
    if (f_cards.size() < a_size_straight)
    { return -1; }

    // Sort the cards in ascending order of value.
    //Sort();

    // Get the values of the cards (exclude any duplicate values).
    std::vector<int> l_card_values;
    for (int i = 0; i < f_cards.size(); ++i)
    {
        // Prevent duplicates from being entered, which stuffs up the algorithm.
        if (i != 0 && Utils::IsValInVector(f_cards[i].GetValue(), l_card_values))
        {
            continue;
        }

        l_card_values.push_back(f_cards[i].GetValue());
    }

    if (l_card_values.size() < a_size_straight)
    { return false; }

    // Sort the values in ascending order.
    std::stable_sort(l_card_values.begin(), l_card_values.end());

    // The first iteration treats aces as 14s, while the second one treats them as 1s.
    for (int i = 0; i < 2; ++i)
    {
        if (i == 1) // if on the second iteration.
        {
            if (l_card_values.back() != PokerCard::S_MAX_VALUE) // If the highest card isn't an ace.
            {
                break;
            }

            // Change the 14 to a 1.
            l_card_values[l_card_values.size() - 1] = 1;

            // Sort the values in ascending order.
            std::stable_sort(l_card_values.begin(), l_card_values.end());
        }

        // Search for a double-barrel gut-shot in l_card_values.
        int l_max_index;
        for (int l_min_index = 0; l_min_index < l_card_values.size(); ++l_min_index)
        {
            l_max_index = l_min_index + a_size_straight - 1; // e.g. 0 to 4 when a_size_straight is 5 and l_min_index is 0;

            if (l_max_index >= l_card_values.size()) // If max index to check is greater than the highest valid index.
            {
                break;
            }

            // Iterate over the segment of l_card_values (l_min_index to l_max_index) to check for an a_n straight.
            for (int j = l_min_index; j < l_max_index; ++j)
            {
                if (j == l_min_index)
                {
                    if (l_card_values[j] + 2 != l_card_values[j + 1])
                    {
                        break;
                    }

                }
                else if (j == l_max_index - 1)
                {
                    if (l_card_values[j] + 2 != l_card_values[j + 1])
                    {
                        break;
                    }
                    else
                    {
                        return true;
                    }

                }
                else if (l_card_values[j] + 1 != l_card_values[j + 1])
                {
                    break;
                }

            }

        }

    }

    return false;
}

int PokerCards::GetHighestAmountOfValue() const
{
    int l_amount_highest = 0;

    for (int l_value = PokerCard::S_MIN_VALUE; l_value <= PokerCard::S_MAX_VALUE; ++l_value) // For each possible card value.
    {
        int l_amount_value = GetAmountOfValue(l_value);

        if (l_amount_value > l_amount_highest)
        {
            l_amount_highest = l_amount_value;
        }

    }

    return l_amount_highest;
}

int PokerCards::GetHighestAmountOfSuits() const
{
    int l_amount_highest = 0;

    for (int l_suit = 0; l_suit < PokerCard::S_NUM_OF_SUITS; ++l_suit) // For each possible card value.
    {
        int l_amount_suit = GetAmountOfSuit((Suit)l_suit);

        if (l_amount_suit > l_amount_highest)
        {
            l_amount_highest = l_amount_suit;
        }

    }

    return l_amount_highest;
}

int PokerCards::GetHighestValue() const
{
    int l_highest_val = 0;

    for (const PokerCard& c : f_cards)
    {
        if (c.GetValue() > l_highest_val)
        {
            l_highest_val = c.GetValue();
        }

    }

    return l_highest_val;
}

/* Accessor of f_value
*/
const HandValue& PokerCards::GetValue() const
{
    return f_value;
}

bool PokerCards::IsPaired() const
{
    if (GetSize() != 2)
    {  return false; }

    return f_cards[0].GetValue() == f_cards[1].GetValue();
}

bool PokerCards::ValueMatch(int a_value) const
{
    for (const PokerCard& c : f_cards)
    {
        if (c.GetValue() == a_value)
        {
            return true;
        }

    }

    return false;
}

void PokerCards::SetValueTallies(int* a_value_tallies, bool a_reset_array /* = true */) const
{
    if (a_reset_array)
    {
        Utils::ResetArray(a_value_tallies, PokerCard::S_MAX_VALUE + 1);
    }

    for (int i = 0; i < f_cards.size(); ++i)
    {
        ++(a_value_tallies[f_cards[i].GetValue()]);
    }

}

/* Mutator of f_value
*/
void PokerCards::SetValue(bool a_select_cards /* = true */)
{
    f_value.Set(*this, a_select_cards);
}

/* Mutator of f_value
    * Sets f_value to a_value.
*/
void PokerCards::SetValue(const HandValue a_value)
{
    f_value = a_value;
}

/* Mutator of f_cards
*/
void PokerCards::SelectAll()
{
    for (PokerCard& p : f_cards)
    {
        p.SetSelected(true);
    }

}

/* Mutator of f_cards
*/
void PokerCards::UnselectAll()
{
    for (PokerCard& p : f_cards)
    {
        p.SetSelected(false);
    }
}

std::vector<PokerCard>::iterator PokerCards::begin()
{
    return f_cards.begin();
}

std::vector<PokerCard>::iterator PokerCards::end()
{
    return f_cards.end();
}

std::vector<PokerCard>::const_iterator PokerCards::begin() const
{
    return f_cards.begin();
}

std::vector<PokerCard>::const_iterator PokerCards::end() const
{
    return f_cards.end();
}



PokerCard& PokerCards::operator[](int a_index)
{
    if (a_index < 0)
    { 
        throw std::runtime_error("a_index cannot be negative."); 
    }

    if (a_index >= GetSize())
    {
        // Either throw an error or increase the size of f_cards.
        // Could be a useful feature to automatically resize: e.g. if switching from Texas Hold'em to Omaha (2-card to 4-card game).
        // Maybe not, just have a resize method that has to be called.
        //f_cards.resize(a_index);
        throw std::runtime_error("a_index is above the maximum for this object.");
    }

    return f_cards[a_index];
}

std::ostream& operator<<(std::ostream& a_ostream, const PokerCards& a_cards)
{
    a_ostream << a_cards.ToString();

    return a_ostream;
}

PokerCards& PokerCards::operator=(const PokerCards& a_rhs)
{
    f_cards.resize(a_rhs.f_cards.size());

    for (int i = 0; i < a_rhs.GetSize(); ++i)
    {
        f_cards[i] = const_cast<PokerCards&>(a_rhs)[i];
    }

    f_value = a_rhs.f_value;

    return *this;
}

bool PokerCards::operator==(const PokerCards& a_lhs) const
{
    if (f_cards.size() != a_lhs.GetSize())
    { return false; }

    for (int i = 0; i < f_cards.size(); ++i)
    {
        if (f_cards[i] != const_cast<PokerCards&>(a_lhs)[i])
        { return false; }
    }

    return true;
}

bool PokerCards::operator!=(const PokerCards& a_lhs) const
{
    return !(*this == a_lhs);
}

bool PokerCards::operator<(const PokerCards& a_lhs) const
{
    return f_value < a_lhs.f_value;
}

bool PokerCards::operator>(const PokerCards& a_lhs) const
{
    return f_value > a_lhs.f_value;
}

bool PokerCards::operator>=(const PokerCards& a_lhs) const
{
    return f_value >= a_lhs.f_value;
}

bool PokerCards::operator<=(const PokerCards& a_lhs) const
{
    return f_value <= a_lhs.f_value;
}



bool PokerCards::Comparator_Value_Ascending(const PokerCards& a_rhs, const PokerCards& a_lhs)
{
    return a_rhs < a_lhs;
}

bool PokerCards::Comparator_Value_Descending(const PokerCards& a_rhs, const PokerCards& a_lhs)
{
    return a_rhs > a_lhs;
}