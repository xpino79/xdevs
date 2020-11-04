#ifndef XLOGGER_H_
#define XLOGGER_H_

#include <memory>
#include <mutex>

// https://download-ib01.fedoraproject.org/pub/epel/8/Everything/x86_64/Packages/s/
// https://github.com/gabime/spdlog/tree/v1.x/include/spdlog

#include "spdlog/spdlog.h"

namespace my
{

class xlogger 
{
private:
    xlogger() = default;
    xlogger(const xlogger &) = delete;
    xlogger &operator=(const xlogger &) = delete;

    static std::shared_ptr<spdlog::logger> _Mylogger;
    static std::once_flag _Myonce_flag;

public:
    ~xlogger() = default;
    static std::shared_ptr<spdlog::logger>& instance();
    static void release_instance();
};

// macros			
#define TRACE(...) ::xlogger::instance()->trace(__VA_ARGS__)
#define INFO(...) ::xlogger::instance()->info(__VA_ARGS__)
#define WARN(...) ::xlogger::instance()->warn(__VA_ARGS__)
#define ERROR(...) ::xlogger::instance()->error(__VA_ARGS__)
#define FATAL(...) ::xlogger::instance()->fatal(__VA_ARGS__)

} // namespace my

#endif /* XLOGGER_H_ */
