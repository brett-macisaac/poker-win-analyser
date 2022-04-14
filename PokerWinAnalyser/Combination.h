#pragma once


#include<iostream>
#include<vector>
#include<stdexcept>


/*
* This class can be used to create and iterate over combinations of size k from n elements, where n >= k.

* Credits:
    > https://web.archive.org/web/20170325012457/https://msdn.microsoft.com/en-us/library/aa289166.aspx
        * James McCaffrey, 2004.
        * This C++ implementation is inspired by his C# solution.

* Composition:
    (a). Fields (8)
    (b). Constructors (3)
    (c). Public Methods (12)
        (i). Accessors (5)
        (ii). Mutators (3)
    (d). Operators (3)
    (e). Static Methods (1)

*/
class Combination
{

private:

// (a). Fields (8) =====================================================================================================

    // The total number of elements.
    unsigned int f_n;

    // The number of elements to choose from n.
    unsigned int f_k;

    /* The Combination
    * Each element in a group of n elements is assumed to have an index, whereby index 0 corresponds to the 'first'
      element and index n-1 corresponds to the 'last' element. The ordering of the elements is completely arbitrary,
      such as the ordering of a deck of cards.
    * Each combination of size k from n elements can be represented as a set of digits of size k, where each digit is
      an index of the group of n elements.
        * e.g. if n is 4 and k is 2 (a group of 4 elements and combinations of size 2), then the combination that
               contains element at indexes 0 and 3 respectively can be represented as, {0,3}.
    */
    unsigned int* f_combination;

    /* The Combination's Index
    * Just as words (sets of letters) are ordered via alphabetical order, sets of numbers can be ordered via
        lexicographic order.
        * e.g. x = comb(4,2) = 6: there are 6 combinations of 2 elements from a group of 4 elements. Each of these
            combinations can be assigned a lexographic index:
            * 0: {0,1} -> first combination
            * 1: {0,2}
            * 2: {0,3}
            * 3: {1,2}
            * 4: {1,3}
            * 5: {2,3} -> last combination
        * The above lexicographic ordering of six sets of numbers can be compared to the alphabetical ordering of
            words (sets of letters):
            * 0: "am"
            * 1: "an"
            * 2: "as"
            * 3: "be"
            * 4: "by"
            * 5: "do"
            i.e. just as "an" is ordered below "as", {0,1} is ordered below {0,2}: i.e. while the two combinations
                have the same first digit, the second digit of {0,1} is lower than that of {0,2}
                (i.e. 1 < 2), just as the second digit of "an" is lower than that of "as".
    */
    unsigned int f_index_lexicographic;

    /* Min and Max Iteration Indexes
    * These two fields represent the maximum and minimum lexicographic indexes of a Combination object when it is
        being 'iterated over' in a for-each loop.
    * The default value for the max is f_num_combinations - 1, while the default for the min is 0 (i.e. full range).
    * The reason for having these fields is that it might take a very long time for one thread to iterate over all
        indexes in a particular algorithm; in contrast, if many threads are given a portion of a combination's
        lexicographic range, the algorithm will be able to run potentially several orders of magnitude faster.
    */
    unsigned int f_index_iteration_max;
    unsigned int f_index_iteration_min;

    // The number of combinations of k from n.
    unsigned int f_num_combinations;

    // A flag that, when true, indicates that the combinations are being iterated over (for each loop).
    bool f_flag_iterating;


public:

// (b). Constructors (3) ===============================================================================================

    /* Constructor
    */
    Combination(unsigned int a_n = 4, unsigned int a_k = 2);

    /* Constructor
    */
    Combination(unsigned int a_n, unsigned int a_k, unsigned int* a_combination, unsigned int a_index_lexicographic);

    /* Copy Constructor
    */
    Combination(const Combination& a_comb);

    /* Destructor
    */
    ~Combination();



// (c). Public Methods (12) ============================================================================================

    /*
        * This method returns a new Combination object at the specified index.
    */
    Combination GetCombAtIndex(unsigned int a_index) const;

    /* Notifier
        * This method returns whether or not the current index is the max index.
    */
    bool IsMaxIndex() const;

    /* Iteration Auxiliary
    */
    Combination begin();

    /* Iteration Auxiliary
    */
    Combination end();


// (c)(i). Accessors (5) ===============================================================================================

    /* Accessor of f_index_combination
        * Returns the index of the current combination.
    */
    unsigned int GetIndex() const;

    /* Accessor of f_combination
    */
    unsigned int* GetCombination() const;

    /* Accessor of f_num_combinations
    */
    unsigned int GetNumCombinations() const;

    /* Accessor of f_n
    */
    unsigned int GetN() const;

    /* Accessor of f_k
    */
    unsigned int GetK() const;


// (c)(ii). Mutators (3) ===============================================================================================

    /* Mutator of f_index_lexicographic, f_combination
    * Sets the combination to the specified index.
    */
    void SetCombination(unsigned int a_index);

    /* Mutator of f_index_lexicographic
       * Sets the combination to the specified index.
    */
    void SetIndex(unsigned int a_index);

    /* Mutator of f_index_iteration_min, f_index_iteration_max
       * Sets the combination to the specified index.
    */
    void SetMinMaxIterationIndexes(unsigned int a_index_iteration_min, unsigned int a_index_iteration_max);



// (d). Operators (3) ==================================================================================================

    /* ++ (prefix increment) Operator
    */
    Combination& operator++();

    /* -- (prefix decrement) Operator
    */
    Combination& operator--();

    /* = (assignment) Operator
    */
    Combination& operator=(const Combination& a_comb);

    /* == (equivalency) Operator
    */
    bool operator==(const Combination& a_comb) const;

    /* == (equivalency) Operator (alternate)
    */
    bool operator==(std::vector<unsigned int> a_comb) const;

    /* != (non-equivalency) Operator
    */
    bool operator!=(const Combination& a_comb);

    /* != (non-equivalency) Operator (alternate)
    */
    bool operator!=(std::vector<unsigned int> a_comb) const;

    /* [] (indexer) Operator (Accessor of f_combination)
    */
    unsigned int operator[](unsigned int a_index) const;

    /* * (dereference) Operator
    */
    const Combination& operator*();

    /* << (output) Operator
    */
    friend std::ostream& operator<<(std::ostream& a_ostream, const Combination a_comb);


// (e). Static Methods (1) =============================================================================================

    /* Static Utility Function
    * Returns the binomial coefficient associated with n and k: that is, it returns the number of combinations of k
      elements from a total of n elements.

    */
    static int Comb(int a_n, int a_k);
};



/*
* Implementation of std::hash<T>, which allows for Combination to be used as the key of unordered associative
    containers such as unordered_map.
*/
namespace std
{
    template <>
    class hash<Combination>
    {

    public:

        size_t operator()(const Combination& a_comb) const
        {
            // The summation of the combination's indexes.
            size_t l_hash = 0;

            for (int i = 0; i < a_comb.GetK() - 1; ++i)
            {
                l_hash += a_comb[i] * (i + 1);
            }

            return l_hash;
        }

    };

};