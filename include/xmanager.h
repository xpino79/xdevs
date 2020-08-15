/**
 * Copyright 2020. xpino79@gmail.com All rights reserved.
 */

#ifndef XMANAGER_H_
#define XMANAGER_H_

#include <memory>
#include <mutex>
#include <map>
#include <algorithm>

#include "xobject.h"

namespace my
{
        
void assign_priority( std::int32_t _Key);

class xmanager
{
private:
    xmanager();
    xmanager(const xmanager &) = delete; 
    xmanager &operator=(const xmanager &) = delete; 
    
    static std::unique_ptr<xmanager> _Myinstance;
    static std::once_flag _Myonce_flag;
    static int32_t _Myunique_identifier;
     
    std::map<int32_t, std::unique_ptr<xobject>> _Myxobjects;
    
public:
    static xmanager& instance();
    static int32_t generate_unique_identifier();
     
    const std::map<int32_t, std::unique_ptr<xobject>>& xobjects();
    xobject *insert( std::unique_ptr<xobject> _Uptr);    
    void erase( std::int32_t _Key);
    xobject *find( std::int32_t _Key ) 
    {
        auto _Iter = _Myxobjects.find(_Key);
        return ( _Iter != _Myxobjects.end() ) ? _Iter->second.get() : nullptr;
    }   

    // MISRA_CPP_07_05_04 함수의 직, 간접적 재귀호출은 사용 금지
    // >> 재귀 호출(recursive call)이란 함수 내부에서 함수가 자기 자신을 또다시 호출하는 행위를 의미합니다.
    void assign_priority_number(my::xobject *_Ptr)
    {
        /*
        for (int32_t _Key : _Ptr->submodels())
        { 
            my::xobject *_Vptr = this->find(_Key);
            _Vptr->set_priority( generate_unique_identifier() );
            if ( !_Vptr->submodels().empty() )
            {
                assign_priority_number(_Vptr);
            }
        }
        */
        
        std::for_each( _Ptr->submodels().begin(), _Ptr->submodels().end(), my::assign_priority );
            
    }        

        
    
    
};  
        
void assign_priority( std::int32_t _Key)
{
    my::xobject *_Vptr = xmanager::instance().find(_Key);
    _Vptr->set_priority( xmanager::instance().generate_unique_identifier() );
    if ( !_Vptr->submodels().empty() )
    {
        xmanager::instance().assign_priority_number(_Vptr);
    }
}

} /* namespace my */


#endif /* XMANAGER_H_ */




