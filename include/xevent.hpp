#include "xtypedefs.h"

class xevent
{
private:
    std:: float64_t _Myta = 0.0; //< 이벤트 시간
public:
    xevent() = default;
    virtual ~xevent() = default;
     
    std::float64_t ta() { return _Myta; }
    set_ta(std::float64_t _Val) { _Myta = _Val; }
    
    virtual void run() = 0; /// 이벤트 실행 순수 가상한수
};
