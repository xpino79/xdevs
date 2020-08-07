/**
 * Copyright (C) 2020 xpino79@gmail.com
 * All rights reserved.
 */

#include "../include/xobject.h"

namespace proj_devs
{
int32_t xobject::key() const 
{ 
    return this->_Mykey;
}
void xobject::set_key(int32_t _Key) 
{ 
    this->_Mykey = _Key;
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
    std::cout << "xmaneuver::refresh start " << std::endl;
    std::cout << this->key() << std::endl;
    std::cout << this->name() << std::endl;
    std::cout << this->course() << std::endl;
    std::cout << "xmaneuver::refresh end " << std::endl;
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
    std::cout << "xsupport::refresh start " << std::endl;
    std::cout << this->key() << std::endl;
    std::cout << this->name() << std::endl;
    std::cout << "xsupport::refresh end " << std::endl;
}
std::int32_t xsupport::course() const
{
    return 0; 
}
void xsupport::set_course(std::int32_t _Val)
{ 
}

}
