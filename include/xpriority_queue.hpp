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

};
