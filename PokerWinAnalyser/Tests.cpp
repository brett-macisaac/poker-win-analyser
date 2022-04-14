
#include"Tests.h"

namespace Tests
{
    /* Test of class PokerCards/PokerCard
    */
    void SetCardsFromString()
    {
        std::string l_cards_string_1 =  "|7d||6c|";
        std::string l_cards_string_2 = "|Ad||Qc||4d||6c||7d|";

        PokerCards l_cards_1(l_cards_string_1);
        PokerCards l_cards_2(l_cards_string_2);

        std::cout << l_cards_1 << std::endl;
        std::cout << l_cards_2 << std::endl;
    }

    /* Test of class PokerFiveCardHand
    */
    void HandRecognition_From5Cards()
    {
        std::string l_high_card_str = "|7d||6d||As||4h||9h|";
        std::string l_one_pair_str = "|Ad||Ac||4d||6c||7d|";
        std::string l_two_pair_str = "|Ad||Ac||4d||4c||7d|";
        std::string l_toak_str = "|Ad||Ac||Ad||6c||7d|";
        std::string l_straight_str = "|Ad||2c||3d||4c||5d|";
        std::string l_flush_str = "|Ad||2d||Kd||4d||3d|";
        std::string l_full_house_str = "|Ad||Ac||Ad||Kc||Kd|";
        std::string l_quads_str = "|Ad||Ac||Ad||Ac||5d|";
        std::string l_straight_flush_str = "|Ad||2d||3d||4d||5d|";

        std::vector<PokerCards> l_cards;
        l_cards.push_back(PokerCards(l_high_card_str));
        l_cards.push_back(PokerCards(l_one_pair_str));
        l_cards.push_back(PokerCards(l_two_pair_str));
        l_cards.push_back(PokerCards(l_toak_str));
        l_cards.push_back(PokerCards(l_straight_str));
        l_cards.push_back(PokerCards(l_flush_str));
        l_cards.push_back(PokerCards(l_full_house_str));
        l_cards.push_back(PokerCards(l_quads_str));
        l_cards.push_back(PokerCards(l_straight_flush_str));

        for (PokerCards& c : l_cards)
        {
            std::cout << c << std::endl;
        }

    }

    /* Test of class PokerFiveCardHand
    */
    void HandRecognition_From6Cards()
    {
        std::string l_high_card_str = "|7d||6d||As||4h||9h||Qc|";
        std::string l_one_pair_str = "|Ad||Ac||4d||Ks||6c||8d|";
        std::string l_two_pair_str = "|Ad||Ac||Ts||4d||Ks||7d|";
        std::string l_toak_str = "|Ad||Ac||Ad||6c||9d||7d|";
        std::string l_straight_str = "|Ad||2c||6c||3d||4c||5d|";
        std::string l_flush_str = "|Ad||2d||Tc||Kd||4d||3d|";
        std::string l_full_house_str = "|Ad||Ac||4c||As||Kc||Kd|";
        std::string l_quads_str = "|Ad||Ks||Ac||Ah||As||Qs|";
        std::string l_straight_flush_str = "|Kd||2d||3d||6d||4d||5d|";

        std::vector<PokerCards> l_cards;
        l_cards.push_back(PokerCards(l_high_card_str));
        l_cards.push_back(PokerCards(l_one_pair_str));
        l_cards.push_back(PokerCards(l_two_pair_str));
        l_cards.push_back(PokerCards(l_toak_str));
        l_cards.push_back(PokerCards(l_straight_str));
        l_cards.push_back(PokerCards(l_flush_str));
        l_cards.push_back(PokerCards(l_full_house_str));
        l_cards.push_back(PokerCards(l_quads_str));
        l_cards.push_back(PokerCards(l_straight_flush_str));

        for (const PokerCards& c : l_cards)
        {
            std::cout << c << std::endl;
        }

    }

