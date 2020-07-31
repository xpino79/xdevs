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
    
const std::map<int32_t, std::unique_ptr<xobject>>& xmanager::xobjects()
{
    return _Myxobjects;
}

void xmanager::insert( std::unique_ptr<xobject> _Ptr)
{
    auto _Pair = xobjects.insert(std::make_pair(_Ptr->ket(), std::move(_Ptr)));
    if (!_Pair.second) {
        // error
    }
}

void xmanager::erase( std::int32_t _Key)
{
    if (0 = xobjects.erase(_Key))
    {
        // error
    }
}
    
} /* namespace proj_devs */
