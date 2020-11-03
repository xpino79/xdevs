#ifndef XLOGGER_H_
#define XLOGGER_H_

#include <memory>
#include <mutex>

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
    static std::shared_ptr<spdlog::logger> instance();
    static void release_instance();
};

} // namespace my

#endif /* XLOGGER_H_ */
