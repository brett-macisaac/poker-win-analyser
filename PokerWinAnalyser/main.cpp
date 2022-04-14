
/* Poker Win Analyser

* Description: 
    > On many modern poker games and television programs, the chance of each player winning the hand is displayed on the
      screen. This program intends to not only replicate this but to include more information, such as multi-way ties.
    > Currently, the implementation focusses entirely on Texas Hold'em, but in the future it may be extended to account
      for other poker variants.

* Author: 
    > Brett MacIsaac.
          
* Problems:
    > The execution time is far too long relative to other implementations. There's an app on the Google Play / App Store
      called 'Poker Calculator' which has the same functionality as this program but with a quick and intuitive GUI.
      It's able to calculate the same results significantly faster than this program. Perhaps it employs multithreading
      in some clever way.
*/



#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<unordered_map>

#include"PokerCards.h"
#include"Tests.h"
#include"Dealer.h"
#include"UtilityFunctions.h"
#include"StopWatch.h"



// A flag that, when true, only allows testing code to be run, as opposed to the actual program.
bool g_testing = false;

// The minimum number of contesting hands.
unsigned int g_min_hands = 2;

// The maximum number of contesting hands.
unsigned int g_max_hands = 8;



// Function prototypes:
void Testing();
void Program_V1();
void Program_V2(); // Slightly lower (oon average) than V1.



int main()
{
    if (g_testing)
    {
        Testing();
    }
    else
    {
        Program_V1();
        //Program_V2();
    }

}


