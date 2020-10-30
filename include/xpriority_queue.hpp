#include <queue>
#include <vector>

class xcompare
{
public:
    bool operator()(const xevent *_Right, const xevent *_Left)
    {
        return _Right.ta() > _Left.ta();
    }

};

class xpriority_queue : public std::priority_queue<xevent *, std::vector<xevent *>, xcompare >
{
public:
    /// 검색 함수
    /// 추가 함수
};
