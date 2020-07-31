#include "../include/xtypedefs.h"

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
};

class xair : public xobject
{
public:
    xair() = default;
    virtual ~xair() = default;
};

class xsea : public xobject
{
public:
    xsea() = default;
    virtual ~xsea() = default;
};

class xground : public xobject
{
public:
    xground() = default;
    virtual ~xground() = default;
};
}

