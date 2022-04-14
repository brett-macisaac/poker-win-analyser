
#include"PokerCard.h"

PokerCard::PokerCard(int a_value /* = 2 */, Suit a_suit /* = Suit::Heart */, bool a_is_community_card /* = true */, 
                     bool a_is_face_up /* = true */)
    : f_value(a_value), f_suit(a_suit), f_is_community_card(a_is_community_card), f_is_face_up(a_is_face_up)
{ }

PokerCard::PokerCard(const PokerCard& a_card)
    : f_value(a_card.f_value), f_suit(a_card.f_suit), f_is_community_card(a_card.f_is_community_card),
      f_is_face_up(a_card.f_is_face_up)

{
}

PokerCard::PokerCard(const std::string& a_card, bool a_is_community_card /* = false */, bool a_is_face_up /* = true */)
    : f_is_community_card(a_is_community_card), f_is_face_up(a_is_face_up)
{
    SetFromString(a_card);
}

void PokerCard::SwapValuesWith(PokerCard& a_card)
{
    std::swap(f_value, a_card.f_value);
    std::swap(f_suit, a_card.f_suit);
    //std::swap(f_is_community_card, a_card.f_is_community_card);
}

std::string PokerCard::ToString() const
{
    std::string l_string = "|";
    if (f_is_face_up)
    {
        l_string += PokerCard::IntToCardVal(f_value);
        l_string += PokerCard::SuitToChar(f_suit);
    }
    else
    {
        l_string += S_CHAR_CARD_BACK_VALUE;
        l_string += S_CHAR_CARD_BACK_SUIT;
    }
    l_string += "|";

    return l_string;
}

void PokerCard::SetFromString(const std::string& a_string)
{
    // The format is assumed to be Ab, where A is the value and b is the suit.

    // Validate the string; if it's invalid in some way, return.
    if (a_string.length() != 2)
    {
        return;
    }
    else if ( a_string[0] < '2' || (a_string[0] > '9' && 
              (a_string[0] != 'T' && a_string[0] != 'J' && a_string[0] != 'Q' && a_string[0] != 'K' && a_string[0] != 'A') ) )
    {
        return;
    }
    else if (a_string[1] != 'h' && a_string[1] != 'd' && a_string[1] != 'c' && a_string[1] != 's')
    {
        return;
    }

    // Assign using the conversion functions.
    f_value = PokerCard::CardValToInt(a_string[0]);
    f_suit = PokerCard::CharToSuit(a_string[1]);
}

int PokerCard::GetValue() const
{
    return f_value;
}

Suit PokerCard::GetSuit() const
{
    return f_suit;
}

bool PokerCard::IsSelected() const
{
    return f_is_selected;
}

bool PokerCard::IsCommunityCard() const
{
    return f_is_community_card;
}

bool PokerCard::IsFaceUp() const
{
    return f_is_face_up;
}

void PokerCard::SetCard(int a_value, Suit a_suit)
{
    f_value = a_value;
    f_suit = a_suit;
}

void PokerCard::SetValue(int a_value)
{
    if (a_value > PokerCard::S_MAX_VALUE || a_value < 0)
    { return; }

    f_value = a_value;
}

void PokerCard::SetCommunityFlag(bool a_is_community_card /* = true */)
{
    f_is_community_card = a_is_community_card;
}

void PokerCard::SetSelected(bool a_is_selected)
{
    f_is_selected = a_is_selected;
}

void PokerCard::SetFaceUp(bool a_is_face_up)
{
    f_is_face_up = a_is_face_up;
}

bool PokerCard::operator==(const PokerCard& a_rhs) const
{
    return f_value == a_rhs.f_value && f_suit == a_rhs.f_suit;
}

bool PokerCard::operator!=(const PokerCard& a_rhs) const
{
    return !(*this == a_rhs);
}

bool PokerCard::operator<(const PokerCard& a_rhs) const
{
    if (f_value == a_rhs.GetValue())
    {
        return (int)f_suit < (int)a_rhs.GetSuit();
    }
    else
    {
        return f_value < a_rhs.GetValue();
    }

}

bool PokerCard::operator>(const PokerCard& a_rhs) const
{
    if (f_value == a_rhs.GetValue())
    {
        return (int)f_suit > (int)a_rhs.GetSuit();
    }
    else
    {
        return f_value > a_rhs.GetValue();
    }

}

bool PokerCard::operator>=(const PokerCard& a_rhs) const
{
    return (*this > a_rhs) || (*this == a_rhs);
}

bool PokerCard::operator<=(const PokerCard& a_rhs) const
{
    return (*this < a_rhs) || (*this == a_rhs);
}

/* = (assignment) Operator (l-value)
*/
PokerCard& PokerCard::operator=(const PokerCard& a_card)
{
    f_value = a_card.f_value;
    f_suit = a_card.f_suit;
    f_is_community_card = a_card.f_is_community_card;
    f_is_face_up = a_card.f_is_face_up;

    return *this;
}


std::ostream& operator<<(std::ostream& a_ostream, const PokerCard& a_card)
{
    a_ostream << a_card.ToString();

    return a_ostream;
}

char PokerCard::SuitToChar(Suit a_suit)
{
    if (a_suit == Suit::Heart)
    {
        return 'h';
    }
    else if (a_suit == Suit::Diamond)
    {
        return 'd';
    }
    else if (a_suit == Suit::Club)
    {
        return 'c';
    }
    else
    {
        return 's';
    }

    return '\0';

}

char PokerCard::IntToCardVal(int a_card_val)
{
    if (a_card_val < 10)
    {
        // Return the char version of the int.
        return a_card_val + '0';
    }
    else
    {
        if (a_card_val == 10)
        {
            return 'T';
        }
        else if (a_card_val == 11)
        {
            return 'J';
        }
        else if (a_card_val == 12)
        {
            return 'Q';
        }
        else if (a_card_val == 13)
        {
            return 'K';
        }
        else if (a_card_val == 14)
        {
            return 'A';
        }

    }

}

Suit PokerCard::CharToSuit(char a_char)
{
    switch (a_char)
    {
        case 'h':
            return Suit::Heart;
        case 'd':
            return Suit::Diamond;
        case 'c':
            return Suit::Club;
        case 's':
            return Suit::Spade;
        default:
            return Suit::Heart;
    }

}

int PokerCard::CardValToInt(char a_char)
{
    if (a_char <= '9')
    {
        return a_char - '0';
    }
    else
    {
        if (a_char == 'T')
        {
            return 10;
        }
        else if (a_char == 'J')
        {
            return 11;
        }
        else if (a_char == 'Q')
        {
            return 12;
        }
        else if (a_char == 'K')
        {
            return 13;
        }
        else if (a_char == 'A')
        {
            return 14;
        }

    }

    return -1;
}

bool PokerCard::Comparator_Ascending_Value(const PokerCard& a_lhs, const PokerCard& a_rhs)
{
    return a_lhs.GetValue() < a_rhs.GetValue();
}

bool PokerCard::Comparator_Descending_Value(const PokerCard& a_lhs, const PokerCard& a_rhs)
{
    return a_lhs.GetValue() > a_rhs.GetValue();
}