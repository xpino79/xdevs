/**
 * Copyright 2021. xpino79@gmail.com All rights reserved.
 *
 * @file circle.h
 * @date 2021. 01. 01.
 * @author xpino79@gmail.com
 * @brief 원 클래스 헤더파일
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include <cstdint>
#include <cmath>
#include <limits>
#include <iostream>

// https://skmagic.tistory.com/313

namespace my
{
    /**
     * @class circle
     * @date 2021. 01. 01.
     * @author xpino79@gmail.com
     * @brief 원 클래스
     */
    class circle
    {
    private:
        std::int32_t _Myx{};
        std::int32_t _Myy{};
        double _Myr{};

    public:
        explicit circle(std::int32_t _Pos_x, std::int32_t _Pos_y, double _Radius)
            : _Myx(_Pos_x), _Myy(_Pos_y), _Myr(_Radius)
        {
        }
        ~circle() = default;

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
            // 원의 중심에서 x y의 변화량 산출
            // 원의 중심과 점과의 거리
            double _Distance = std::sqrt((_Myx - _Pos_x) * (_Myx - _Pos_x) + (_Myy - _Pos_y) * (_Myy - _Pos_y));
            // 원의 중심부터 점과의 거리가 원의 반지름보다 크면 충돌이 아니다
            if (_Distance <= _Myr)
            {
                _Inside = true;
            }
            return _Inside;
        }
        // 한점이 부채꼴 범위 내 존재 여부
        // 부채꼴 중심각, 좌우 범위
        bool contains(std::int32_t _Pos_x, std::int32_t _Pos_y, std::int32_t _Direction, std::int32_t _Range) const
        {
            // https://rangsub.tistory.com/15
            // https://neoplanetz.tistory.com/entry/C-%EB%91%90-%EB%B2%A1%ED%84%B0%EC%9D%98-%EA%B0%81-%EA%B5%AC%ED%95%98%EA%B8%B0Calculate-degree-between-two-vectors
            bool _Inside = false;
            return _Inside;
        }
        
        bool contains(const circle &_Right) const
        {
            bool _Inside = false;
            double _Distance = std::sqrt((_Myx - _Right._Myx) * (_Myx - _Right._Myx) + (_Myy - _Right._Myy) * (_Myy - _Right._Myy));
            // 원의 중심간의 가리가 두 원의 반지름 합보다 크다면 충돌이 아니다
            if ((_Distance + _Right._Myr) <= _Myr)
            {
                _Inside = true;
            }
            return _Inside;
        }
        bool intersects(std::int32_t _Begin_x, std::int32_t _Begin_y, std::int32_t _End_x, std::int32_t _End_y) const noexcept
        {
            double dx = _End_x - _Begin_x;
            double dy = _End_y - _Begin_y;
            double a = dx * dx + dy * dy;
            double b = 2.0 * (dx * (_Begin_x - _Myx) + dy * (_Begin_y - _Myy));
            double c = _Myx * _Myx + _Myy * _Myy;
            c += _Begin_x * _Begin_x + _Begin_y * _Begin_y;
            c -= 2.0 * (_Myx * _Begin_x + _Myy * _Begin_y);
            c -= _Myr * _Myr;
            double bb4ac = b * b - 4.0 * a * c;

            if ((std::fabs(bb4ac) < std::numeric_limits<double>::epsilon()) || (bb4ac < 0))
            {
                return false; 
            }
            /*
            double mu1 = (-b + std::sqrt(bb4ac)) / (2.0 * a);
            double mu2 = (-b - std::sqrt(bb4ac)) / (2.0 * a); 
            std::int32_t b1x = _Begin_x + mu1 * (_End_x - _Begin_x);
            std::int32_t b1y = _Begin_y + mu1 * (_End_y - _Begin_y);
            std::int32_t b2x = _Begin_x + mu2 * (_End_x - _Begin_x);
            std::int32_t b2y = _Begin_y + ㅕmu2 * (_End_y - _Begin_y);   
            std::cout << " > " << b1x << ", " << b1y << ", " << b2x << ", " << b2y << std::endl;    
            */
            return true;
        }
        void print() const
        {
            std::cout << _Myx << " " << _Myy << " " << _Myr << std::endl;
        }
    };

} /* namespace my */

#endif /* CIRCLE_H_ */