    /* Test of class PokerFiveCardHand
    */
    void HandRecognition_From7Cards()
    {
        std::string l_high_card_str = "|7d||6d||As||4h||9h||Qc||2c|";
        std::string l_one_pair_str = "|Ad||Ac||4d||Ks||6c||7d||8d|";
        std::string l_two_pair_str = "|Ad||Ac||Ts||4d||Ks||4c||7d|";
        std::string l_toak_str = "|Ad||Ac||Ad||6c||9d||7d||Ks|";
        std::string l_straight_str = "|Ad||2c||6c||3d||4c||5d||Kd|";
        std::string l_flush_str = "|Ad||2d||Td||Kd||4d||3d||7c|";
        std::string l_full_house_str = "|Ad||Ac||4c||As||Kc||Kd||7d|";
        std::string l_quads_str = "|Ad||Ks||Ac||Ah||As||5d||Qs|";
        std::string l_straight_flush_str = "|Kd||2d||3d||6d||4d||5d||8c|";

        std::vector<PokerCards> l_cards;
        l_cards.push_back(PokerCards(l_high_card_str));
        l_cards.push_back(PokerCards(l_one_pair_str));
        l_cards.push_back(PokerCards(l_two_pair_str));
        l_cards.push_back(PokerCards(l_toak_str));
        l_cards.push_back(PokerCards(l_straight_str));
        l_cards.push_back(PokerCards(l_flush_str));
        l_cards.push_back(PokerCards(l_full_house_str));
        l_cards.push_back(PokerCards(l_quads_str));
        l_cards.push_back(PokerCards(l_straight_flush_str));

        for (const PokerCards& c : l_cards)
        {
            std::cout << c << std::endl;
        }

    }

    /* Auxiliary of HandTypeComparison and the 'HandMagnitudeComparison_X' functions
    */
    void HandComparison(std::vector<PokerCards>& a_cards)
    {
        // Might noe be needed, as the Combination class will have 0 combinations.
        if (a_cards.size() == 0)
        {
            return;
        }

        Combination l_comparison_combs(a_cards.size(), 2);

        for (const Combination& c : l_comparison_combs)
        {
            if (a_cards[c[0]] > a_cards[c[1]])
            {
                std::cout << a_cards[c[0]] << " > " << a_cards[c[1]] << std::endl;
            }
            else if (a_cards[c[0]] < a_cards[c[1]])
            {
                std::cout << a_cards[c[0]] << " < " << a_cards[c[1]] << std::endl;
            }
            else
            {
                std::cout << a_cards[c[0]] << " == " << a_cards[c[1]] << std::endl;
            }

        }

    }

    /* Test of class PokerFiveCardHand
    */
    void HandTypeComparison()
    {
        std::string l_high_card_str = "|7d||6d||As||4h||9h|";
        std::string l_one_pair_str = "|Ad||Ac||4d||6c||7d|";
        std::string l_two_pair_str = "|Ad||Ac||4d||4c||7d|";
        std::string l_toak_str = "|Ad||Ac||Ad||6c||7d|";
        std::string l_straight_str = "|Ad||2c||3d||4c||5d|";
        std::string l_flush_str = "|Ad||2d||Kd||4d||3d|";
        std::string l_full_house_str = "|Ad||Ac||Ad||Kc||Kd|";
        std::string l_quads_str = "|Ad||Ac||Ad||Ac||5d|";
        std::string l_straight_flush_str = "|Ad||2d||3d||4d||5d|";

        std::vector<PokerCards> l_cards;
        l_cards.push_back(PokerCards(l_high_card_str));
        l_cards.push_back(PokerCards(l_one_pair_str));
        l_cards.push_back(PokerCards(l_two_pair_str));
        l_cards.push_back(PokerCards(l_toak_str));
        l_cards.push_back(PokerCards(l_straight_str));
        l_cards.push_back(PokerCards(l_flush_str));
        l_cards.push_back(PokerCards(l_full_house_str));
        l_cards.push_back(PokerCards(l_quads_str));
        l_cards.push_back(PokerCards(l_straight_flush_str));

        Combination l_comparison_combs(l_cards.size(), 2);

        for (const Combination& c : l_comparison_combs)
        {
            if (l_cards[c[0]] > l_cards[c[1]])
            {
                std::cout << l_cards[c[0]] << " > " << l_cards[c[1]] << std::endl;
            }
            else if (l_cards[c[0]] < l_cards[c[1]])
            {
                std::cout << l_cards[c[0]] << " < " << l_cards[c[1]] << std::endl;
            }

        }

    }

