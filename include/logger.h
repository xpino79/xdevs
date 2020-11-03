#ifndef LOGGER_H_
#define LOGGER_H_

#include <memory>
#include <mutex>

#include "spdlog/spdlog.h"

namespace my
{

    class logger 
    {
    private:
        logger() = default;
        logger(const logger &) = delete;
        logger &operator=(const logger &) = delete;
 
        static std::shared_ptr<spdlog::logger> _Mylogger;
        static std::once_flag _Myonce_flag;

    public:
        ~logger() = default;
        static std::shared_ptr<spdlog::logger> instance();
        static void release_instance();
    };

} // namespace my

#endif /* LOGGER_H_ */
