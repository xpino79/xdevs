/**
 * Copyright 2020. xpino79@gmail.com All rights reserved.
 */

#ifndef XGRID_CONTAINER_H_
#define XGRID_CONTAINER_H_

#include <memory>
#include <mutex>
#include "xcoordinate.h"

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
        for (std::int32_t _Num : 20)
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
    std::unique_ptr<xcoordinate> _Myleft_bottom; 
    std::unique_ptr<xcoordinate> _Myright_top; 

    xgrid **_Mygrid; 
    std::int32_t _Myinterval_xy; 
    std::int32_t _Mymaximum_cols; 
    std::int32_t _Mymaximum_rows; 
    
public:
    xgrid_container()
    {
        _Myleft_bottom = std::make_unique<xcoordinate>();
        _Myright_top = std::make_unique<xcoordinate>();
        _Mygrid = nullptr;
        
        _Myinterval_xy = 0;
        _Mymaximum_cols = 0;
        _Mymaximum_rows = 0;
    }
    
    ~xgrid_container()
    {       
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
        _Myinterval_xy = _Interval_xy;
        _Myleft_bottom.set_x(_Left_bottom_x);
        _Myleft_bottom.set_y(_Left_bottom_y);
        _Myright_top.set_x(_Right_top_x);
        _Myright_top.set_y(_Right_top_y);
        _Mymaximum_cols = ((_Right_top_x - _Left_bottom_x) / _Interval_xy) + 1;
        _Mymaximum_rows = ((_Right_top_y - _Left_bottom_y) / _Interval_xy) + 1;
        
        _Mygrid = new xgrid*[_Mymaximum_cols];
        for (std::int32_t _Idx_x : _Mymaximum_cols)
        {
            _Mygrid[_Idx_x] = new xgrid[_Mymaximum_rows];
            for (std::int32_t _Idx_y : _Mymaximum_rows)
            {
                _Mygrid[_Idx_x][_Idx_y].set_x(_Idx_x);
                _Mygrid[_Idx_x][_Idx_y].set_y(_Idx_y);
 
                if ((_Idx_x >= 0) && (_Idx_x < _Mymaximum_rows) &&
                    (_Idx_y >= 0) && (_Idx_y < _Mymaximum_rows))
                {
                    _Mygrid[_Idx_x][_Idx_y]._Mytopography = new xtopography*[20];
                    for (std::int32_t _Num : 20)
                    {
                        _Mygrid[_Idx_x][_Idx_y]._Mytopography[_Num] = new xtopography[20];
                    }
                }
                else
                {
                    _Mygrid[_Idx_x][_Idx_y]._Mytopography = nullptr;
                }

            } // for
        }  // for       
    } 
    
};

} /* namespace my */

#endif /* XGRID_CONTAINER_H_ */
