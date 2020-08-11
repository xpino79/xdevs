/**
 * Copyright 2020. xpino79@gmail.com All rights reserved.
 */

#ifndef XOBJECT_H_
#define XOBJECT_H_

#include <iostream>
#include <memory>
#include "xtypedefs.h"

namespace my
{
class xobject
{
private:
    int32_t _Mykey = 0;
    my::xobject* _Myparent = nullptr;
    
public:
    xobject() = default;
    virtual ~xobject() 
    { 
        std::cout << ">>>>> xobject::~xobject " << std::endl;
    }
    int32_t key() const;
    void set_key(int32_t _Key);
    
    my::xobject* parent() { return _Myparent; }
    void set_parent(my::xobject* _Parent) { _Myparent = _Parent; }
    
    // MISRA_CPP_10_03_01 상속 계층을 따라 각 virtual function 정이는 하나씩만 존재해야 함.
    // MISRA_CPP_10_03_03 재선언되는 base클래스의 함수가 pure virtual일 때만 pure virtual함수로 재선언 할 수 있음. 
    virtual void refresh() = 0;
    
    // xground - pure virtual
    virtual std::string name() const = 0;
    virtual void set_name(const std::string &_Val) = 0;
    
    // xmaneuver - pure virtual
    virtual std::int32_t course() const = 0;
    virtual void set_course(std::int32_t _Val) = 0;
    
};

class xground : public xobject
{
private:
    std::string _Myname;
    
public:
    xground() = default;
    virtual ~xground() 
    { 
        std::cout << ">>>>> xground::~xground " << std::endl;
    }
    
    virtual std::string name() const final;
    virtual void set_name(const std::string &_Val) final;
};
    
class xmaneuver : public xground
{
private:
    std::int32_t _Mycourse = 90;
    
public:
    xmaneuver() = default;
    virtual ~xmaneuver() 
    { 
        std::cout << ">>>>> xmaneuver::~xmaneuver " << std::endl;
    }
    
    virtual void refresh() final;
    virtual std::int32_t course() const final;
    virtual void set_course(std::int32_t _Val) final;
};
class xsupport : public xground
{
public:
    xsupport() = default;
    virtual ~xsupport() 
    { 
        std::cout << ">>>>> xsupport::~xsupport " << std::endl;
    }
    
    virtual void refresh() final;
    
    // TODO xobject 클래스의 pure virtual 함수로 인한 불필요한 함수 선언
    virtual std::int32_t course() const final;
    virtual void set_course(std::int32_t _Val) final;
};
    
} /* my */

#endif /* AAA_H_ */

