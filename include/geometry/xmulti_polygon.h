/**
 * Copyright 2020. xpino79@gmail.com All rights reserved.
 */

#ifndef XMULTI_POLYGON_H_
#define XMULTI_POLYGON_H_

#include "xpolygon.h"

namespace my
{
class xmulti_polygon
{
private:
    std::vector<std::unique_ptr<xpolygon>> _Mypolygons;
    
public:
    xmulti_polygon() = default;
    ~xmulti_polygon()
    {
        std::cout << "~xmulti_polygon" << std::endl;
    }
    
    void clear()
    {
        this->_Mypolygons.clear();
    }
    bool empty()
    {
        return this->_Mypolygons.empty();
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
    
    bool contains(std::int32_t _X, std::int32_t _Y)
    {
        bool _Val = false;
        for(auto &_Elem : _Mypolygons)
        {
            xpolygon *_Ptr = _Elem.get();
            if( _Ptr->contains(_X, _Y))
            {
                _Val = true;
                break;
            }
        }
        return _Val;
    }
    
};

} /* namespace my */

#endif /* XMULTI_POLYGON_H_ */
