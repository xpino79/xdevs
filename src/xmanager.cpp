#include "../include/xmanager.h"

namespace proj_devs
{
std::unique_ptr<xmanager> xmanager::_Myinstance;
std::once_flag xmanager::_Myonce_flag;

xmanager::xmanager()
{
}

xmanager& xmanager::instance()
{
    std::call_once(_Myonce_flag, []() {
        _Myinstance.reset(new xmanager);
    });
    return *(_Myinstance.get());
}
} /* namespace proj_devs */
