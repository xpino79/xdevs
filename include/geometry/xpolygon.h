/**
 * Copyright 2020. xpino79@gmail.com All rights reserved.
 */
#ifndef XPOLYGON_H_
#define XPOLYGON_H_

#include <algorithm>
#include <cmath>
#include <memory>
#include <mutex>
#include <vector> 
#include "xcoordinate.h"

namespace my
{
class xpolygon
{
private:
    std::vector<std::unique_ptr<xcoordinate>> _Mycoordinates;

public:
    xpolygon() = default;
    ~xpolygon()
    {
        std::cout << "~xpolygon" << std::endl;
    }
    void clear()
    {
        this->_Mycoordinates.clear();
    }
    bool empty()
    {
        return this->_Mycoordinates.empty();
    }
    xcoordinate *get_coordinateN(std::size_t _Num)
    {
        xcoordinate *_Ptr = nullptr;
        // Notice that the first element has a position of 0 (not 1).
        if (this->_Mycoordinates.size() > _Num)
        {
            _Ptr = this->_Mycoordinates.at(_Num).get();
        }
        return _Ptr;
    }

    void push_back(std::int32_t _x, std::int32_t _y)
    {
        this->_Mycoordinates.push_back(std::make_unique<my::xcoordinate>(_x, _y));
    }
    void push_back(std::unique_ptr<xcoordinate> _Uptr)
    {
        this->_Mycoordinates.push_back(std::move(_Uptr));
    }

    std::float64_t area()
    {
        std::float64_t _Val = 0.0;
        std::int32_t _Max = this->_Mycoordinates.size();

        for (std::int32_t _Num = 0; _Num < _Max; ++_Num)
        {
            // _Num is the index of the first vertex, _Next is the next one.
            std::int32_t _Next = (_Num + 1) % _Max;

            // The vertices of the edge we are checking.
            std::int32_t _x1 = this->_Mycoordinates[_Num]->x();
            std::int32_t _y1 = this->_Mycoordinates[_Num]->y();
            std::int32_t _x2 = this->_Mycoordinates[_Next]->x();
            std::int32_t _y2 = this->_Mycoordinates[_Next]->y();

            _Val += (0.5 * (_x1 * _y2 - _x2 * _y1));
        }
        return _Val;
    }

    std::float64_t length()
    {
        std::float64_t _Val = 0.0;

        std::int32_t _Max = this->_Mycoordinates.size();
        for (std::int32_t _Num = 0; _Num < _Max; ++_Num)
        {
            // _Num is the index of the first vertex, _Next is the next one.
            std::int32_t _Next = (_Num + 1) % _Max;

            // The vertices of the edge we are checking.
            std::int32_t _x1 = this->_Mycoordinates[_Num]->x();
            std::int32_t _y1 = this->_Mycoordinates[_Num]->y();
            std::int32_t _x2 = this->_Mycoordinates[_Next]->x();
            std::int32_t _y2 = this->_Mycoordinates[_Next]->y();

            _Val += (std::sqrt(std::pow(_x2 - _x1, 2) + std::pow(_y2 - _y1, 2)));
        }
        return _Val;
    }

    // https://en.wikipedia.org/wiki/Point_in_polygon#Ray_casting_algorithm
    // https://wrf.ecse.rpi.edu//Research/Short_Notes/pnpoly.html
    bool within(std::int32_t _x, std::int32_t _y)
    {
        // If we never cross any lines we're inside.
        bool _Inside = false;
        std::int32_t _Max = this->_Mycoordinates.size();

        for (std::int32_t _Num = 0; _Num < _Max; ++_Num)
        {
            // _Num is the index of the first vertex, _Next is the next one.
            std::int32_t _Next = (_Num + 1) % _Max;

            // The vertices of the edge we are checking.
            std::int32_t _x1 = this->_Mycoordinates[_Num]->x();
            std::int32_t _y1 = this->_Mycoordinates[_Num]->y();
            std::int32_t _x2 = this->_Mycoordinates[_Next]->x();
            std::int32_t _y2 = this->_Mycoordinates[_Next]->y();

            // First check if the line crosses the horizontal line at _Y in either direction.
            if (((_y1 <= _y) && (_y2 > _y)) || ((_y2 <= _y) && (_y1 > _y)))
            {
                // If so, get the point where it crosses that line. This is a simple solution
                // to a linear equation. Note that we can't get a division by zero here -
                // if _Y1 == _Y0 then the above if be false.
                std::float64_t _Cross = (_x2 - _x1) * (_y - _y1) / (_y2 - _y1) + _x1;

                // Finally check if it crosses to the left of our test point. You could equally
                // do right and it should give the same result.
                if (_Cross < _x)
                {
                    _Inside = !_Inside;
                }
            }
        } /* for */

        return _Inside;
    }

