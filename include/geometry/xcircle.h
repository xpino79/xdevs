
/**
 * Copyright 2021. xpino79@gmail.com All rights reserved.
 *
 * @file xcircle.h
 * @date 2021. 01. 01.
 * @author xpino79@gmail.com
 * @brief 원 클래스 헤더파일
 */

#ifndef XCIRCLE_H_
#define XCIRCLE_H_

#include <cstdint>
#include <cmath>
#include <iostream>

namespace my
{
    /**
     * @class xcircle
     * @date 2021. 01. 01.
     * @author xpino79@gmail.com
     * @brief 원 클래스
     */
    class xcircle
    {
    private:
        std::int32_t _Myx{};
        std::int32_t _Myy{};
        double _Myr{};

    public:
        explicit xcircle(std::int32_t _Pos_x, std::int32_t _Pos_y, double _Radius)
            : _Myx(_Pos_x), _Myy(_Pos_y), _Myr(_Radius)
        {
        }
        ~xcircle() = default;

        std::int32_t x() const noexcept
        {
            return _Myx;
        }
        std::int32_t y() const noexcept
        {
            return _Myy;
        }
        double radius() const noexcept
        {
            return _Myr;
        }
        double diameter() const noexcept
        {
            return 2.0 * _Myr;
        }
        double circumference() const noexcept
        {
            return 3.14159 * diameter();
        }
        double area() const noexcept
        {
            return 3.14159 * _Myr * _Myr;
        }
        bool contains(std::int32_t _Pos_x, std::int32_t _Pos_y) const
        {
            bool _Inside = false;
            double _Distance = std::sqrt((_Myx - _Pos_x) * (_Myx - _Pos_x) + (_Myy - _Pos_y) * (_Myy - _Pos_y));
            if (_Distance <= _Myr)
            {
                _Inside = true;
            }
            return _Inside;
        }
        bool contains(const circle &_Right) const
        {
            bool _Inside = false;
            double _Distance = std::sqrt((_Myx - _Right._Myx) * (_Myx - _Right._Myx) + (_Myy - _Right._Myy) * (_Myy - _Right._Myy));
            if ((_Distance + _Right._Myr) <= _Myr)
            {
                _Inside = true;
            }
            return _Inside;
        }
        void print() const
        {
            std::cout << _Myx << " " << _Myy << " " << _Myr << std::endl;
        }
    };

} /* namespace my */

#endif /* XCIRCLE_H_ */
