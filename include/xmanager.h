#include <memory>
#include <mutex>
#include <map>

#include "xtypedefs.h"

namespace proj_devs
{
class xmanager
{
private:
    xmanager();
    xmanager(const xmanager &) = delete; 
    xmanager &operator=(const xmanager &) = delete; 
    
    static std::unique_ptr<xmanager> _Myinstance;
    static std::once_flag _Myonce_flag;
    std::map<int32_t, std::unique_ptr<xobject>> _Myxobjects;
    
public:
    static xmanager& instance();
    const std::map<int32_t, std::unique_ptr<xobject>>& xobjects();

};  
} /* namespace proj_devs */




