#ifndef XGRID_MANAGER_H_
#define XGRID_MANAGER_H_

#include <list>
#include "../include/geometry/xgrid_container.h"

namespace my {

class xgrid_manager
{
private:
    xgrid_manager()
    {
        _Mygrid_container = std::make_unique<xgrid_container>();
        
        // 초기화 호출방안 검토
        std::int32_t _Interval_xy = 0;
        std::int32_t _Left_bottom_x = 0; 
        std::int32_t _Left_bottom_y = 0; 
        std::int32_t _Right_top_x = 0;
        std::int32_t _Right_top_y = 0;

        // 기존 값으로 초기화 테스트
        _Interval_xy = 10000;
        _Left_bottom_x = 726029;
        _Left_bottom_y = 1464252;
        _Right_top_x = 1383896;
        _Right_top_y = 2559450;
            
        _Mygrid_container->initialize(
            _Interval_xy, 
            _Left_bottom_x, _Left_bottom_y, 
            _Right_top_x, _Right_top_y);
    }
    
    xgrid_manager(const xgrid_manager &) = delete; 
    xgrid_manager &operator=(const xgrid_manager &) = delete; 
    
    static std::unique_ptr<xgrid_manager> _Myinstance;
    static std::once_flag _Myonce_flag;
    
    std::unique_ptr<xgrid_container> _Mygrid_container;

public:
    static xgrid_manager &instance();
          
    xgrid *find_grid(std::int32_t _Pos_x, std::int32_t _Pos_y)
    {
        // 구현 <위치X, 위치Y>
        return _Mygrid_container->find_grid(_Pos_x, _Pos_y);
    }
    std::list<xgrid *> within_grid(std::int32_t _Pos_x, std::int32_t _Pos_y, std::int32_t _Range = 0)
    {
        // 구현
        return _Mygrid_container->within_grid(_Pos_x, _Pos_y, _Range);
    }
    void push_ground_data(std::int32_t _Handle, std::int32_t _Pos_x, std::int32_t _Pos_y)
    {
        // 방안1. 구현 <객체구분자, 객체식별자, 위치X, 위치Y>
        _Mygrid_container->push_griddata(1, _Handle, _Pos_x, _Pos_y);
        
        // 방안2. 구현 <객체구분자, 객체식별자>
        // xgrid *_Ptr = _Mygrid_container->find_grid(_Pos_x, _Pos_y);
        // _Ptr->push_data(1, _Handle);
    }
    void erase_ground_data(std::int32_t _Handle, std::int32_t _Pos_x, std::int32_t _Pos_y)
    {
        // 방안1. 구현 <객체구분자, 객체식별자, 위치X, 위치Y>
        _Mygrid_container->erase_griddata(1, _Handle, _Pos_x, _Pos_y);
        
        // 방안2. 구현 <객체구분자, 객체식별자>
        // xgrid *_Ptr = _Mygrid_container->find_grid(_Pos_x, _Pos_y);
        // _Ptr->erase_data(1, _Handle);
    }    
};

} /* namespace my */

#endif /* XGRID_MANAGER_H_ */
