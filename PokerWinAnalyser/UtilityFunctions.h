#pragma once

#include<stdlib.h> // rand().
#include<fstream> // std::ifstream
#include<iostream> // std::cout
#include<vector>
#include<string>
#include<sstream>

namespace Utils
{
    template<typename T>
    void ResetArray(T* a_array, int a_size)
    {
        for (int i = 0; i < a_size; ++i)
        {
            a_array[i] = T();
        }

    }

    /* Utility Function
        * Returns a pseudo-random integer between a_min and a_max (inclusive of both).
    */
    int GetRandomBetween(int a_min, int a_max);

    /* Utility Function
        * Moves the stream 'cursor' a_num_of_lines lines down: i.e. if cursor is at line number x, the cursor moves to 
          the (beginning) of line number 'x + a_num_of_lines'
        * This is particularly useful for taking text input from a text file.
    */
    void SkipFileLines(std::ifstream& a_istream, int a_num_of_lines);

    /*
        * Prints the values of a_int_vector to the console.
    */
    void PrintIntVector(const std::vector<int>& a_int_vector);

    /*
        * Returns a string form of the given int vector. 
    */
    std::string IntVectorToString(const std::vector<int>& a_int_vector);

    /*
        * Returns whether or not a_val is in a_int_vector.
    */
    bool IsValInIntVector(int a_val, std::vector<int> a_int_vector);

    /*
        * Returns whether or not a_val is in a_int_vector.
    */
    template<typename T>
    bool IsValInVector(T a_val, std::vector<T>& a_vector)
    {
        for (const T& val : a_vector)
        {
            if (a_val == val)
            {
                return true;
            }

        }

        return false;
    }

    template<typename T>
    void CopyVectorAToB(std::vector<T>& a_vector_a, std::vector<T>& a_vector_b)
    {
        for (int i = 0; i < a_vector_b.size() && i < a_vector_a.size(); ++i)
        {
            a_vector_b[i] = a_vector_a[i];
        }

    }

    // return 1 if a > b; -1 if b > a, and 0 if a == b.
    template<typename T>
    int CompareVectors(std::vector<T>& a_vector_a, std::vector<T>& a_vector_b)
    {
        int l_size_a = a_vector_a.size(), 
            l_size_b = a_vector_b.size();

        for (int i = 0; i < l_size_a && i < l_size_b; ++i)
        {
            if (a_vector_a[i] > a_vector_b[i])
            {
                return 1;
            }
            else if (a_vector_a[i] < a_vector_b[i])
            {
                return -1;
            }

        }

        if (l_size_a > l_size_b)
        { return 1; }
        else if (l_size_a < l_size_b)
        { return -1; }

        return 0;
    }

}
