#include "Utility.h"

#include <time.h> /* time */
#include <stdio.h> /* printf, scanf, puts, NULL */

#include <stdexcept>
#include <sstream>

bool Utility::s_srandIsInitialized = false;

Utility::Utility()
{
    if (! s_srandIsInitialized)
    {
        srand((unsigned int)time(NULL)); // initialize random seed
        s_srandIsInitialized = true;
    }
}

double Utility::selectRandomBetween(double lower, double upper) const
{
    double result;
    do
    {
        result = (upper - lower) * ( (double)rand() / (double)RAND_MAX ) + lower;
    } while (result == upper);
    
    return result;
}

size_t Utility::selectRandomElementWrtRatio(const std::vector<double>& vec) const
{
    double sum = 0;
    
    for (auto it = vec.begin(), itEnd = vec.end(); it != itEnd; ++it)
    {
        sum += *it;
    }
    
    double rnd = selectRandomBetween(0.0, sum);
    
    double counter = 0.0;
    size_t size = vec.size();
    for (size_t i = 0; i < size; ++i)
    {
        counter += vec[i];
        if (rnd < counter)
            return i;
    }
    
    std::ostringstream oss;
    for (size_t i = 0; i < size; ++i)
    {
        oss << "[" << i << "] = " << vec[i] << ", ";
    }
    oss << "rnd = " << rnd;
    
    throw std::logic_error("Utility::selectRandomElementWrtRatio(): Error in calculations: " + oss.str());
    return vec.size(); // invalid, should not get here
}