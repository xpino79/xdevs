/**
 * Copyright 2020. xpino79@gmail.com All rights reserved.
 */

#ifndef XCOORDINATE_H_
#define XCOORDINATE_H_

#include <iostream>
#include "../xtypedefs.h"

namespace my
{
class xcoordinate
{
private:
    std::int32_t _Myx;
    std::int32_t _Myy;
  
public:
    xcoordinate()
    : _Myx(0), _Myy(0)
    {
    }
    xcoordinate(std::int32_t _X, std::int32_t _Y)
    : _Myx(_X), _Myy(_Y)
    {
    }
    ~xcoordinate() 
    {
        std::cout << "~xcoordinate" << std::endl;
    }
    
    std::int32_t x() { return this->_Myx; }
    std::int32_t y() { return this->_Myy; }
    
    void set_x(std::int32_t _X) { this->_Myx = _X; }
    void set_y(std::int32_t _Y) { this->_Myy = _Y; }

    void correction(xcoordinate &_Left_bottom, xcoordinate &_Right_top)
    {
        if(_Myx < _Left_bottom.x())
        {
            _Myx = _Left_bottom.x();
        }
        if(_Myy < _Left_bottom.y())
        {
            _Myy = _Left_bottom.y();
        }

        if(_Right_top.x() < _Myx)
        {
            _Myx = _Right_top.x();
        }
        if(_Right_top.y() < _Myy)
        {
            _Myy = _Right_top.y();
        }
    }
    
    bool operator<=(xcoordinate &_Right)
    {
        return (_Myx <= _Right.x() && _Myy <= _Right.y());
    }

    xcoordinate operator-(xcoordinate &_Right)
    {
        std::int32_t _X = _Myx - _Right.x();
        std::int32_t _Y = _Myy - _Right.y();
        
        return xcoordinate(_X, _Y);
    }
    xcoordinate operator-(std::int32_t &_Right)
    {
        std::int32_t _X = _Myx - _Right;
        std::int32_t _Y = _Myy - _Right;
        
        return xcoordinate(_X, _Y);
    }
    void operator-=(xcoordinate &_Right)
    {
        _Myx -= _Right.x();
        _Myy -= _Right.y();
    }

    xcoordinate operator+(std::int32_t &_Right)
    {
        std::int32_t _X = _Myx + _Right;
        std::int32_t _Y = _Myy + _Right;
        
        return xcoordinate(_X, _Y);
    }
    void operator+=(std::int32_t &_Right)
    {
        _Myx += _Right;
        _Myy += _Right;
    }

    xcoordinate operator/(std::int32_t &_Right)
    {
        std::int32_t _X = _Myx / _Right;
        std::int32_t _Y = _Myy / _Right;
        
        return xcoordinate(_X, _Y);
    }
    void operator/=(std::int32_t &_Right)
    {
        _Myx /= _Right;
        _Myy /= _Right;
    }
};

} /* namespace my */

#endif /* XCOORDINATE_H_ */