/*

* Notes:
    (a). These are the hands whose chances of winning are to be determined.
    (b). For information on the format of the file, there are notes within it.
    (c). Note that there must at least be one community card to be dealt; if the river has already been dealt then
            the problem ceases to be probabilistic but rather deterministic: i.e. the winner/s is/are already known,
            thus rendering the program redundant.
    (d). All of the revealed/known cards must be removed from the deck, otherwise the combinations of future
            community cards may include the ones already dealt, which isn't desired.
    (e). The 'key' of each element of this map may be referred to as a 'winner combination'. To help explain this
            concept, imagine a set of hands, {a, b, c} with an associated set of indexes {0, 1, 2} (i.e. 0 maps to a,
            1 to b, etc). Most of the time, a, b, or c will win (i.e. one winner), but sometimes there might be multiple
            winners, such as a tie between a and b (0 and 1). The winning hand/hands can be represented as a subset of
            the hands' indexes: e.g. if a wins, the subset will be {0}, but if a and b tie it will be {0, 1}; both of
            these subsets may be referred to as 'winner combinations' (WCs). The total number of WCs is equal to
            2^n - 1, where n is the number of contesting hands. the associated 'value' of each element is the number of
            times the corresponding WB occurs: e.g. if a and b tie 100 times, the value of the key {0, 1} will be 100.
*/
void Program_V1()
{
    // (a). A container for the players' hands.
    std::vector<PokerCards> l_hands;

    // (b). Open an input stream to the file in which the hands are contained.
    std::ifstream l_file_cards("cards.txt");

    // Check if the text file couldn't be opened.
    if (!l_file_cards.good())
    {
        std::cout << "Error: cannot open 'cards.txt'.";
        return;
    }

    // The number of hands.
    int l_num_hands;

    // Get the number of hands.
    l_file_cards >> l_num_hands;

    // A string to take input from the file.
    std::string l_cards;

    // Populate the hands container.
    Utils::SkipFileLines(l_file_cards, 1); // Go to the next line.
    for (int i = 0; i < l_num_hands; ++i)
    {
        std::getline(l_file_cards, l_cards);

        l_hands.push_back(PokerCards(l_cards));
    }

    // If there's less than two hands, the program cannot run.
    if (l_hands.size() < g_min_hands)
    {
        std::cout << "Error: there must be at least two hands.";
        return;
    }
    else if (l_hands.size() > g_max_hands)
    {
        std::cout << "Error: there must be at most eight hands.";
        return;
    }

    // The dealer.
    Dealer l_dealer;

    // Get the community cards.
    std::getline(l_file_cards, l_cards);

    // Create the community cards.
    PokerCards l_community_cards(l_cards, false, false, true);

    // (c). Validate the community cards.
    int l_size_community_cards = l_community_cards.GetSize();
    if (l_size_community_cards < 3 && l_size_community_cards != 0)
    {
        std::cout << "Error: there must be either zero or at least three community cards.";
        return;
    }
    else if (l_size_community_cards >= 5)
    {
        std::cout << "Error: there must be at least one community card not yet dealt.";
        return;
    }

    // Get the folded/known cards.
    std::getline(l_file_cards, l_cards);

    // The 'known' cards. These are typically the cards that have already been folded or accidentally revealed by the dealer or players.
    PokerCards l_known_cards(l_cards, false);

    // All of the (relevant) data from the file has been removed; therefore, close it.
    l_file_cards.close();

    // (d). Remove all of the visible/known cards from the deck (the contesting hands + revealed community cards + 'known' cards).
    l_dealer.RemoveCardsFromDeck(l_hands);
    l_dealer.RemoveCardsFromDeck(l_community_cards);
    l_dealer.RemoveCardsFromDeck(l_known_cards);

    // The number of known cards.
    int l_num_cards_known = l_hands.size() * l_hands[0].GetSize() + l_community_cards.GetSize() + l_known_cards.GetSize();

    if (PokerDeck::S_NUM_CARDS_FULL_DECK - l_dealer.GetDeck().GetSize() != l_num_cards_known)
    {
        std::cout << "Error: there are one or more duplicate cards.";
        return;
    }


    // If this point is reached, the actual program can commence (i.e. everything has been set-up and validated).

    std::ofstream l_file_output("results.txt");

    // Output the situation to console.
    std::cout << "Contesting Hands:\n";
    for (PokerCards& p : l_hands)
    {
        std::cout << "    > " << p << std::endl;
    }
    std::cout << "Community Cards:\n    > " << l_community_cards << std::endl;
    std::cout << "Known Cards:\n    > " << l_known_cards << std::endl;

    // Output the situation to file.
    l_file_output << "Contesting Hands:\n";
    for (PokerCards& p : l_hands)
    {
        l_file_output << "    > " << p << std::endl;
    }
    l_file_output << "Community Cards:\n    > " << l_community_cards << std::endl;
    l_file_output << "Known Cards:\n    > " << l_known_cards << std::endl;

    // An object to record how long the program executes for.
    StopWatch l_timer;

    // The number of community cards to be revealed.
    int l_num_community_cards_to_reveal = 5 - l_community_cards.GetSize();

    // The combinations associated with the community cards to be revealed.
    Combination l_combs_community_cards(l_dealer.GetDeck().GetSize(), l_num_community_cards_to_reveal);

    // The number of combinations that must be iterated over.
    unsigned int l_num_combinations = l_combs_community_cards.GetNumCombinations();

    // A map that links each hand with its best 5-card hand for given community cards.
    std::unordered_map<PokerCards, HandValue> l_hands_5_card_map;

    // (e). A container to house the results of every 'winner combination'.
    // Could instead create a class called 'Result', which is simply a Combination adapter class with an int field.
    // Alternatively, it could be a child class of Combination. This might speed things up.
    std::unordered_map<Combination, int> l_results;

    // Populate the results container (the power-set of n minus the empty set).
    for (int i = 1; i <= l_hands.size(); ++i)
    {
        // All WCs where there's i winner(s).
        Combination l_combs_i_winners(l_hands.size(), i);

        for (const Combination& c : l_combs_i_winners)
        {
            l_results.insert({ c, 0 });
        }

    }

    // A container to hold the 7-cards available to a player at the river.
    PokerCards l_7_cards(7);
    //l_7_cards.CopyCards(l_community_cards); // it always includes the current (previously revealed) community cards.

    // A container for the community cards that are yet to be revealed.
    PokerCards l_community_cards_to_come(l_num_community_cards_to_reveal, true);

    // A vector with all the hands' best 5-card combinations.
    std::vector<HandValue> l_best_5_card_hands(l_hands.size());

    float l_duration_hand_assignment = 0.0;

    StopWatch l_timer_micro(false, TimeUnit::MicroSecs);

    // Iterate over every possible combination of community cards.
    for (const Combination& c : l_combs_community_cards)
    {
        // Copy the values of the cards of the current combination into the 7-card container.
        l_7_cards.CopyCards(l_community_cards);
        for (int i = 0; i < l_combs_community_cards.GetK(); ++i)
        {
            l_7_cards.CopyCard(l_dealer.GetDeck()[c[i]], 5 - l_num_community_cards_to_reveal + i);
        }
        
        l_timer_micro.Start(); // About 80% of the time is consumed by this for loop.
        // Assign the best 5-card hand for each hand in l_hands.
        for (int i = 0; i < l_hands.size(); ++i)
        {
            // Copy the values of the player's hand into the 7-card container.
            if (i == 0)
            {
                // Copy the values of the player's hand into the 7-card container.
                l_7_cards.CopyCards(l_hands[i], 5);
            }
            else
            {
                l_7_cards.CopyCards_NonCommunity(l_hands[i]);
            }

            // Set l_7_cards value.
            l_7_cards.SetValue(false);

            // Assign hand's highest 5-card combination.
            l_hands_5_card_map[l_hands[i]] = l_7_cards.GetValue();
        }
        l_timer_micro.Stop();
        l_duration_hand_assignment += l_timer_micro.GetDuration();

        // Populate l_best_5_card_hands.
        // https://stackoverflow.com/questions/14555751/how-to-iterate-over-a-c-stl-map-data-structure-using-the-auto-keyword
        int l_index_best_5_card_hands = 0;
        for (auto& [key, value] : l_hands_5_card_map) // requires C++17 or higher.
        {
            l_best_5_card_hands[l_index_best_5_card_hands++] = value;
        }

        // Sort l_best_5_card_hands.
        std::stable_sort(l_best_5_card_hands.begin(), l_best_5_card_hands.end(), HandValue::Comparator_Descending);

        // The winning hand. The winning hand might belong to more than one player.
        HandValue& l_winning_hand = l_best_5_card_hands.front();

        // A container of the hands that won.
        std::vector<PokerCards> l_winners_cards;

        // Populate l_winners_cards.
        for (auto& [key, value] : l_hands_5_card_map) // requires C++17 or higher.
        {
            if (value == l_winning_hand)
            {
                l_winners_cards.push_back(key);
            }

        }

        // A container to hold the WC.
        std::vector<unsigned int> l_winner_combination;

        // Populate l_winner_combination.
        for (int i = 0; i < l_hands.size(); ++i)
        {
            for (PokerCards& cards : l_winners_cards)
            {
                if (l_hands[i] == cards)
                {
                    l_winner_combination.push_back(i);
                    break;
                }

            }

        }

        // Increment the count of the WC.
        for (auto& [key, value] : l_results)
        {
            if (key == l_winner_combination) // If key is the WC.
            {
                ++value;
                break;
            }

        }

    }

    l_timer.Stop();

    // Remove all WCs which have a win count of 0, as these are irrelevant.
    for (auto it_curr = l_results.begin(), it_end = l_results.end(); it_curr != it_end;)
    {
        if (it_curr->second == 0) // If there are 0 wins associated with this WC.
        {
            // The erase method returns the iterator to the next element; thus, don't increment the iterator using the increment operator.
            it_curr = l_results.erase(it_curr);
        }
        else
        {
            ++it_curr;
        }

    }

    // Output the results.
    std::cout << "\nResults:\n";
    l_file_output << "\nResults:\n";
    for (auto& [key, value] : l_results)
    {
        // Indent the results.
        std::cout << "    > ";
        l_file_output << "    > ";

        // Output the hands that corrrespond to the WC.
        for (int i = 0; i < key.GetK(); ++i)
        {
            if (i != key.GetK() - 1) // If not on the last index of the combination.
            {
                std::cout << l_hands[key[i]] << ", ";
                l_file_output << l_hands[key[i]] << ", ";
            }
            else
            {
                std::cout << l_hands[key[i]];
                l_file_output << l_hands[key[i]];
            }

        }

        float l_chance = (float)(100 * value) / l_num_combinations;

        // Output the % chance of this WC occurring.
        std::cout << ": " << l_chance << '%' << std::endl;
        l_file_output << ": " << l_chance << '%' << std::endl;
    }

    std::cout << "\nTime taken:\n    > " << l_timer.GetDuration() << "ms" << std::endl;
    std::cout << "\nNo. of combinations:\n    > " << l_combs_community_cards.GetNumCombinations() << std::endl;
    std::cout << "\nCombs per ms:\n    > " << (float)l_combs_community_cards.GetNumCombinations() / l_timer.GetDuration() << std::endl;
    std::cout << "\nTime taken for hand-assignment (microsecs):\n    > " << l_duration_hand_assignment << std::endl;
    l_file_output << "\nTime Taken:\n    > " << l_timer.GetDuration() << "ms" << std::endl;
    l_file_output << "\nNo. of combinations:\n    > " << l_combs_community_cards.GetNumCombinations() << std::endl;
    l_file_output << "\nCombs per ms:\n    > " << (float)l_combs_community_cards.GetNumCombinations() / l_timer.GetDuration() << std::endl;
    l_file_output << "\nTime taken for hand-assignment (microsecs):\n    > " << l_duration_hand_assignment << std::endl;

    l_file_output.close();
}


