/**
 * Copyright 2020. xpino79@gmail.com. All rights reserved.
 */

#include "../xtypedefs.h"

namespace proj_devs
{
class xcoordinate
{
private:
  std::int32_t _Myx;
  std::int32_t _Myy;
  
public:
    xcoordinate(std::int32_t _X, std::int32_t _Y)
    : _Myx(_X), _Myy(_Y)
    {
    }
    ~xcoordinate() = default;
    
    std::int32_t x() { return this->_Myx; }
    std::int32_t y() { return this->_Myy; }
};

} /* namespace proj_devs */
