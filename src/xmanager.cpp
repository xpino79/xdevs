#include "../include/xmanager.h"

namespace proj_devs
{
std::unique_ptr<xmanager> xmanager::_Myinstance;
std::once_flag xmanager::_Myonce_flag;
int32_t xmanager::_Myunique_identifier;
    
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

int32_t xmanager::generate_unique_identifier()
{
    return ++_Myunique_identifier;
}
    
const std::map<int32_t, std::unique_ptr<xobject>>& xmanager::xobjects()
{
    return this->_Myxobjects;
}

xobject *xmanager::insert( std::unique_ptr<xobject> _Uptr)
{
    xobject *_Ptr = _Uptr.get();
    _Ptr->set_key( generate_unique_identifier() );
    
    auto _Pair = this->xobjects.insert(std::make_pair(_Uptr->key(), std::move(_Uptr)));
    if (!_Pair.second) {
        // error
        _Ptr = nullptr;
    }
    return _Ptr;
}

void xmanager::erase( std::int32_t _Key)
{
    if (0 = this->xobjects.erase(_Key))
    {
        // error
    }
}

// api
xmanager* get_xmanager_ptr()
{
    return xmanager::instance();
}
    
} /* namespace proj_devs */
