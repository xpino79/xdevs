
#include <iostream>

#include "logger.h"
#include "spdlog/sinks/rotating_file_sink.h"

namespace my {


    std::shared_ptr<spdlog::logger> logger::_Mylogger;
    std::once_flag logger::_Myonce_flag;

    /**
     * @brief 인스턴스 반환
     * @return
     */
    std::shared_ptr<spdlog::logger> logger::instance()
    {
        std::call_once(_Myonce_flag, []() {
            spdlog::flush_every(std::chrono::seconds(1));

            auto max_size = 1048576 * 5;
            auto max_files = 3;
            _Mylogger = spdlog::rotating_logger_mt("log", "logs/log", max_size, max_files, true);
            _Mylogger->set_level(spdlog::level::trace);

            atexit(release_instance);
        });
        return _Mylogger;
    }
    /**
     * @brief 인스턴스 초기화
     * 
     */
    void logger::release_instance()
    {
        spdlog::shutdown();
    }


}
