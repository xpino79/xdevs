/**
 * Copyright 2020. xpino79@gmail.com All rights reserved.
 */

#ifndef XGRID_CONTAINER_H_
#define XGRID_CONTAINER_H_

#include <memory>
#include <mutex>
#include <vector>
#include <cmath>
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
    std::vector<std::vector<std::unique_ptr<xtopography>>> _Mytopography;
 
public:
    xgrid()
    {
        _Myx = -1; 
        _Myy = -1;
    }
    ~xgrid()
    {

    }

    std::float64_t length(std::int32_t _Idx_x, std::int32_t _Idx_y)
    {
        return std::sqrt(std::pow(_Idx_x - _Myx, 2) + std::pow(_Idx_y - _Myy, 2));
    }

    std::int32_t x() { return _Myx; }
    std::int32_t y() { return _Myy; }
    std::vector<std::vector<std::unique_ptr<xtopography>>> &topography() { return _Mytopography; }
    void set_x(std::int32_t _X) { _Myx = _X; }
    void set_y(std::int32_t _Y) { _Myy = _Y; }
    void set_topography(std::int32_t _Width, std::int32_t _Height)
    {
        _Mytopography.resize(_Width);
        for (auto& _Elem : _Mytopography)
        {
            _Elem.resize(_Height);
            for (auto& _Topography : _Elem)
            {
                _Topography = std::make_unique<xtopography>();
            }
        }
    }
};

class xgrid_container
{
private:
    std::unique_ptr<xcoordinate> _Myleft_bottom; 
    std::unique_ptr<xcoordinate> _Myright_top; 

    std::vector<std::vector<std::unique_ptr<xgrid>>> _Mygrid; 
    std::int32_t _Myinterval_xy; 
    std::int32_t _Mymaximum_cols; 
    std::int32_t _Mymaximum_rows; 
    
public:
    xgrid_container()
    {
        _Myleft_bottom = std::make_unique<xcoordinate>();
        _Myright_top = std::make_unique<xcoordinate>();
        
        _Myinterval_xy = 0;
        _Mymaximum_cols = 0;
        _Mymaximum_rows = 0;
    }
    
    ~xgrid_container()
    {
    }
    
    void initialize(
        std::int32_t _Interval_xy, 
        std::int32_t _Left_bottom_x, std::int32_t _Left_bottom_y, 
        std::int32_t _Right_top_x, std::int32_t _Right_top_y
    )
    {
        _Myinterval_xy = _Interval_xy;
        _Myleft_bottom->set_x(_Left_bottom_x);
        _Myleft_bottom->set_y(_Left_bottom_y);
        _Myright_top->set_x(_Right_top_x);
        _Myright_top->set_y(_Right_top_y);
        
        // >>>>> EPSG:3857 좌표계에서 적도 포함한 사각형일경우 아래 계산 공식이 적용여부.
        _Mymaximum_cols = ((_Right_top_x - _Left_bottom_x) / _Interval_xy) + 1;
        _Mymaximum_rows = ((_Right_top_y - _Left_bottom_y) / _Interval_xy) + 1;
        
        _Mygrid.clear();
        _Mygrid.resize(_Mymaximum_cols);
        for (std::int32_t _Idx_x = 0; _Idx_x < _Mymaximum_cols; ++_Idx_x)
        {
            _Mygrid[_Idx_x].resize(_Mymaximum_rows);
            for (std::int32_t _Idx_y = 0; _Idx_y < _Mymaximum_rows; ++_Idx_y)
            {
                _Mygrid[_Idx_x][_Idx_y] = std::make_unique<xgrid>();
                _Mygrid[_Idx_x][_Idx_y]->set_x(_Idx_x);
                _Mygrid[_Idx_x][_Idx_y]->set_y(_Idx_y);

                if ((0 <= _Idx_x) && (_Idx_x < _Mymaximum_rows) &&
                    (0 <= _Idx_y) && (_Idx_y < _Mymaximum_rows))
                {
                    _Mygrid[_Idx_x][_Idx_y]->set_topography(20, 20);
                }
            } // for
        }  // for
    }

    // >>>>> to_grid_index 작명 변경 요청. 모호한 함수명칭임.
    std::tuple<std::int32_t, std::int32_t> to_index(std::int32_t _Pos_x, std::int32_t _Pos_y)
    {
        xcoordinate _Pos(_Pos_x, _Pos_y);

        // >>>>> EPSG:3857 좌표계에서 적도 포함한 사각형일경우 아래 계산 공식이 적용여부.
        if((*(_Myleft_bottom.get()) <= _Pos) && (_Pos <= *(_Myright_top.get())))
        {
            _Pos -= *(_Myleft_bottom.get());
            _Pos /= _Myinterval_xy;
        }
        else
        {
            _Pos.set_x(-1);
            _Pos.set_y(-1);
        }

        return std::tuple<std::int32_t, std::int32_t>(_Pos.x(), _Pos.y());
    }

