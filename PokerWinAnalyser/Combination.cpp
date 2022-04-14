
#include"Combination.h"

Combination::Combination(unsigned int a_n /* = 4 */, unsigned int a_k /* = 2 */)
    : f_n(a_n), f_k(a_k), f_index_lexicographic(0), f_flag_iterating(false), f_index_iteration_min(0)
{
    f_combination = new unsigned int[f_k]();

    // n must be >= to k.
    if (f_n < f_k)
    {
        f_n = f_k;
    }

    for (int i = 0; i < f_k; ++i)
    {
        f_combination[i] = i;
    }

    f_num_combinations = Comb(f_n, f_k);

    f_index_iteration_max = f_num_combinations - 1;
}

Combination::Combination(unsigned int a_n, unsigned int a_k, unsigned int* a_combination, unsigned int a_index_lexicographic)
    : f_n(a_n), f_k(a_k), f_index_lexicographic(a_index_lexicographic), f_flag_iterating(false), f_index_iteration_min(0)
{
    f_combination = new unsigned int[f_k]();

    for (unsigned int i = 0; i < f_k; ++i)
    {
        f_combination[i] = a_combination[i];
    }

    f_num_combinations = Comb(f_n, f_k);

    f_index_iteration_max = f_num_combinations - 1;
}

Combination::Combination(const Combination& a_comb)
    : f_n(a_comb.f_n), f_k(a_comb.f_k), f_index_lexicographic(a_comb.f_index_lexicographic),
    f_num_combinations(a_comb.f_num_combinations), f_flag_iterating(a_comb.f_flag_iterating),
    f_index_iteration_min(a_comb.f_index_iteration_min), f_index_iteration_max(a_comb.f_index_iteration_max)
{
    f_combination = new unsigned int[f_k]();

    for (unsigned int i = 0; i < f_k; ++i)
    {
        f_combination[i] = a_comb.f_combination[i];
    }

}

Combination::~Combination()
{
    delete[] f_combination;
}

bool Combination::IsMaxIndex() const
{
    return f_index_lexicographic == f_num_combinations - 1;
}

Combination Combination::begin()
{
    Combination l_begin = *this;

    l_begin.SetCombination(f_index_iteration_min);

    l_begin.f_flag_iterating = true;

    return l_begin;
}

Combination Combination::end()
{
    Combination l_end = *this;

    l_end.SetIndex(f_index_iteration_max + 1);

    return l_end;
}

/* Accessor of f_combination
    * Returns the index of the current combination.
*/
unsigned int Combination::GetIndex() const
{
    return f_index_lexicographic;
}

/* Accessor of f_combination
*/
unsigned int* Combination::GetCombination() const
{
    return f_combination;
}

/* Accessor of f_num_combinations
*/
unsigned int Combination::GetNumCombinations() const
{
    return f_num_combinations;
}

/* Accessor of f_n
*/
unsigned int Combination::GetN() const
{
    return f_n;
}

/* Accessor of f_k
*/
unsigned int Combination::GetK() const
{
    return f_k;
}

