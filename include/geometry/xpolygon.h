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

#include "../utility/stringtok.hpp"
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

   void push_back(std::int32_t _X, std::int32_t _Y)
   {
      this->_Mycoordinates.push_back(std::make_unique<my::xcoordinate>(_X, _Y));
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

   xcoordinate get_center()
   {
      
      std::float64_t _Area = 0.0;
      std::float64_t _Center_x = 0.0;
      std::float64_t _Center_y = 0.0;
      
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
         
         _Area += (_x1 * _y2);
         _Area -= (_y1 * _x2);
         _Center_x += ((x1 + x2) * ((x1 * y2) - (x2 * y1)));
         _Center_y += ((y1 + y2) * ((x1 * y2) - (x2 * y1)));
      }
      _Area /= 2.0;
      _Area = std::fabs(_Area);
      _Center_x = _Center_x / (6.0 * _Area);
      _Center_y = _Center_y / (6.0 * _Area);
      
      return xcoordinate(_Center_x, _Center_y);
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

   bool within(std::int32_t _X, std::int32_t _Y, std::float64_t _Radius)
   {
      bool _Intersect = false;

      _Intersect = within(_X, _Y);

      if (false == _Intersect)
      {
         std::int32_t _Max = this->_Mycoordinates.size();

         for (std::int32_t _Num = 0; _Num < _Max; ++_Num)
         {
            std::int32_t _Next = (_Num + 1) % _Max;

            std::int32_t _X0 = this->_Mycoordinates[_Num]->x();
            std::int32_t _Y0 = this->_Mycoordinates[_Num]->y();
            std::int32_t _X1 = this->_Mycoordinates[_Next]->x();
            std::int32_t _Y1 = this->_Mycoordinates[_Next]->y();

            if (intersect(_X0, _Y0, _X1, _Y1, _X, _Y, _Radius))
            {
               _Intersect = true;
               break;
            }
         } /* for */
      }

      return _Intersect;
   }

   bool intersect(std::float64_t _X0, std::float64_t _Y0, std::float64_t _X1, std::float64_t _Y1,
   std::float64_t _Circle_x, std::float64_t _Circle_y, std::float64_t _Radius)
   {
      bool _Retval = false;

      // 원이 좌표의 중심에 있도록 이동합니다.
      _X0 -= _Circle_x;
      _Y0 -= _Circle_y;
      _X1 -= _Circle_x;
      _Y1 -= _Circle_y;

      std::float64_t _Diff_x = _X1 - _X0;
      std::float64_t _Diff_y = _Y1 - _Y0;

      // 직선과 원의 교차점에 대한 이차 방정식의 계수를 구성합니다.
      // 세그먼트 [0..1]에 음수 값이 있으면 세그먼트가 원과 교차합니다.
      std::float64_t a = (_Diff_x * _Diff_x) + (_Diff_y * _Diff_y);
      std::float64_t b = 2. * ((_X0 * _Diff_x) + (_Y0 * _Diff_y));
      std::float64_t c = (_X0 * _X0) + (_Y0 * _Y0) - (_Radius * _Radius);

      // 세그먼트 [0..1]에 솔루션이 있는지 확인하십시오.
      if (-b < 0)
      {
         _Retval = (c < 0);
      }
      else if (-b < (2. * a))
      {
         _Retval = (((4. * a * c) - (b * b)) < 0);
      }
      else
      {
         _Retval = (a + b + c < 0);
      }

      return _Retval;
   }
};

} /* namespace my */

#endif /* XPOLYGON_H_ */
