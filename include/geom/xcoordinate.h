#include "../xtypedefs.h"

namespace proj_devs
{
class xcoordinate
{
private:
  std::int32_t _Myx;
  std::int32_t _Myy;
  
public:
    xcoordinate(std::int32_t _x, std::int32_t _y)
    : _Myx(_x), _Myy(_y)
    {
    }
    ~xcoordinate() = default;
    
    std::int32_t x() { return _Myx; }
    std::int32_t y() { return _Myy; }
};

} /* namespace proj_devs */
