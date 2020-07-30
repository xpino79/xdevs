#include <string>
#include <map>
#include <list>

// MISRA_CPP_03_09_02 기본 숫자 타입 대신 크기와 부호를 나타내는 typedef를 사용해야 함
#include "../include/typedefs.h"

std::int32_t main(std::int32_t argc, char_t *argv[])
{
      std::int32_t _Key = 1;
      std::map<std::int32_t, std::int32_t> _Map;
      std::list<std::int32_t> _List;
      
      _Map.insert(std::make_pair(_Key, 0));
      _List.push_back(_Key);

      { // MISRA_CPP_00_01_07 함수 반환 값 미사용 금지
            auto _Pair = _Map.insert(std::make_pair(key, 0));
            if (!_Pair.second) {
                  // error
            }
            if (0==_Map.erase( _Key )) {
                  // error
            }
      }
      { // MISRA_CPP_00_01_07 함수 반환 값 미사용 금지
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
