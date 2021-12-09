#include <thread>
#include <future>
#include <vector>
#include <unordered_map>
#include <iostream>

bool __compar(std::size_t _x, std::size_t _j)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return (_x < _j);
}

std::int32_t main()
{
    std::cout << "run" << std::endl;
    auto _begin = std::chrono::system_clock::now();

    // std::vector<std::future<bool>> _futures;
    std::unordered_map<std::size_t, std::future<bool>> _futures;
    std::size_t _x = 1;
    for (std::size_t _i = 0; _i < 1000; ++_i)
    {
        // _futures.push_back(std::async(
        _futures.emplace(_i, std::async(
                                 std::launch::async,
                                 [](std::size_t _x, std::size_t _i)
                                 {
                                     return __compar(_x, _i);
                                 },
                                 _x, _i));
    }

    for (auto &_future : _futures)
    {
        // std::cout << " >>> " << _future.get() << std::endl;
        // _future.get();

        std::cout << " >>> " << _future.first << ", " << _future.second.get() << std::endl;
        // _future.first;
        // _future.second.get();
    }

    auto _end = std::chrono::system_clock::now();
    // std::chrono::microseconds _microseconds = std::chrono::duration_cast<std::chrono::microseconds>(_end - _begin);
    // std::chrono::milliseconds _milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(_end - _begin);
    std::chrono::seconds _seconds = std::chrono::duration_cast<std::chrono::seconds>(_end - _begin);
    // std::chrono::minutes _minutes = std::chrono::duration_cast<std::chrono::minutes>(_end - _begin);
    // std::chrono::hours _hours = std::chrono::duration_cast<std::chrono::hours>(_end - _begin);

    std::cout << "end: " << _seconds.count() << std::endl;
    return EXIT_SUCCESS;
}
