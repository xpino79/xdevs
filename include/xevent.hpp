#include "xtypedefs.h"

class xevent
{
private:
    double _Myta = 0.0; //< 이벤트 시간
public:
    xevent() = default;
    ~xevent() = default;
     
    diuble ta() { return _Myta; }
    set_ta(double _Val) { _Myta = _Val; }
    
    void run() {}
};
