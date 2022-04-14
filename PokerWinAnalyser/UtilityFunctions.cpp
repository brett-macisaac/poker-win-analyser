
#include"UtilityFunctions.h"

namespace Utils
{
    /* Utility Function

        * Notes:
            (a).
                * 'rand() % 100' is a random integer between 0 and 99 (inclusive), while
                  'rand() % 100 + 1' is a random integer between 1 and 100 (i.e. 1 is added to both bounds).
                * 'rand() % a_max' is a random integer between 0 and a_max-1 (inclusive), while
                  'rand() % a_max + 1' is a random integer between 1 and a_max (i.e. 1 is added to both bounds).
                * 'rand() % l_amount_of_numbers' is between 0 and 'a_max - a_min + 1', while
                  'rand() % l_amount_of_numbers + a_min' is between a_min and a_max (inclusive).
    */
    int GetRandomBetween(int a_min, int a_max)
    {
        // Ensure a_min is less than a_max.
        if (a_min >= a_max)
        {
            return a_max;
        }

        // Calculate the amount of numbers between a_max and a_min (incl. both a_max and a_min).
        int l_amount_of_numbers = a_max - a_min + 1;

        // (a). Return a pseudo-random number between a_max and a_min.
        return rand() % l_amount_of_numbers + a_min;
    }

    /* Utility Function
    */
    void SkipFileLines(std::ifstream& a_ifstream, int a_num_of_lines)
    {
        for (int i = 0; i < a_num_of_lines; ++i)
        {
            a_ifstream.ignore(1000, '\n');
        }

    }

    /*
        * Prints the values of a_int_vector to the console.
    */
    void PrintIntVector(const std::vector<int>& a_int_vector)
    {
        std::cout << '(';
        for (int i = 0; i < a_int_vector.size(); ++i)
        {
            std::cout << a_int_vector[i];

            if (i != a_int_vector.size() - 1)
            {
                std::cout << ", ";
            }

        }
        std::cout << ')';

    }

    /*
        * Returns a string form of the given int vector.
    */
    std::string IntVectorToString(const std::vector<int>& a_int_vector)
    {
        std::stringstream l_ss;

        l_ss << '(';
        for (int i = 0; i < a_int_vector.size(); ++i)
        {
            l_ss << a_int_vector[i];

            if (i != a_int_vector.size() - 1)
            {
                l_ss << ", ";
            }
        }
        l_ss << ')';

        std::string l_str = l_ss.str();

        return l_str;
    }

}