#include "xtypedefs.h"

namespace proj_devs
{
class xobject
{
private:
    int32_t _Mykey;
public:
    xobject() = default;
    virtual ~xobject() = default;
    int32_t key() const { return _Mykey;}
    void set_key(int32_t _Key) { _Mykey = _Key;}
    
    // MISRA_CPP_10_03_01 상속 계층을 따라 각 virtual function 정이는 하나씩만 존재해야 함.
    // MISRA_CPP_10_03_03 재선언되는 base클래스의 함수가 pure virtual일 때만 pure virtual함수로 재선언 할 수 있음. 
    virtual void refresh() = 0;
};

class xair : public xobject
{
public:
    xair() = default;
    virtual ~xair() = default;
    // MISRA_CPP_10_03_02 virtual 함수를 상속 받은 함수에 virtual 속성을 명시해야 함.
    virtual void refresh() final {} 
};

class xsea : public xobject
{
public:
    xsea() = default;
    virtual ~xsea() = default;
    
    virtual void refresh() final {} 
};

class xground : public xobject
{
public:
    xground() = default;
    virtual ~xground() = default;
    
    virtual void refresh() final {} 
};
}

