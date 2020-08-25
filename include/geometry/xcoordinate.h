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
    xcoordinate operator-=(xcoordinate &_Right)
    {
        return operator-(_Right);
    }
    xcoordinate operator/(std::int32_t &_Right)
    {
        std::int32_t _X = _Myx / _Right;
        std::int32_t _Y = _Myy / _Right;
        
        return xcoordinate(_X, _Y);
    }
    xcoordinate operator/=(std::int32_t &_Right)
    {
        return operator/(_Right);
    }
};

} /* namespace my */

#endif /* XCOORDINATE_H_ */

