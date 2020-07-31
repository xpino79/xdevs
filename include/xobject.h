namespace proj_devs
{
class xobject
{
public:
    xobject() = default;
    virtual ~xobject() = default;
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

