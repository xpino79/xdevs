/**
 * Copyright 2020. xpino79@gmail.com All rights reserved.
 */

#ifndef XMANAGER_H_
#define XMANAGER_H_

#include <memory>
#include <mutex>
#include <map>

#include "xobject.h"

namespace my
{
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
    
    void assign_priority_number(my::xobject *_Ptr)
    {
        for (auto &_Elem : _Ptr->submodels())
        { 
            my::xobject *_Vptr = _Elem.second.get();
            _Vptr->set_priority( generate_unique_identifier() );
            if ( !_Vptr->submodels().empty() )
            {
                assign_priority_number(_Vptr);
            }
        }
    }
    
    
};  

// api
xmanager* get_xmanager_ptr();
        
} /* namespace my */


#endif /* XMANAGER_H_ */




