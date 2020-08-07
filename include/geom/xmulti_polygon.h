/**
 * Copyright (C) 2020 xpino79@gmail.com
 * All rights reserved.
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
    virtual ~xmulti_polygon() = default;
    
    void push_back(std::unique_ptr<xpolygon>);
    
    std::float64_t area();
    std::float64_t length();
    
    bool empty();
    bool within(std::int32_t _x, std::int32_t _y);
    
};

} /* namespace proj_devs */