// Like the GetAtIndex method from V1.
Combination Combination::GetCombAtIndex(unsigned int a_index) const
{
    // The maximum index of a combination.
    unsigned int l_index_max = f_num_combinations - 1;

    if (a_index > l_index_max)
    {
        return Combination();
    }
    else if (a_index == f_index_lexicographic)
    {
        return *this;
    }

    // An array to temporarily store indexes of the elements in the combination that will be returned.
    unsigned int* l_combination = new unsigned int[f_k]();

    // (a). The dual index of a_index.
    unsigned int l_index_dual = l_index_max - a_index;

    // Variables used in creating the combinadic representation of a_index_dual.
    unsigned int l_prev_combinatic_digit = f_n;
    unsigned int l_b = f_k;
    unsigned int l_index_dual_remaining = l_index_dual;

    // (b). Get the combinadic representation of a_index_dual.
    for (unsigned int i = 0; i < f_k; ++i)
    {
        // The ith digit must be less than the previous combinatic digit (or f_n if i is 0).
        unsigned int l_ith_combinatic_digit = l_prev_combinatic_digit - 1;

        // Get the digit.
        while (Comb(l_ith_combinatic_digit, l_b) > l_index_dual_remaining)
        {
            --l_ith_combinatic_digit;
        }

        // Assign the digit.
        l_combination[i] = l_ith_combinatic_digit;

        // Store the digit so that the next one can be determined.
        l_prev_combinatic_digit = l_ith_combinatic_digit;

        // Subtract the magnitude of the ith digit from the remaining magnitude of the dual index.
        l_index_dual_remaining -= Comb(l_ith_combinatic_digit, l_b);

        --l_b;
    }

    // Get the lexicographic index of the combination at a_index by modifying each digit of the dual index's combinadic form.
    for (unsigned int i = 0; i < f_k; ++i)
    {
        l_combination[i] = (f_n - 1) - l_combination[i];
    }

    // Create the combination.
    Combination l_to_return = Combination(f_n, f_k, l_combination, a_index);

    // Deallocate data (after the combination is created, for it requires the data in this array).
    delete[] l_combination;

    return l_to_return;
}

/* Mutator of f_index_lexicographic, f_combination
*/
void Combination::SetCombination(unsigned int a_index)
{
    *this = GetCombAtIndex(a_index);
}

/* Mutator of f_index_lexicographic
*/
void Combination::SetIndex(unsigned int a_index)
{
    f_index_lexicographic = a_index;
}

/* Mutator of f_index_iteration_min, f_index_iteration_max
   * Sets the combination to the specified index.
*/
void Combination::SetMinMaxIterationIndexes(unsigned int a_index_iteration_min, unsigned int a_index_iteration_max)
{
    // Do not change the min/max iteration indexes if presently iterating.
    if (f_flag_iterating)
    {
        return;
    }

    // Neither index can be greater than the max index.
    if (a_index_iteration_min >= f_num_combinations || a_index_iteration_min >= f_num_combinations)
    {
        return;
    }

    // The min must be <= to the max.
    if (a_index_iteration_min > a_index_iteration_min)
    {
        return;
    }

    f_index_iteration_min = a_index_iteration_min;
    f_index_iteration_max = a_index_iteration_max;
}



/* Increment Operator (prefix)
*/
Combination& Combination::operator++()
{
    // Return if already at the highest combination.
    if (f_index_lexicographic == f_index_iteration_max)
    {
        if (f_flag_iterating)
        {
            SetIndex(f_index_iteration_max + 1);
        }

        return *this;
    }

    // The highest index of the group of n elements.
    unsigned int l_index_n_max = f_n - 1;

    // The highest index of a combination set (i.e. the highest index of f_combination).
    unsigned int l_index_k_max = f_k - 1;

    if (f_combination[l_index_k_max] < l_index_n_max)
    {
        ++f_combination[l_index_k_max];

        ++f_index_lexicographic;
    }
    else
    {
        for (int i = l_index_k_max - 1; i >= 0; --i)
        {
            unsigned int l_index_higher = i + 1;

            if (f_combination[i] + 1 == f_combination[l_index_higher])
            {
                continue;
            }

            // Assign the ith index of the combination's set.
            ++f_combination[i];

            // Make sure the indexes from i to l_index_k_max are consecutive.
            for (int j = i + 1; j <= l_index_k_max; ++j)
            {
                f_combination[j] = f_combination[i] + (j - i);
            }

            ++f_index_lexicographic;

            break;

        }

    }

    return *this;
}

