#include <memory>
#include <mutex>

class singleton
{
private:
    singleton();
    singleton(const singleton &) = delete; 
    singleton &operator=(const singleton &) = delete; 
    
    static std::unique_ptr<singleton> _Myinstance;
    static std::once_flag _Myonce_flag;
public:
    static singleton& instance();

};

