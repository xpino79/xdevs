/**
 * Copyright 2020. xpino79@gmail.com. All rights reserved.
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

    void clear()
    {
        this->_Mycoordinates.clear();
    }    
    bool empty()
    {
        this->_Mycoordinates.empty();
    }
    void set_wkt(const std::string &_WKT)
    {
        // WKT(Well-Known Text) Geometry
        // POLYGON((1 1,2 1,2 2,1 2,1 1))
        // MULTIPOLYGON(((1 1,2 1,2 2,1 2,1 1)),((3 3,3 5,5 5,5 3,3 3)))
        this->clear();
        
    }
    
    xcoordinate *get_coordinateN (std::size_t _Num)
    {
    }

    void push_back(std::int32_t _X, std::int32_t _Y)
    {
        this->_Mycoordinates.push_back( std::make_unique<proj_devs::xcoordinate>(_X, _Y) );
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

    bool within(std::int32_t _x, std::int32_t _y)
    {
    }
 
};
    
} /* namespace proj_devs */
