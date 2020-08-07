#include <memory>
#include <mutex>
#include <vector>

#include "xcoordinate.h"

namespace proj_devs
{
class xpolygon
{
private:
    std::vector<std::unique_ptr<xcoordinate>> _Myvertex;
    
public:
    xpolygon() = default;
    virtual ~xpolygon() = default;
};
