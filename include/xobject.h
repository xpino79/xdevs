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
    virtual std::string name() = 0;
    virtual void set_name(std::string _Val) = 0;
    
};

class xground : public xobject
{
public:
    xground() = default;
    virtual ~xground() = default;
};
    
class xmaneuver : public xground
{
private:
    std::string _Myname;
public:
    xmaneuver() = default;
    virtual ~xmaneuver() = default;
    
    virtual void refresh() final 
    { 
        std::cout << this->key() << std::endl;
        std::cout << this->name() << std::endl;
    } 
    virtual std::string name() final 
    { 
        return this->_Myname; 
    }
    virtual void set_name(const std::string &_Val) final 
    { 
        this->_Myname = _Val; 
    }
    
};
class xsupport : public xground
{
public:
    xsupport() = default;
    virtual ~xsupport() = default;
    
    virtual void refresh() final {} 
};
    
}

