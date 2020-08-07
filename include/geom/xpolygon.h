/**
 * Copyright (C) 2020 xpino79@gmail.com
 * All rights reserved.
 */

#include <memory>
#include <mutex>
#include <vector>

#include "xcoordinate.h"

namespace proj_devs
{
class xpolygon
{
private:
    std::vector<std::unique_ptr<xcoordinate>> _Mycoordinates;
    
public:
    xpolygon() = default;
    ~xpolygon() = default;
    
    void push_back(std::int32_t _x, std::int32_t _y)
    {
        this->_Mycoordinates.push_back( std::make_unique<proj_devs::xcoordinate>(_x, _y) );
    }
    void push_back(std::unique_ptr<xcoordinate> _Uptr)
    {
        this->_Mycoordinates.push_back( std::move(_Uptr) );
    }
    
    std::float64_t area()
    {
    }
    std::float64_t length();
    {
    }
    
    bool empty()
    {
        this->_Mycoordinates.empty();
    }
    bool within(std::int32_t _x, std::int32_t _y)
    {
    }
 
};
    
} /* namespace proj_devs */
