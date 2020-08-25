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
        xgrid *_Ptr = nullptr;
        // 구현 <위치X, 위치Y> 
        // _Ptr = _Mygrid_container->find_grid(_Pos_x, _Pos_y);
        return _Ptr;
    }
    std::list<xgrid *> within_grid(std::int32_t _Pos_x, std::int32_t _Pos_y, std::int32_t _Range = 0)
    {
        std::list<xgrid *> _Val;
        // 구현
        return _Val;
    }
    void push_ground_data(std::int32_t _Handle, std::int32_t _Pos_x, std::int32_t _Pos_y)
    {
        // 방안1. 구현 <객체구분자, 객체식별자, 위치X, 위치Y>
        // _Mygrid_container->push_griddata(1, _Handle, _Pos_x, _Pos_y);
        
        // 방안2. 구현 <객체구분자, 객체식별자>
        // xgrid *_Ptr = _Mygrid_container->find_grid(_Pos_x, _Pos_y);
        // _Ptr->push_data(1, _Handle);
    }
    void erase_ground_data(std::int32_t _Handle, std::int32_t _Pos_x, std::int32_t _Pos_y)
    {
        // 방안1. 구현 <객체구분자, 객체식별자, 위치X, 위치Y>
        // _Mygrid_container->erase_griddata(1, _Handle, _Pos_x, _Pos_y);
        
        // 방안2. 구현 <객체구분자, 객체식별자>
        // xgrid *_Ptr = _Mygrid_container->find_grid(_Pos_x, _Pos_y);
        // _Ptr->erase_data(1, _Handle);
    }    
};

} /* namespace my */

#endif /* XGRID_MANAGER_H_ */
