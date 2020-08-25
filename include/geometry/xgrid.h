/**
 * Copyright 2020. xpino79@gmail.com All rights reserved.
 */

#ifndef XGRID_H_
#define XGRID_H_

#include "../xcoordinate.h"

namespace my {

class xtopography
{
public:
    xtopography() {}
    ~xtopography() {}
};

class xgrid
{
private:
    std::int32_t _Myx; 
    std::int32_t _Myy; 
    xtopography **_Mytopography; 
 
public:
    xgrid()
    {
        _Myx = -1; 
        _Myy = -1; 
        _Mytopography = nullptr; 
    }
    ~xgrid()
    {
        for (std::int32_t _Num : _Mymaximum_cols)
        {
            delete[] _Mytopography[_Num];
            _Mytopography[_Num] = nullptr;
        }
        delete[] _Mytopography;
        _Mytopography = nullptr;
    }

    std::int32_t x() { return _Myx; }
    std::int32_t y() { return _Myy; }
    void set_x(std::int32_t _X) { _Myx = _X; }
    void set_y(std::int32_t _Y) { _Myy = _Y; }
};

class xgrid_container
{
private:
    xcoordinate *_Myleft_bottom; 
    xcoordinate *_Myright_top; 

    xgrid **_Mygrid; 
    std::int32_t _Myinterval_xy; 
    std::int32_t _Mymaximum_cols; 
    std::int32_t _Mymaximum_rows; 
    
public:
    xgrid_container()
    {
        _Myleft_bottom = nullptr;
        _Myright_top = nullptr;
        _Mygrid = nullptr;
        
        _Myinterval_xy = 0;
        _Mymaximum_cols = 0;
        _Mymaximum_rows = 0;
    }
    ~xgrid_container()
    {
        delete _Myleft_bottom;
        delete _Myright_top;
        
        for (std::int32_t _Num : _Mymaximum_cols)
        {
            delete[] _Mygrid[_Num];
        }
        delete[] _Mygrid;
    }
    void initialize(
        std::int32_t _Interval_xy, 
        std::int32_t _Left_bottom_x, std::int32_t _Left_bottom_y, 
        std::int32_t _Right_top_x, std::int32_t _Right_top_y
    )
    {
    }
    
};

} /* namespace my */

#endif /* XGRID_H_ */
