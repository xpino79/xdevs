/**
 * Copyright 2020. xpino79@gmail.com All rights reserved.
 */

#include <string>
#include <map>
#include <list>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <omp.h> // 병렬 

// MISRA_CPP_03_09_02 기본 숫자 타입 대신 크기와 부호를 나타내는 typedef를 사용해야 함
#include "../include/xobject_manager.h"
#include "../include/xgrid_manager.h"
#include "../include/utility/xpointer_cast.hpp"
#include "../include/geometry/xmulti_polygon.h"
// #include "../include/xparallel.h"

// compilers
#if defined(__GNUC__)
    #if defined(__MINGW32__) || defined(__MINGW64__)
        #define COMPILER "MinGW GCC %d.%d.%d"
    #else
        #define COMPILER "GCC %d.%d.%d"
    #endif
#endif

#if defined(_MSC_VER)
    #define COMPILER "Microsoft C / Visual C++ compiler %d.%d"
    #define COMP_VERSION _MSC_VER / 100, _MSC_VER % 100
#endif

std::int32_t main(std::int32_t argc, std::char_t *argv[])
{
 
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
        assert( _Pptr != nullptr );
     
        for (int i=0; i<10; ++i)
        {
            my::xobject *_Ptr = my::xobject_manager::instance().insert(std::make_unique<my::xmaneuver>());
            _Pptr->insert_submodel( _Ptr->key() );
        }
        
        // MISRA_CPP_07_05_04 함수의 직, 간접적 재귀호출은 사용 금지 
        my::xobject_manager::instance().assign_priority_number(_Pptr);

        // >>>>> std::map, std::vector 병렬처리 테스트
        // _My_tbb_parallel_for();
        
        // return 1;
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
                // [[maybe_unused]] auto _UNUSED = _List.erase( _Iter );
                (void)_List.erase( _Iter );
          }
    }

    {// POLYGON || MULTIPOLYGON

        std::unique_ptr<my::xpolygon> _Puptr = std::make_unique<my::xpolygon>();
         
        _Puptr->push_back(0, 0);
        _Puptr->push_back(2, 0);
        _Puptr->push_back(2, 2);
        _Puptr->push_back(0, 2);
        _Puptr->push_back(0, 0);
        std::cout << "POLYGON area: " << _Puptr->area() << std::endl;
        std::cout << "POLYGON length: " << _Puptr->length() << std::endl;
        std::cout << "POLYGON within: " << _Puptr->within(10, 10) << ", " << _Puptr->within(0, 0) << ", " << _Puptr->within(1, 1) << std::endl;
        std::cout << "POLYGON intersects: " << _Puptr->intersects(1, 2, 1) << std::endl; 
        std::int32_t _Centroid_x = 0;
        std::int32_t _Centroid_y = 0;
        _Puptr->get_centroid(&_Centroid_x, &_Centroid_y);
        std::cout << "POLYGON centroid: " << _Centroid_x << ", " << _Centroid_y << std::endl;
     
        std::unique_ptr<my::xmulti_polygon> _MPuptr = std::make_unique<my::xmulti_polygon>();
        _MPuptr->push_back( std::move(_Puptr) );
        std::cout << "MULTIPOLYGON area: " << _MPuptr->area() << std::endl;
        std::cout << "MULTIPOLYGON length: " << _MPuptr->length() << std::endl;
        std::cout << "MULTIPOLYGON within: " << _MPuptr->within(10, 10) << ", " << _MPuptr->within(0, 0) << ", " << _MPuptr->within(1, 1) << std::endl;      
    
    }
  
    std::cout << ">>>>> application quit " << std::endl;
 
    return 1;
}