/*
    * An slightly different version of Program_V1().
    * For some reason it 'swaps' some of the hands' results, such as with the below input:
    * 4
      |Ah||Ad|
      |Kc||Kd|
      |8c||8d|
      |Ac||4d|
      |Jc||Qc||Tc|

*/
void Program_V2()
{
    // (a). A container for the players' hands.
    std::vector<PokerCards> l_hands;

    // (b). Open an input stream to the file in which the hands are contained.
    std::ifstream l_file_cards("cards.txt");

    // Check if the text file couldn't be opened.
    if (!l_file_cards.good())
    {
        std::cout << "Error: cannot open 'cards.txt'.";
        return;
    }

    // The number of hands.
    int l_num_hands;

    // Get the number of hands.
    l_file_cards >> l_num_hands;

    // A string to take input from the file.
    std::string l_cards;

    // Populate the hands container.
    Utils::SkipFileLines(l_file_cards, 1); // Go to the next line.
    for (int i = 0; i < l_num_hands; ++i)
    {
        std::getline(l_file_cards, l_cards);

        l_hands.push_back(PokerCards(l_cards));
    }

    // If there aren't more than two hands the program cannot run.
    if (l_hands.size() < g_min_hands)
    {
        std::cout << "Error: there must be at least two hands.";
        return;
    }
    else if (l_hands.size() > g_max_hands)
    {
        std::cout << "Error: there must be at most eight hands.";
        return;
    }

    // The dealer.
    Dealer l_dealer;

    // Get the community cards.
    std::getline(l_file_cards, l_cards);

    // Create the community cards.
    PokerCards l_community_cards(l_cards, false, false, true);

    // (c). Validate the community cards.
    int l_size_community_cards = l_community_cards.GetSize();
    if (l_size_community_cards < 3 && l_size_community_cards != 0)
    {
        std::cout << "Error: there must be either zero or at least three community cards.";
        return;
    }
    else if (l_size_community_cards == 5)
    {
        std::cout << "Error: there must be at least one community card not yet dealt.";
        return;
    }

    // Get the folded/known cards.
    std::getline(l_file_cards, l_cards);

    // The 'known' cards. These are typically the cards that have already been folded or accidentally revealed by the dealer or players.
    PokerCards l_known_cards(l_cards, false);

    // All of the (relevant) data from the file has been removed; therefore, close it.
    l_file_cards.close();

    // (d). Remove all of the visible/known cards from the deck (the contesting hands + revealed community cards + 'known' cards).
    l_dealer.RemoveCardsFromDeck(l_hands);
    l_dealer.RemoveCardsFromDeck(l_community_cards);
    l_dealer.RemoveCardsFromDeck(l_known_cards);

    if (PokerDeck::S_NUM_CARDS_FULL_DECK - l_dealer.GetDeck().GetSize() != l_hands.size() * l_hands[0].GetSize() + l_community_cards.GetSize() + l_known_cards.GetSize())
    {
        std::cout << "Error: there are one or more duplicates.";
        return;
    }


    // If this point is reached, the actual program can commence (i.e. everything has been set-up and validated).

    std::ofstream l_file_output("results.txt");

    // Output the situation to console.
    std::cout << "Contesting Hands:\n";
    for (PokerCards& p : l_hands)
    {
        std::cout << "    > " << p << std::endl;
    }
    std::cout << "Community Cards:\n    > " << l_community_cards << std::endl;
    std::cout << "Known Cards:\n    > " << l_known_cards << std::endl;

    // Output the situation to file.
    l_file_output << "Contesting Hands:\n";
    for (PokerCards& p : l_hands)
    {
        l_file_output << "    > " << p << std::endl;
    }
    l_file_output << "Community Cards:\n    > " << l_community_cards << std::endl;
    l_file_output << "Known Cards:\n    > " << l_known_cards << std::endl;

    // Create and start the timer.
    StopWatch l_timer;

    // The number of community cards to be revealed.
    int l_num_community_cards_to_reveal = 5 - l_community_cards.GetSize();

    // The combinations associated with the community cards to be revealed.
    Combination l_combs_community_cards(l_dealer.GetDeck().GetSize(), l_num_community_cards_to_reveal);

    // The number of combinations that must be iterated over.
    unsigned int l_num_combinations = l_combs_community_cards.GetNumCombinations();

    // A map that links each hand with its original index of the vector l_hands.
    std::unordered_map<PokerCards, int> l_hand_indexes;
    for (int i = 0; i < l_hands.size(); ++i)
    {
        l_hand_indexes.insert({ l_hands[i], i });
    }

    // (e). A container to house the results of every 'winner combination'.
    // Could instead create a class called 'Result', which is simply a Combination adapter class with an int field.
    // Alternatively, it could be a child class of Combination. This might speed things up.
    std::unordered_map<Combination, int> l_results;

    // Populate the results container (the power-set of n minus the empty set).
    for (int i = 1; i <= l_hands.size(); ++i)
    {
        // All WCs where there's i winner(s).
        Combination l_combs_i_winners(l_hands.size(), i);

        for (const Combination& c : l_combs_i_winners)
        {
            l_results.insert({ c, 0 });
        }

    }

    // A container to hold the 7-cards available to a player at the river.
    PokerCards l_7_cards(7);
    //l_7_cards.CopyCards(l_community_cards); // it always includes the current (previously revealed) community cards.

    // A container for the community cards that are yet to be revealed.
    PokerCards l_community_cards_to_come(l_num_community_cards_to_reveal, true);

    float l_duration_hand_assignment = 0.0;

    StopWatch l_timer_micro(false, TimeUnit::MicroSecs);

    // Iterate over every possible combination of community cards.
    for (const Combination& c : l_combs_community_cards)
    {
        // Copy the values of the cards of the current combination into the 7-card container.
        l_7_cards.CopyCards(l_community_cards);
        for (int i = 0; i < l_combs_community_cards.GetK(); ++i)
        {
            l_7_cards.CopyCard(l_dealer.GetDeck()[c[i]], 5 - l_num_community_cards_to_reveal + i);
        }

        l_timer_micro.Start();
        // Assign the best 5-card hand for each hand in l_hands.
        for (int i = 0; i < l_hands.size(); ++i)
        {
            // Copy the values of the player's hand into the 7-card container.
            if (i == 0)
            {
                l_7_cards.CopyCards(l_hands[i], 5);
            }
            else
            {
                l_7_cards.CopyCards_NonCommunity(l_hands[i]);
            }

            // Set l_7_cards value.
            l_7_cards.SetValue(false);

            // Copy the hand value of l_7_cards to l_hands[i].
            l_hands[i].SetValue(l_7_cards.GetValue());
        }
        l_timer_micro.Stop();
        l_duration_hand_assignment += l_timer_micro.GetDuration();

        // A container to hold the WC.
        std::vector<unsigned int> l_winner_combination;

        // Sort l_hands in descending order.
        std::stable_sort(l_hands.begin(), l_hands.end(), PokerCards::Comparator_Value_Descending);

        // Populate l_winner_combination.
        l_winner_combination.push_back(l_hand_indexes[l_hands[0]]);
        for (int i = 1; i < l_hands.size(); ++i)
        {
            if (l_hands[i].GetValue() == l_hands[i - 1].GetValue())
            {
                l_winner_combination.push_back(l_hand_indexes[l_hands[i]]);
            }
            else
            {
                break;
            }
        }

        // Make sure the WC is in ascending order, as all of the WCs in l_results are in ascending order.
        std::stable_sort(l_winner_combination.begin(), l_winner_combination.end());

        // Increment the count of the WC.
        for (auto& [key, value] : l_results)
        {
            if (key == l_winner_combination) // If key is the WC.
            {
                ++value;
                break;
            }

        }

    }

    l_timer.Stop();

    // Remove all WCs which have a win count of 0, as these are irrelevant.
    for (auto it_curr = l_results.begin(), it_end = l_results.end(); it_curr != it_end;)
    {
        if (it_curr->second == 0) // If there are 0 wins associated with this WC.
        {
            // The erase method returns the iterator to the next element; thus, don't increment the iterator using the increment operator.
            it_curr = l_results.erase(it_curr);
        }
        else
        {
            ++it_curr;
        }

    }

    // Output the results.
    std::cout << "\nResults:\n";
    l_file_output << "\nResults:\n";
    for (auto& [key, value] : l_results)
    {
        // Indent the results.
        std::cout << "    > ";
        l_file_output << "    > ";

        // Output the hands that corrrespond to the WC.
        for (int i = 0; i < key.GetK(); ++i)
        {
            if (i != key.GetK() - 1) // If not on the last index of the combination.
            {
                std::cout << l_hands[key[i]] << ", ";
                l_file_output << l_hands[key[i]] << ", ";
            }
            else
            {
                std::cout << l_hands[key[i]];
                l_file_output << l_hands[key[i]];
            }

        }

        float l_chance = (float)(100 * value) / l_num_combinations;

        // Output the % chance of this WC occurring.
        std::cout << ": " << l_chance << '%' << std::endl;
        l_file_output << ": " << l_chance << '%' << std::endl;
    }

    std::cout << "\nTime taken:\n    > " << l_timer.GetDuration() << "ms" << std::endl;
    std::cout << "\nNo. of combinations:\n    > " << l_combs_community_cards.GetNumCombinations() << std::endl;
    std::cout << "\nCombs per ms:\n    > " << (float)l_combs_community_cards.GetNumCombinations() / l_timer.GetDuration() << std::endl;
    std::cout << "\nTime taken for hand-assignment (microsecs):\n    > " << l_duration_hand_assignment << std::endl;
    l_file_output << "\nTime Taken:\n    > " << l_timer.GetDuration() << "ms" << std::endl;
    l_file_output << "\nNo. of combinations:\n    > " << l_combs_community_cards.GetNumCombinations() << std::endl;
    l_file_output << "\nCombs per ms:\n    > " << (float)l_combs_community_cards.GetNumCombinations() / l_timer.GetDuration() << std::endl;
    l_file_output << "\nTime taken for hand-assignment (microsecs):\n    > " << l_duration_hand_assignment << std::endl;

    l_file_output.close();
}


void Testing()
{
    //Tests::SetCardsFromString();

    //Tests::HandRecognition_From1Card();
    //Tests::HandRecognition_From2Cards();
    //Tests::HandRecognition_From3Cards();
    //Tests::HandRecognition_From4Cards();
    //Tests::HandRecognition_From5Cards();
    //Tests::HandRecognition_From6Cards();
    Tests::HandRecognition_From7Cards();

    //Tests::HandTypeComparison();

    //Tests::HandMagnitudeComparison_HighCard();
    //Tests::HandMagnitudeComparison_OnePair();
    //Tests::HandMagnitudeComparison_TwoPair();
    //Tests::HandMagnitudeComparison_TOAK();
    //Tests::HandMagnitudeComparison_Straight();
    //Tests::HandMagnitudeComparison_Flush();
    //Tests::HandMagnitudeComparison_FullHouse();
    //Tests::HandMagnitudeComparison_Quads();
    //Tests::HandMagnitudeComparison_StraightFlush();

    //Tests::IdentifyHighestStraight();
    //Tests::IdentifyStraightFlush();
}