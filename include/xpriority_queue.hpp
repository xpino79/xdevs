class xcompare
{
public:
    bool operator()(const xevent *_Right, const xevent *_Left)
    {
        return _Right.ta() > _Left.ta();
    }

};

class xpriority_queue
{

};
