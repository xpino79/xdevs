#ifndef XCOMPONENT_H_
#define XCOMPONENT_H_

namespace my {

class xcontent
{
private:
    std::int32_t _Mykey = 0;
    std::int32_t _Myparent = 0;
public:
    xcontent(std::int32_t _Key, std::int32_t _Parent)
        : _Mykey(_Key), _Myparent(_Parent)
    {
    }
};

class xcomponent
{
private:
 
public:
    xcomponent()
    {
    }
    ~xcomponent()
    {
    }
    
};

} // namespace my

#endif /* XCOMPONENT_H_ */
