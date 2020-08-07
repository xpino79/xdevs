#include <memory>
#include <mutex>
#include <vector>

#include "xcoordinate.h"

namespace proj_devs
{
class xpolygon
{
private:
    std::vector<std::unique_ptr<xcoordinate>> _Mycoordinates;
    
public:
    xpolygon() = default;
    virtual ~xpolygon() = default;
    
    void push_back(std::int32_t _x, std::int32_t _y);
    void push_back(std::unique_ptr<xcoordinate>);
    
    std::float64_t area();
    std::float64_t length();
    
    bool empty();
    bool within(std::int32_t _x, std::int32_t _y);
 
};
