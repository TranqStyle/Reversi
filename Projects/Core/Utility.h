#ifndef UTILITY_H
#define UTILITY_H

#include <stdlib.h> /* srand, rand */

#include <vector>
#include <set>

class Utility
{
public:
    Utility();

    template <typename T>
    T selectRandomElement(const std::vector<T>& vec) const
    {
        size_t index = rand() % vec.size();
    
        return vec[index];
    }

    template <typename T>
    T selectRandomElement(const std::set<T>& s) const
    {
        size_t index = rand() % s.size();

        auto it = s.cbegin();
        std::advance(it, index);
        return *it;
    }
    
    double selectRandomBetween(double lower, double upper) const;
    size_t selectRandomElementWrtRatio(const std::vector<double>& vec) const; // returns index
    
private:
    static bool s_srandIsInitialized;
};

#endif // UTILITY_H

