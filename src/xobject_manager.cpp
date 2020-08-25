/**
 * Copyright 2020. xpino79@gmail.com All rights reserved.
 */

#include "../include/xobject_manager.h"

namespace my
{
std::unique_ptr<xobject_manager> xobject_manager::_Myinstance;
std::once_flag xobject_manager::_Myonce_flag;
int32_t xobject_manager::_Myunique_identifier;

void _Myassign_priority( std::int32_t _Key)
{
    my::xobject *_Ptr = xobject_manager::instance().find(_Key);
    _Ptr->set_priority( xobject_manager::instance().generate_unique_identifier() );
    if ( !_Ptr->submodels().empty() )
    {
        // xobject_manager::instance().assign_priority_number( _Ptr );
        // >> 재귀 호출(recursive call)이란 함수 내부에서 함수가 자기 자신을 또다시 호출하는 행위를 의미합니다.
        std::for_each( _Ptr->submodels().begin(), _Ptr->submodels().end(), my::_Myassign_priority );
    }
}
  
xobject_manager::xobject_manager()
{
}

xobject_manager& xobject_manager::instance()
{
    std::call_once(_Myonce_flag, []() {
        _Myinstance.reset(new xobject_manager);
    });
    return *(_Myinstance.get());
}

int32_t xobject_manager::generate_unique_identifier()
{
    return ++_Myunique_identifier;
} 
const std::map<int32_t, std::unique_ptr<xobject>>& xobject_manager::xobjects()
{
    return this->_Myxobjects;
}
 
xobject *xobject_manager::insert( std::unique_ptr<xobject> _Uptr)
{
    xobject *_Ptr = _Uptr.get();
    if (0==_Uptr->key())
    {
        _Ptr->set_key( generate_unique_identifier() );
        _Ptr->set_name( std::to_string(_Uptr->key()));
    }
    auto _Pair = this->_Myxobjects.insert(std::make_pair(_Uptr->key(), std::move(_Uptr)));
    if (!_Pair.second) {
        // error
        _Ptr = nullptr;
    }
    return _Ptr;
}
void xobject_manager::erase( std::int32_t _Key)
{
    std::cout << ">>>>> xobject_manager::erase " << std::endl;
    std::cout << " - key " << _Key << std::endl;
    if (0 == this->_Myxobjects.erase(_Key))
    {
        // error
    }
}


} /* namespace proj_devs */
