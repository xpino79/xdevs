#include "xpriority_queue.hpp"
#include "xevent.hpp"

class xevent_manager
{
private:
    /// 싱글톤
    xevent_manager() = default;

    xpriority_queue _Myqueue;
public:
    
    /// 이벤트 등록 함수
    /// 이벤트 실행 함수
    /// 이벤트 취소 함수

};