    xgrid *find_grid(std::int32_t _Pos_x, std::int32_t _Pos_y)
    {
        std::int32_t _Idx_x;
        std::int32_t _Idx_y;

        std::tie(_Idx_x, _Idx_y) = to_index(_Pos_x, _Pos_y);

        xgrid *_Ptr = nullptr;
        if((0 <= _Idx_x) && (0 <= _Idx_y))
        {
            _Ptr = _Mygrid[_Idx_x][_Idx_y].get();
        }

        return _Ptr;
    }
    
    std::list<xgrid *> within_grid(std::int32_t _Pos_x, std::int32_t _Pos_y, std::int32_t _Range = 0)
    {
        std::list<xgrid *> _Val;
        
        xgrid *_Center_Ptr = find_grid( _Pos_x,  _Pos_y);
        if ( nullptr != _Center_Ptr )
        {
            if(0 == _Range)
            {
                _Val.push_back(_Center_Ptr);
            }
            else
            {

                xcoordinate _Start = xcoordinate(_Pos_x, _Pos_y) - _Range;
                xcoordinate _End = xcoordinate(_Pos_x, _Pos_y) + _Range;

                // >>>>> xcoordinate 클래스에 correction 함수는 일회성 함수. xcoordinate 클래스에 있을 필요성 판단
                // >>>>> xcoordinate 클래스를 사용하지 않고 구현.
                _Start.correction(*(_Myleft_bottom.get()), *(_Myright_top.get()));
                _End.correction(*(_Myleft_bottom.get()), *(_Myright_top.get()));

                std::int32_t _Start_idx_x;
                std::int32_t _Start_idx_y;
                std::int32_t _End_idx_x;
                std::int32_t _End_idx_y;
                
                std::tie(_Start_idx_x, _Start_idx_y) = to_index(_Start.x(), _Start.y());
                std::tie(_End_idx_x, _End_idx_y) = to_index(_End.x(), _End.y());

                std::cout << "max_idx: " << _Mymaximum_cols - 1 << ", " << _Mymaximum_rows - 1 << std::endl;
                std::cout << "start_idx: " << _Start_idx_x << ", " << _Start_idx_y << std::endl;
                std::cout << "end_idx: " << _End_idx_x << ", " << _End_idx_y << std::endl;

                // >>>>> 유지보수 힘든 코드 시작 , 단순한 코드로.
                if((0 > _Start_idx_x) || (0 > _Start_idx_y) ||
                   (0 > _End_idx_x) || ( 0 > _End_idx_y))
                {
                    std::cerr << "xgrid_container::to_index underflow (" << _Start.x() << ", " << _Start.y() << "), (" << _End.x() << ", " << _End.y() << ")" << std::endl;
                }
                else if((_Mymaximum_cols <= _Start_idx_x) || (_Mymaximum_rows <= _Start_idx_y) ||
                        (_Mymaximum_cols <= _End_idx_x) || (_Mymaximum_rows <= _End_idx_y))
                {
                    std::cerr << "xgrid_container::to_index overflow (" << _Start.x() << ", " << _Start.y() << "), (" << _End.x() << ", " << _End.y() << ")" << std::endl;
                }
                else
                {
                    std::float64_t _Idx_maxlen = ((double)_Range / (double)_Myinterval_xy) + 1.0;
                    _Idx_maxlen = std::sqrt(std::pow(_Idx_maxlen, 2));

                    for (int y = _Start_idx_y; y <= _End_idx_y; ++y)
                    {
                        for (int x = _Start_idx_x; x <= _End_idx_x; ++x)
                        {
                            if(_Center_Ptr->length(x, y) <= _Idx_maxlen)
                            {
                                std::cout << x << ", " << y << ": O" << std::endl;
                                xgrid *ptr = _Mygrid[x][y].get();
                                if(nullptr != ptr)
                                {
                                    _Val.push_back( ptr );
                                }
                            }
                            else
                            {
                                std::cout << x << ", " << y << ": X" << std::endl;
                            }
                        }
                    }
                }
                // <<<<< 유지보수 힘든 코드 끝
            }
            
        }
        return _Val;
    }
};

} /* namespace my */

#endif /* XGRID_CONTAINER_H_ */
