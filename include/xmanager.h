#include <memory>
#include <mutex>

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
public:
    static xmanager& instance();

};  
} /* namespace proj_devs */