    /* Test of class PokerFiveCardHand
    */
    void HandMagnitudeComparison_HighCard()
    {
        std::string l_AKQJ9_str = "|Ad||Kc||Qd||Jc||9d|";
        std::string l_AKQJ4_str = "|Ad||Kc||Qd||Jc||4d|";
        std::string l_AKQT7_str = "|Ad||Kc||Qd||Tc||7d|";
        std::string l_AJT98_str = "|Ad||Jc||Td||9c||8d|";
        std::string l_KQJT4_str = "|Kd||Qc||Jd||Tc||4d|";

        std::vector<PokerCards> l_cards;
        l_cards.push_back(PokerCards(l_AKQJ9_str));
        l_cards.push_back(PokerCards(l_AKQJ4_str));
        l_cards.push_back(PokerCards(l_AKQT7_str));
        l_cards.push_back(PokerCards(l_AJT98_str));
        l_cards.push_back(PokerCards(l_KQJT4_str));

        HandComparison(l_cards);
    }

    /* Test of class PokerFiveCardHand
    */
    void HandMagnitudeComparison_OnePair()
    {
        std::string l_AAK97_str = "|Ad||Ac||Kd||9c||7d|";
        std::string l_AAKQ7_str = "|Ad||Ac||Kd||Qc||7d|";
        std::string l_AAK67_str = "|Ad||Ac||Kd||6c||7d|";
        std::string l_AAK57_str = "|Ad||Ac||Kd||5c||7d|";
        std::string l_KK497_str = "|Kd||Kc||4d||9c||7d|";

        std::vector<PokerCards> l_cards;
        l_cards.push_back(PokerCards(l_AAK97_str));
        l_cards.push_back(PokerCards(l_AAKQ7_str));
        l_cards.push_back(PokerCards(l_AAK67_str));
        l_cards.push_back(PokerCards(l_AAK57_str));
        l_cards.push_back(PokerCards(l_KK497_str));

        HandComparison(l_cards);
    }

    /* Test of class PokerFiveCardHand
    */
    void HandMagnitudeComparison_TwoPair()
    {
        std::string l_AK_Q_str = "|Ad||Ac||Kd||Kc||Qd|";
        std::string l_AK_T_str = "|Ad||Ac||Kd||Kc||Td|";
        std::string l_AK_8_str = "|Ad||Ac||Kd||Kc||8d|";

        std::string l_AJ_Q_str = "|Ad||Ac||Jd||Jc||Qd|";
        std::string l_AJ_4_str = "|Ad||Ac||Jd||Jc||4d|";

        std::string l_QJ_A_str = "|Qd||Qc||Jd||Jc||Ad|";

        std::vector<PokerCards> l_cards;
        l_cards.push_back(PokerCards(l_AK_Q_str));
        l_cards.push_back(PokerCards(l_AK_T_str));
        l_cards.push_back(PokerCards(l_AK_8_str));
        l_cards.push_back(PokerCards(l_AJ_Q_str));
        l_cards.push_back(PokerCards(l_AJ_4_str));
        l_cards.push_back(PokerCards(l_QJ_A_str));

        HandComparison(l_cards);
    }

