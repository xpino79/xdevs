/**
 * Copyright 2020. xpino79@gmail.com All rights reserved.
 */

#include "xpolygon.h"

namespace proj_devs
{
class xmulti_polygon
{
private:
    std::vector<std::unique_ptr<xpolygon>> _Mypolygons;
    
public:
    xmulti_polygon() = default;
    ~xmulti_polygon() = default;
    
    void clear()
    {
        this->_Mypolygons.clear();
    }
    bool empty()
    {
        this->_Mypolygons.empty();
    } 
    void set_wkt(const std::string &_WKT)
    {
        // WKT(Well-Known Text) Geometry
        // POLYGON((1 1,2 1,2 2,1 2,1 1))
        // MULTIPOLYGON(((1 1,2 1,2 2,1 2,1 1)),((3 3,3 5,5 5,5 3,3 3)))
        this->clear();
        
    }
    
    void push_back(std::unique_ptr<xpolygon> _Uptr)
    {
        this->_Mypolygons.push_back( std::move(_Uptr) );
    }
    
    std::float64_t area()
    {
        std::float64_t _Val = 0.0;
        for(auto &_Elem : _Mypolygons)
        {
            xpolygon *_Ptr = _Elem.get();
            _Val += _Ptr->area();
        }
        return _Val;        
    }
    std::float64_t length()
    {
        std::float64_t _Val = 0.0;
        for(auto &_Elem : _Mypolygons)
        {
            xpolygon *_Ptr = _Elem.get();
            _Val += _Ptr->length();
        }
        return _Val;     
    }
    
    bool within(std::int32_t _X, std::int32_t _Y)
    {
        bool _Val = false;
        for(auto &_Elem : _Mypolygons)
        {
            xpolygon *_Ptr = _Elem.get();
            if( _Ptr->within(_X, _Y))
            {
                _Val = true;
                break;
            }
        }
        return _Val;
    }
    
};

} /* namespace proj_devs */
