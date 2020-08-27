/**
 * Copyright 2020. xpino79@gmail.com All rights reserved.
 */

#ifndef XCOORDINATE_H_
#define XCOORDINATE_H_

#include <iostream>
#include <tuple>
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
    xcoordinate(std::int32_t _Pos_x, std::int32_t _Pos_y)
    : _Myx(_Pos_x), _Myy(_Pos_y)
    {
    }
    xcoordinate(const xcoordinate& _Off)
    : _Myx(_Off._Myx), _Myy(_Off._Myy)
    {
    }
    ~xcoordinate() 
    {
        std::cout << "~xcoordinate" << std::endl;
    }
    
    std::int32_t x() { return this->_Myx; }
    std::int32_t y() { return this->_Myy; }
    
    void set_x(std::int32_t _Pos_x) { this->_Myx = _Pos_x; }
    void set_y(std::int32_t _Pos_y) { this->_Myy = _Pos_y; }
   
    xcoordinate& operator+=(const xcoordinate& _Off) { _Myx += _Off._Myx; _Myy += _Off._Myy; return *this; }
    xcoordinate& operator-=(const xcoordinate& _Off) { _Myx -= _Off._Myx; _Myy -= _Off._Myy; return *this; }
    xcoordinate& operator*=(const xcoordinate& _Off) { _Myx *= _Off._Myx; _Myy *= _Off._Myy; return *this; }
    xcoordinate& operator/=(const xcoordinate& _Off) { _Myx /= _Off._Myx; _Myy /= _Off._Myy; return *this; }
 
    friend bool operator==(const xcoordinate& _Left, const xcoordinate& _Right) { return std::tie(_Left._Myy, _Left._Myy) == std::tie(_Right._Myy, _Right._Myy); }
    friend bool operator!=(const xcoordinate& _Left, const xcoordinate& _Right) { return !(_Left == _Right); }
 
    friend bool operator< (const xcoordinate& _Left, const xcoordinate& _Right) { return std::tie(_Left._Myy, _Left._Myy) < std::tie(_Right._Myy, _Right._Myy); }
    friend bool operator>=(const xcoordinate& _Left, const xcoordinate& _Right) { return !(_Left < _Right); }
    friend bool operator> (const xcoordinate& _Left, const xcoordinate& _Right) { return   _Right < _Left ; }
    friend bool operator<=(const xcoordinate& _Left, const xcoordinate& _Right) { return !(_Right < _Left); }
 
    xcoordinate& operator*=(const std::int32_t& _Off) { _Myy *= _Off; _Myy *= _Off; return *this; }
    xcoordinate& operator/=(const std::int32_t& _Off) { _Myy /= _Off; _Myy /= _Off; return *this; }
  
};

xcoordinate operator+(const xcoordinate& _Left, const xcoordinate& _Right) { return xcoordinate(_Left) += _Right; }
xcoordinate operator-(const xcoordinate& _Left, const xcoordinate& _Right) { return xcoordinate(_Left) -= _Right; }
xcoordinate operator*(const xcoordinate& _Left, const xcoordinate& _Right) { return xcoordinate(_Left) *= _Right; }
xcoordinate operator/(const xcoordinate& _Left, const xcoordinate& _Right) { return xcoordinate(_Left) /= _Right; }
xcoordinate operator*(const std::int32_t& _Left, const xcoordinate& _Right) { return xcoordinate(_Right) *= _Left; }
xcoordinate operator*(const xcoordinate>& _Left, const std::int32_t& _Right) { return xcoordinate(_Left) *= _Right; }
xcoordinate operator*(const xcoordinate& _Left, const std::int32_t& _Right) { return xcoordinate(_Left) *= _Right; }
    
} /* namespace my */


#endif /* XCOORDINATE_H_ */

