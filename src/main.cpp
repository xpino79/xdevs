#include <string>
#include <map>
#include <list>

 
// MISRA_CPP_03_09_02 기본 숫자 타입 대신 크기와 부호를 나타내는 typedef를 사용해야 함
#include "../include/xmanager.h"

std::int32_t main(std::int32_t argc, char_t *argv[])
{
    { // MISRA_CPP_18_04_01 동적 힙 메모리 할당은 사용하면 안됨 
        api_devs::xobject *_Ptr = api_devs::xmanager::instance().insert( std::make_unique<api_devs::xair>() );
        if (nullptr != _Ptr)
        {
            // something
        }
    }
    { // MISRA_CPP_05_02_03 상위(base) 클래스를 하위(derived)클래스로 변환하는 것은 다형(polymorphic) 타입 간에 이루어져서는 안됨
        for (auto &_Elem : api_devs::xmanager::instance().xobjects())
        { 
            // api_devs::xair *_Ptr = std::dynamic_cast<api_devs::xair *>(_Elem.second.get());
            // _Ptr->refresh();
            // down casting, cross casting 해결방안 ?
            // 하위(derived)클래스의 함수를 상위(base)클래스 pure virtual 로 만든다.
            api_devs::xobject *_Ptr = _Elem.second.get();
            _Ptr->refresh();
        }
    }
    { // MISRA_CPP_00_01_07 함수 반환 값 미사용 금지
          std::int32_t _Key = 1;
          std::map<std::int32_t, std::int32_t> _Map;
          _Map.insert(std::make_pair(_Key, 0));
          auto _Pair = _Map.insert(std::make_pair(key, 0));
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
  
 
    return 1;
}
