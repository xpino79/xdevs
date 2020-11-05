#include <iostream>
#include <memory>
#include <execinfo.h>
#include <regex>
#include <limits.h>
#include <unistd.h>
 
namespace my
{

std::string get_exepath()
{
    char _val[PATH_MAX];
    ssize_t _len = readlink("/proc/self/exe", _val, PATH_MAX);
    return std::string(_val, (_len > 0) ? _len : 0);
}

std::string sh(std::string _cmd)
{
    std::array<char, 128> _buf;
    std::string _val;
    std::shared_ptr<FILE> _pipe(popen(_cmd.c_str(), "r"), ::pclose);
    if (!_pipe)
    {
        throw std::runtime_error("popen() failed!");
    }
    while (!feof(_pipe.get()))
    {
        if (fgets(_buf.data(), 128, _pipe.get()) != nullptr)
        {
            _val += _buf.data();
        }
    }
    return _val;
}

void print_stack_trace(void)
{
    void *_addrlist[1024];
    std::int32_t _addrlen = 0;
    char **_symbollist;

    _addrlen = backtrace(_addrlist, 1024);
    _symbollist = backtrace_symbols(_addrlist, _addrlen);

    std::regex _regex("\\[(.+)\\]");
    auto _filename = get_exepath();
    std::string _address = "";
    for (std::int32_t i = 1; i < _addrlen; i++)
    {
        std::string _symbol = _symbollist[i];
        std::smatch _match;
        if (std::regex_search(_symbol, _match, _regex))
        {
            std::string _tmp = _match[1];
            _address += " " + _tmp;
        }
    }
    
    auto r = sh("addr2line -e " + _filename + " -f -C " + _address);
    std::cerr << r << std::endl;
    free(_symbollist);
}

} // namespace my
