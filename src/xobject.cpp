/**
 * Copyright 2020. xpino79@gmail.com All rights reserved.
 */

#include "../include/xobject.h"

namespace my
{
int32_t xobject::key() const 
{ 
    return this->_Mykey;
}
int32_t xobject::priority() const 
{ 
    return this->_Mypriority;
}
    
void xobject::set_key(int32_t _Key) 
{ 
    this->_Mykey = _Key;
}    
void xobject::set_priority(int32_t _Priority) 
{ 
    this->_Mypriority = _Priority;
}

    
std::string xground::name() const 
{ 
    return this->_Myname; 
}
void xground::set_name(const std::string &_Val) 
{ 
    this->_Myname = _Val; 
}

void xmaneuver::refresh() 
{ 
    std::cout << ">>>>> xmaneuver::refresh " << std::endl;
    std::cout << " - key: " << this->key() << std::endl;
    std::cout << " - priority: " << this->priority() << std::endl;
    std::cout << " - name: " << this->name() << std::endl;
    std::cout << " - course: " << this->course() << std::endl;
 
}
std::int32_t xmaneuver::course() const
{
    return this->_Mycourse; 
}
void xmaneuver::set_course(std::int32_t _Val)
{
    this->_Mycourse = _Val; 
}
    
void xsupport::refresh() 
{ 
    std::cout << ">>>>> xsupport::refresh " << std::endl;
    std::cout << " - key: " << this->key() << std::endl;
    std::cout << " - priority: " << this->priority() << std::endl;
    std::cout << " - name: " << this->name() << std::endl;
    std::cout << " - course: " << this->course() << std::endl;
    
}
std::int32_t xsupport::course() const
{
    return 0; 
}
void xsupport::set_course(std::int32_t _Val)
{ 
}

} /* namespace my */
