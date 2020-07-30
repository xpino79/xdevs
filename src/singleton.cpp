#include "../include/singleton.h"

namespace proj_devs
{
std::unique_ptr<singleton> singleton::_Myinstance;
std::once_flag singleton::_Myonce_flag;

singleton::singleton()
{
}

singleton& singleton::instance()
{
    std::call_once(_Myonce_flag, []() {
        _Myinstance.reset(new singleton);
    });
    return *(_Myinstance.get());
}
} /* namespace proj_devs */
