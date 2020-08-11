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
     
    std::map<int32_t, std::shared_ptr<xobject>> _Myxobjects;
    
public:
    static xmanager& instance();
    static int32_t generate_unique_identifier();
     
    const std::map<int32_t, std::shared_ptr<xobject>>& xobjects();
     
    std::weak_ptr<xobject> insert( std::shared_ptr<xobject> _Uptr);
    
    void erase( std::int32_t _Key);
    
};  

// api
xmanager* get_xmanager_ptr();
        
} /* namespace my */


#endif /* XMANAGER_H_ */




