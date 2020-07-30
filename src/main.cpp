#include <string>
#include <map>
#include <list>

#include "../include/typedefs.h"

// MISRA_CPP_2008 
std::int32_t main(std::int32_t argc, char_t *argv[])
{
      std::int32_t k = 1;
      std::map<std::int32_t, std::int32_t> _Map;
      _Map.insert(std::make_pair(key, 0));

      // insert return
      auto _Pair = _Map.insert(std::make_pair(key, 0));
      if (!_Pair.second) {
            // error
      }
      
      // erase return
      if (0==_Map.erase( k )) {
            // error
      }
      
      return 1;
}
