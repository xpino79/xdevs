#include "xpriority_queue.hpp"
#include "xevent.hpp"

class xevent_manager
{
private:
    xevent_manager() = default;
    xpriority_queue _Myqueue;

public:
    static xobject_manager& instance()
    {
    }
    /// 이벤트 등록 함수
    /// 이벤트 실행 함수
    /// 이벤트 취소 함수

};