    /* Test of class PokerFiveCardHand
    */
    void HandMagnitudeComparison_TOAK()
    {
        std::string l_AAA_KQ_str = "|Ad||Ac||Ad||Kc||Qd|";
        std::string l_AAA_KJ_str = "|Ad||Ac||Ad||Kc||Jd|";
        std::string l_AAA_QJ_str = "|Ad||Ac||Ad||Qc||Jd|";

        std::string l_KKK_AQ_str = "|Kd||Kc||Kd||Ac||Qd|";
        std::string l_KKK_AJ_str = "|Kd||Kc||Kd||Ac||Jd|";
        std::string l_KKK_QJ_str = "|Kd||Kc||Kd||Qc||Jd|";

        std::vector<PokerCards> l_cards;
        l_cards.push_back(PokerCards(l_AAA_KQ_str));
        l_cards.push_back(PokerCards(l_AAA_KJ_str));
        l_cards.push_back(PokerCards(l_AAA_QJ_str));
        l_cards.push_back(PokerCards(l_KKK_AQ_str));
        l_cards.push_back(PokerCards(l_KKK_AJ_str));
        l_cards.push_back(PokerCards(l_KKK_QJ_str));

        HandComparison(l_cards);
    }

    /* Test of class PokerFiveCardHand
    */
    void HandMagnitudeComparison_Straight()
    {
        std::string l_A2345_str = "|Ad||2c||3d||4c||5d|";
        std::string l_23456_str = "|2d||3c||4d||5c||6d|";
        std::string l_789TJ_str = "|7d||8c||9d||Tc||Jd|";
        std::string l_9TJQKA_str = "|9d||Tc||Jd||Qc||Kd|";
        std::string l_TJQKA_str = "|Td||Jc||Qd||Kc||Ad|";

        std::vector<PokerCards> l_cards;
        l_cards.push_back(PokerCards(l_A2345_str));
        l_cards.push_back(PokerCards(l_23456_str));
        l_cards.push_back(PokerCards(l_789TJ_str));
        l_cards.push_back(PokerCards(l_9TJQKA_str));
        l_cards.push_back(PokerCards(l_TJQKA_str));

        HandComparison(l_cards);
    }

    /* Test of class PokerFiveCardHand
    */
    void HandMagnitudeComparison_Flush()
    {
        std::string l_AKT89_str = "|Ad||Kd||Td||8d||9d|";
        std::string l_AQT89_str = "|Ad||Qd||Td||8d||9d|";
        std::string l_AQ987_str = "|Ad||Qd||9d||8d||7d|";
        std::string l_ATJ42_str = "|Ad||Td||Jd||4d||2d|";
        std::string l_KQT89_str = "|Kd||Qd||Td||8d||9d|";

        std::vector<PokerCards> l_cards;
        l_cards.push_back(PokerCards(l_AKT89_str));
        l_cards.push_back(PokerCards(l_AQT89_str));
        l_cards.push_back(PokerCards(l_AQ987_str));
        l_cards.push_back(PokerCards(l_ATJ42_str));
        l_cards.push_back(PokerCards(l_KQT89_str));

        HandComparison(l_cards);
    }

    /* Test of class PokerFiveCardHand
    */
    void HandMagnitudeComparison_FullHouse()
    {
        std::string l_AFOK_str = "|Ad||Ah||Ac||Kc||Ks|";
        std::string l_AFOQ_str = "|Ad||Ah||Ac||Qc||Qs|";
        std::string l_9FOA_str = "|9d||9h||9c||Ac||As|";
        std::string l_8FO2_str = "|8d||8d||8d||2d||2d|";

        std::vector<PokerCards> l_cards;
        l_cards.push_back(PokerCards(l_AFOK_str));
        l_cards.push_back(PokerCards(l_AFOQ_str));
        l_cards.push_back(PokerCards(l_9FOA_str));
        l_cards.push_back(PokerCards(l_8FO2_str));

        HandComparison(l_cards);
    }

