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

template <typename T>
bool circle_line_intersect(T x1, T y1, T x2, T y2, T cx, T cy, T cr ) 
{
    T dx = x2 - x1;
    T dy = y2 - y1;
    T a = (dx * dx) + (dy * dy);
    T b = 2.0 * (dx * (x1 - cx) + dy * (y1 - cy));
    T c = (cx * cx) + (cy * cy);
    c += (x1 * x1) + (y1 * y1);
    c -= (2.0 * ((cx * x1) + (cy * y1)));
    c -= (cr * cr);
    T bb4ac = (b * b) - (4.0 * a * c);

    // return false  No collision
    // return true Collision
    return (bb4ac >= 0);

    /*
    if ((std::fabs(bb4ac) < std::numeric_limits<T>::epsilon) || (bb4ac < 0)) 
    {   
        return false; // No collision
    }
    T mu1 = (-b + std::sqrt(bb4ac)) / (2.0 * a);
    T mu2 = (-b - std::sqrt(bb4ac)) / (2.0 * a); 
    T sx1 = x1 + mu1 * (x2 - x1);
    T sy1 = y1 + mu1 * (y2 - y1);
    T sx2 = x1 + mu2 * (x2 - x1);
    T sy2 = y1 + mu2 * (y2 - y1);    
    */
    
}
    
}

#endif /* UTILITY_H_ */
