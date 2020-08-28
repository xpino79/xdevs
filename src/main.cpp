/**
 * Copyright 2020. xpino79@gmail.com All rights reserved.
 */

#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <omp.h> // 병렬 

// MISRA_CPP_03_09_02 기본 숫자 타입 대신 크기와 부호를 나타내는 typedef를 사용해야 함
#include "../include/xobject_manager.h"
#include "../include/xgrid_manager.h"
#include "../include/utility/xpointer_cast.hpp"
#include "../include/geometry/xmulti_polygon.h"

std::int32_t main(std::int32_t argc, std::char_t *argv[])
{
    // if(false)
    {
        // within_grid 테스트
        std::int32_t _Interval_xy = 10000;
        std::int32_t _Left_bottom_x = 726029;
        std::int32_t _Left_bottom_y = 1464252;
        std::int32_t _Right_top_x = 1383896;
        std::int32_t _Right_top_y = 2559450;
        
        std::ignore = _Interval_xy;
        std::ignore = _Left_bottom_x;
        std::ignore = _Left_bottom_y;
        std::ignore = _Right_top_x;
        std::ignore = _Right_top_y;

        my::xgrid_manager::instance().within_grid(_Left_bottom_x + 10000, _Left_bottom_y, 10000);

        my::xgrid_manager::instance().push_ground_data(1, _Left_bottom_x, _Left_bottom_y);
        my::xgrid_manager::instance().push_ground_data(2, _Left_bottom_x, _Left_bottom_y);

        my::xgrid_manager::instance().erase_ground_data(3, _Left_bottom_x, _Left_bottom_y);
        my::xgrid_manager::instance().push_ground_data(2, _Left_bottom_x, _Left_bottom_y);
        // return 1;
    }
    { 
        // MISRA_CPP_18_04_01 동적 힙 메모리 할당은 사용하면 안됨
        my::xobject *_Pptr = my::xobject_manager::instance().insert(std::make_unique<my::xmaneuver>());
        
        for (int i=0; i<100000; ++i)
        {
            my::xobject *_Ptr = my::xobject_manager::instance().insert(std::make_unique<my::xmaneuver>());
            _Pptr->insert_submodel( _Ptr->key() );
        }
        
        // MISRA_CPP_07_05_04 함수의 직, 간접적 재귀호출은 사용 금지 
        my::xobject_manager::instance().assign_priority_number(_Pptr);
        
        std::int32_t _Priority = 100000;
        my::xobject *_Vptr = nullptr;
        
        // >>>>> 병렬 처리 속도 테스트 
        #pragma omp parallel for
        for (auto _Iter = _Pptr->submodels().begin(); _Iter != _Pptr->submodels().end(); ++_Iter )
        {
            my::xobject *_Tmp = my::xobject_manager::instance().find(*_Iter);
            if (_Priority > _Tmp->priority() )
            {
                _Vptr = _Tmp;
                _Priority = _Tmp->priority();
            }
        }
        std::cout << "#1 "<< _Vptr->key() << ", " _Priority << std::endl;        
    }
 
    { // MISRA_CPP_05_02_03 상위(base) 클래스를 하위(derived)클래스로 변환하는 것은 다형(polymorphic) 타입 간에 이루어져서는 안됨
        for (auto &_Elem : my::xobject_manager::instance().xobjects())
        { 
            // down casting, cross casting 해결방안 ?
            my::xground *_Ptr = my::dynamic_pointer_cast<my::xground>(_Elem.second.get());
            if (nullptr != _Ptr)
            {
                // MISRA_CPP_10_03_01 상속 계층을 따라 각 virtual function 정이는 하나씩만 존재해야 함
                // 하위(derived)클래스의 함수를 상위(base)클래스 pure virtual 로 만든다.
                _Ptr->refresh();
            }
        }       
    }
    { // MISRA_CPP_00_01_07 함수 반환 값 미사용 금지
          std::int32_t _Key = 1;
          std::map<std::int32_t, std::int32_t> _Map;
          _Map.insert(std::make_pair(_Key, 0));
          auto _Pair = _Map.insert(std::make_pair(_Key, 0));
          if (!_Pair.second) {
                // error
          }
          if (0==_Map.erase( _Key )) {
                // error
          }
    }
    { // MISRA_CPP_00_01_07 함수 반환 값 미사용 금지
          std::int32_t _Key = 1;
          std::list<std::int32_t> _List;
          _List.push_back(_Key);
          auto _Iter = std::find(_List.begin(), _List.end(), _Key);
          if ( _Iter != _List.end() )
          {
                _Iter = _List.erase( _Iter );
                // _Iter 변수 >>> MISRA_CPP_00_01_06 변수 값 할당 후에 한 번도 사용하지 않는 프로세스 금지 
                // 해결방안 ?
          }
    }

     {// POLYGON || MULTIPOLYGON
        /*
        std::unique_ptr<my::xpolygon> _Puptr = std::make_unique<my::xpolygon>();
         
        _Puptr->push_back(0, 0);
        _Puptr->push_back(2, 0);
        _Puptr->push_back(2, 2);
        _Puptr->push_back(0, 2);
        _Puptr->push_back(0, 0);
         // _Puptr->read_wkt("POLYGON((0 0,2 0,2 2,0 2,0 0))");
        std::cout << "POLYGON area: " << _Puptr->area() << std::endl;
        std::cout << "POLYGON length: " << _Puptr->length() << std::endl;
        std::cout << "POLYGON within: " << _Puptr->within(10, 10) << ", " << _Puptr->within(0, 0) << ", " << _Puptr->within(1, 1) << std::endl;
        
        std::unique_ptr<my::xmulti_polygon> _MPuptr = std::make_unique<my::xmulti_polygon>();
        _MPuptr->push_back( std::move(_Puptr) );
        std::cout << "MULTIPOLYGON area: " << _MPuptr->area() << std::endl;
        std::cout << "MULTIPOLYGON length: " << _MPuptr->length() << std::endl;
        std::cout << "MULTIPOLYGON within: " << _MPuptr->within(10, 10) << ", " << _MPuptr->within(0, 0) << ", " << _MPuptr->within(1, 1) << std::endl;      
        */
         
    }
  
    std::cout << ">>>>> application quit " << std::endl;
 
    return 1;
}