    /* Test of class PokerFiveCardHand
    */
    void HandMagnitudeComparison_Quads()
    {
        std::string l_AAAAK_str = "|Ad||Ah||Ac||As||Ks|";
        std::string l_AAAA4_str = "|Ad||Ah||Ac||As||4s|";
        std::string l_KKKKA_str = "|Kd||Kh||Kc||Ks||As|";
        std::string l_44447_str = "|4d||4h||4c||4s||7s|";

        std::vector<PokerCards> l_cards;
        l_cards.push_back(PokerCards(l_AAAAK_str));
        l_cards.push_back(PokerCards(l_AAAA4_str));
        l_cards.push_back(PokerCards(l_KKKKA_str));
        l_cards.push_back(PokerCards(l_44447_str));

        HandComparison(l_cards);
    }

    /* Test of class PokerFiveCardHand
*/
    void HandMagnitudeComparison_StraightFlush()
    {
        std::string l_A2345_str = "|Ad||2d||3d||4d||5d|";
        std::string l_23456_str = "|2d||3d||4d||5d||6d|";
        std::string l_789TJ_str = "|7d||8d||9d||Td||Jd|";
        std::string l_9TJQKA_str = "|9d||Td||Jd||Qd||Kd|";
        std::string l_TJQKA_str = "|Td||Jd||Qd||Kd||Ad|";

        std::vector<PokerCards> l_cards;
        l_cards.push_back(PokerCards(l_A2345_str));
        l_cards.push_back(PokerCards(l_23456_str));
        l_cards.push_back(PokerCards(l_789TJ_str));
        l_cards.push_back(PokerCards(l_9TJQKA_str));
        l_cards.push_back(PokerCards(l_TJQKA_str));

        HandComparison(l_cards);
    }

    /* Test of class PokerCards
    */
    void IdentifyHighestStraight()
    {
        std::string l_A234567_str = "|Ad||2d||3d||4d||5d||6c||7s|";
        std::string l_234567_str = "|2d||3d||4d||5d||6c||7s|";
        std::string l_89TJQKA_str = "|8d||9d||Td||Jd||Qc||Ks||As|";

        std::vector<PokerCards> l_cards;
        l_cards.push_back(PokerCards(l_A234567_str));
        l_cards.push_back(PokerCards(l_234567_str));
        l_cards.push_back(PokerCards(l_89TJQKA_str));

        PokerCards l_straight(l_A234567_str);

        for (PokerCards& c : l_cards)
        {
            c.Shuffle();
            std::cout << c << " is a straight of order " << c.IsNstraight(5) << std::endl;
        }

    }

    /* Test of class PokerCards
    */
    void IdentifyStraightFlush()
    {
        std::string l_A234567_str = "|Ad||2d||3d||4d||5d||6c||7s|";
        std::string l_A234567_str_v2 = "|Ad||2d||3d||4d||5d||6d||7s|";
        std::string l_A234567_str_v3 = "|Ad||2d||3d||4d||5d||6d||7d|";
        std::string l_234567_str = "|2d||3d||4d||5d||6c||7s|";
        std::string l_89TJQKA_str = "|8d||9d||Td||Jd||Qd||Ks||As|";
        std::string l_89TJQKA_str_v2 = "|8d||9d||Td||Jd||Qd||Ks||Ad|";

        std::vector<PokerCards> l_cards;
        l_cards.push_back(PokerCards(l_A234567_str));
        l_cards.push_back(PokerCards(l_A234567_str_v2));
        l_cards.push_back(PokerCards(l_A234567_str_v3));
        l_cards.push_back(PokerCards(l_234567_str));
        l_cards.push_back(PokerCards(l_89TJQKA_str));
        l_cards.push_back(PokerCards(l_89TJQKA_str_v2));

        PokerCards l_straight(l_A234567_str);

        for (PokerCards& c : l_cards)
        {
            c.Shuffle();
            std::cout << c << " is a straight-flush of order " << c.IsNstraightFlush(5) << std::endl;
        }

    }

}