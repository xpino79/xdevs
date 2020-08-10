#ifndef UTILITY_H_
#define UTILITY_H_

namespace my
{

#include <string>
#include <sstream>
#include <cmath>
#include "typedefs.h"

template<typename T>
static bool nearly_equal(const T t, const T u)
{
    return (std::nextafter(t, std::numeric_limits<T>::lowest()) <= u)
                && (std::nextafter(t, std::numeric_limits<T>::max()) >= u);
}

template <typename T>
static T to_numeric(const std::string& _str)
{
    T t = 0;
    std::istringstream ( _str ) >> t;
    return t;
}

template <typename T, typename U>
auto numeric_add(T t, U u)
{
    return t + u;
}

template <typename T, typename U>
auto numeric_minus(T t, U u)
{
    return t - u;
}

template <typename T, typename U>
auto numeric_muliply(T t, U u)
{
    return t * u;
}

template <typename T>
T numeric_division(T t, T u)
{
    T retval(0);
    if(false == std::isnan(t / static_cast<float64_t>(u)))
    {
        retval = t / u;
    }
    return retval;
}

}

#endif /* UTILITY_H_ */