    bool intersects(std::int32_t _x, std::int32_t _y, std::float64_t _radius)
    {
        bool _Intersect = within(_x, _y);
        if (false == _Intersect)
        {
            std::int32_t _Max = this->_Mycoordinates.size();
            for (std::int32_t _Num = 0; _Num < _Max; ++_Num)
            {
                std::int32_t _Next = (_Num + 1) % _Max;

                std::int32_t _x1 = this->_Mycoordinates[_Num]->x();
                std::int32_t _y1 = this->_Mycoordinates[_Num]->y();
                std::int32_t _x2 = this->_Mycoordinates[_Next]->x();
                std::int32_t _y2 = this->_Mycoordinates[_Next]->y();

                if (intersects(_x1, _y1, _x2, _y2, _x, _y, _radius))
                {
                    _Intersect = true;
                    break;
                }
            } /* for */
        }

        return _Intersect;
    }

    // https://stackoverflow.com/questions/6091728/line-segment-circle-intersection
    // https://forums.cgsociety.org/t/intersection-of-a-line-and-a-sphere/1552684/2
    bool intersects(std::float64_t _x1, std::float64_t _y1, std::float64_t _x2, std::float64_t _y2,
            std::float64_t _cx, std::float64_t _cy, std::float64_t _cr)
    {
 
        std::float64_t dx = _x2 - _x1;
        std::float64_t dy = _y2 - _y1;
        std::float64_t a = dx * dx + dy * dy;
        std::float64_t b = 2.0 * (dx * (_x1 - _cx) + dy * (_y1 - _cy));
        std::float64_t c = _cx * _cx + _cy * _cy;
        c += _x1 * _x1 + _y1 * _y1;
        c -= 2.0 * (_cx * _x1 + _cy * _y1);
        c -= _cr * _cr;
        std::float64_t bb4ac = b * b - 4.0 * a * c;


        
        // return false  No collision
        // return true Collision
        // return (bb4ac >= 0);      

        if ((std::fabs(bb4ac) < std::numeric_limits<std::float64_t>::epsilon()) || (bb4ac < 0)) 
        {   
            return false; // No collision
        }
        else {
            std::float64_t mu1 = (-b + std::sqrt(bb4ac)) / (2.0 * a);
            std::float64_t mu2 = (-b - std::sqrt(bb4ac)) / (2.0 * a); 
            std::int32_t b1x = _x1 + mu1 * (_x2 - _x1);
            std::int32_t b1y = _y1 + mu1 * (_y2 - _y1);
            std::int32_t b2x = _x1 + mu2 * (_x2 - _x1);
            std::int32_t b2y = _y1 + mu2 * (_y2 - _y1);   
            
            std::int32_t new_x = 0;
            std::int32_t new_y = 0;
 
            get_intersection_point_of_two_lines(
                _x1, _y1, _x2, _y2, 
                b1x, b1y, b2x, b2y,
                &new_x, &new_y);
            
            std::cout << " > " << new_x << ", " << new_x << std::endl;    
            return true;
        }

      
      /*
      bool _Val = false;

      // 원이 좌표의 중심에 있도록 이동합니다.
      _x1 -= _cx;
      _y1 -= _cy;
      _x2 -= _cx;
      _y2 -= _cy;

      std::float64_t dx = _x2 - _x1;
      std::float64_t dy = _y2 - _y1;

      // 직선과 원의 교차점에 대한 이차 방정식의 계수를 구성합니다.
      // 세그먼트 [0..1]에 음수 값이 있으면 세그먼트가 원과 교차합니다.
      std::float64_t a = (dx * dx) + (dy * dy);
      std::float64_t b = 2. * ((_x1 * dx) + (_y1 * dy));
      std::float64_t c = (_x1 * _x1) + (_y1 * _y1) - (_cr * _cr);

      // 세그먼트 [0..1]에 솔루션이 있는지 확인하십시오.
      if (-b < 0)
      {
         _Val = (c < 0);
      }
      else if (-b < (2. * a))
      {
         _Val = (((4. * a * c) - (b * b)) < 0);
      }
      else
      {
         _Val = (a + b + c < 0);
      }

      return _Val;
      */
        
    }
    
    bool get_intersection_point_of_two_lines(
        int _a1x, int _a1y, int _a2x, int _a2y,
        int _b1x, int _b1y, int _b2x, int _b2y,
        int *_x, int *_y)
    {

        double a1 = _a2y - _a1y;
        double b1 = _a1x - _a2x;
        double c1 = a1*(_a1x) + b1*(_a1y);

        double a2 = _b2y - _b1y;
        double b2 = _b1x - _b2x;
        double c2 = a2*(_b1x)+ b2*(_b1y);

        double determinant = a1*b2 - a2*b1;
        if (determinant == 0)
        {
            *_x = -1;
            *_y = -1;
            return false;
        }
        else
        {
            *_x = (b2*c1 - b1*c2)/determinant;
            *_y = (a1*c2 - a2*c1)/determinant;
            return true;
        }

    }
    
};

} /* namespace my */

#endif /* XPOLYGON_H_ */
