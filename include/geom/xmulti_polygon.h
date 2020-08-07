#include "xpolygon.h"

namespace proj_devs
{
class xmulti_polygon
{
private:
    std::vector<std::unique_ptr<xpolygon>> _Mypolygons;
    
public:
    xmulti_polygon() = default;
    virtual ~xmulti_polygon() = default;
};
