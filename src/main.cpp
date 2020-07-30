#include <string>
#include <map>
#include <list>

// MISRA_CPP_03_09_02 기본 숫자 타입 대신 크기와 부호를 나타내는 typedef를 사용해야 함
#include "../include/typedefs.h"

std::int32_t main(std::int32_t argc, char_t *argv[])
{
      std::int32_t k = 1;
      std::map<std::int32_t, std::int32_t> _Map;
      _Map.insert(std::make_pair(key, 0));

      // MISRA_CPP_00_01_07 함수 반환 값 미사용 금지 
      auto _Pair = _Map.insert(std::make_pair(key, 0));
      if (!_Pair.second) {
            // error
      }
      // MISRA_CPP_00_01_07 함수 반환 값 미사용 금지 
      if (0==_Map.erase( k )) {
            // error
      }
      
      return 1;
}