/* Decrement Operator (postfix)
    * Still needs to be tested.
*/
Combination& Combination::operator--()
{
    // The lexographic index of the highest combination.
    unsigned int l_index_max = f_num_combinations - 1;

    // Return if already at the lowest possible combination.
    if (f_index_lexicographic == 0)
    {
        return *this;
    }

    // The highest index of the group of n elements.
    unsigned int l_index_n_max = f_n - 1;

    // The highest index of a combination set (i.e. the highest index of f_combination).
    unsigned int l_index_k_max = f_k - 1;

    // An index can only be decremented if its value post-decrement is greater than the value of the next lowest index.
    // If an index post-decrement is greater than the value of the next lowest index then it should be decremented.
    // If there is no lower index, the index should be decremented (assuming it's above 0).
    for (int i = l_index_k_max; i >= 0; --i)
    {
        unsigned int l_index_lower = i - 1;

        if (l_index_lower < 0) // If there is no lower index.
        {
            if (f_combination[i] > 0)
            {
                --f_combination[i];
            }

        }
        else if (f_combination[i] - 1 > f_combination[l_index_lower])
        {
            --f_combination[i];
        }
        else
        {
            continue;
        }

        --f_index_lexicographic;
        break;


    }

    return *this;
}

/* Indexer Operator (Accessor of f_combination)
*/
unsigned int Combination::operator[](unsigned int a_index) const
{
    unsigned int l_index_max = f_k - 1;

    if (a_index > l_index_max || a_index < 0)
    {
        throw std::range_error("The given index is out of valid bounds.");
    }

    return f_combination[a_index];
}

const Combination& Combination::operator*()
{
    return *this;
}

/* Assignment Operator
*/
Combination& Combination::operator=(const Combination& a_comb)
{
    if (this == &a_comb)
    {
        return *this;
    }

    unsigned int l_k_old = f_k;

    f_n = a_comb.f_n;
    f_k = a_comb.f_k;
    f_index_lexicographic = a_comb.f_index_lexicographic;
    f_num_combinations = a_comb.f_num_combinations;
    f_index_iteration_max = a_comb.f_index_iteration_max;
    f_index_iteration_min = a_comb.f_index_iteration_min;

    // If the size of the f_combination array has changed.
    if (f_k != l_k_old)
    {
        // Deallocate old data.
        delete[] f_combination;

        // Allocate new data.
        f_combination = new unsigned int[f_k]();
    }

    // Assign new combination.
    for (int i = 0; i < f_k; ++i)
    {
        f_combination[i] = a_comb.f_combination[i];
    }

    return *this;
}

/* Equivalency Operator
*/
bool Combination::operator==(const Combination& a_comb) const
{
    return (f_n == a_comb.f_n) && (f_k == a_comb.f_k) && (f_index_lexicographic == a_comb.f_index_lexicographic);
}

/* Equivalency Operator (alternate)
*/
bool Combination::operator==(std::vector<unsigned int> a_comb) const
{
    if (a_comb.size() != f_k)
    {
        return false;
    }

    for (int i = 0; i < f_k; ++i)
    {
        if (f_combination[i] != a_comb[i])
        {
            return false;
        }

    }

    return true;
}

/* Non-Equivalency Operator
*/
bool Combination::operator!=(const Combination& a_comb)
{
    return !(*this == a_comb);
}

/* Non-Equivalency Operator (alternate)
*/
bool Combination::operator!=(std::vector<unsigned int> a_comb) const
{
    return !(*this == a_comb);
}

/* Output Operator
*/
std::ostream& operator<<(std::ostream& a_ostream, const Combination a_comb)
{
    // e.g. {0,1,2}
    a_ostream << '{';
    for (int index_digit = 0; index_digit < a_comb.f_k; ++index_digit)
    {
        a_ostream << a_comb.f_combination[index_digit];

        // Don't add a comma if on the index's last digit.
        if (index_digit != a_comb.f_k - 1)
        {
            a_ostream << ',';
        }

    }
    a_ostream << '}';

    return a_ostream;
}


/* Static Utility Function
*/
int Combination::Comb(int a_n, int a_k)
{
    // Guard against fK being greater than fN (in which case there are 0 combs).
    if (a_k > a_n)
    {
        return 0;
    }

    if (a_n < 0 || a_k < 0)
    {
        return 0;
    }

    // The number of combinations.
    int l_comb_num = 1;

    // Pick the lowest 'k' value to make program more efficient.
    unsigned int lK = (a_k > a_n - a_k) ? a_n - a_k : a_k;

    for (int i = 1; i <= lK; ++i)
    {
        l_comb_num *= a_n - lK + i;
        l_comb_num /= i;
    }

    return l_comb_num;
}