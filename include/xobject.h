#include <iostream>
#include "xtypedefs.h"

namespace proj_devs
{
class xobject
{
private:
    int32_t _Mykey = 0;
public:
    xobject() = default;
    virtual ~xobject() = default;
    int32_t key() const { return _Mykey;}
    void set_key(int32_t _Key) { _Mykey = _Key;}
    
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
    virtual ~xground() = default;
    
    virtual std::string name() const final 
    { 
        return this->_Myname; 
    }
    virtual void set_name(const std::string &_Val) final 
    { 
        this->_Myname = _Val; 
    }
};
    
class xmaneuver : public xground
{
private:
    std::int32_t _Mycourse = 90;
    
public:
    xmaneuver() = default;
    virtual ~xmaneuver() = default;
    
    virtual void refresh() final 
    { 
        std::cout << "xmaneuver::refresh start " << std::endl;
        std::cout << this->key() << std::endl;
        std::cout << this->name() << std::endl;
        std::cout << this->course() << std::endl;
        std::cout << "xmaneuver::refresh end " << std::endl;
    }
    virtual std::int32_t course() const final
    {
        return this->_Mycourse; 
    }
    virtual void set_course(std::int32_t _Val) final
    {
        this->_Mycourse = _Val; 
    }
};
class xsupport : public xground
{
public:
    xsupport() = default;
    virtual ~xsupport() = default;
    
    virtual void refresh() final 
    { 
        std::cout << "xsupport::refresh start " << std::endl;
        std::cout << this->key() << std::endl;
        std::cout << this->name() << std::endl;
        std::cout << "xsupport::refresh end " << std::endl;
    }
    virtual std::int32_t course() const final
    {
        return 0; 
    }
    virtual void set_course(std::int32_t _Val) final default;
};
    
}

