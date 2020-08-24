#ifndef COMPONENT_H_
#define COMPONENT_H_

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


} // namespace my

#endif /* COMPONENT_H_ */
