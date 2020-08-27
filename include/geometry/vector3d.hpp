/*
 * vector3d.hpp
 *
 *  Created on: 2020. 6. 4.
 *      Author: pino7
 */

#ifndef VECTOR3D_HPP_
#define VECTOR3D_HPP_

/*
I am creating a class vector3d which will be used for vector operation . I have overloaded all the basic functions for the required for vector operation .
There is no need for extra class , so no inheritance was necessary .
*/
#include<iostream>
#include<math.h>
#include<assert.h>

template<class T>
class vector3d
{
public:
     T x;
     T y;
     T z;

    vector3d(): x(T(0)), y(T(0)), z(T(0)) {}
    vector3d(const T& vx, const T& vy, const T& vz): x(vx), y(vy), z(vz) {}
    vector3d(const vector3d& v):x(v.x), y(v.y), z(v.z){}

    // have operations performed on the relative (x, y, z) values
    vector3d &operator+=(const vector3d &v) { x+=v.x; y+=v.y; z+=v.z; return *this; }
    vector3d &operator-=(const vector3d &v) { x-=v.x;y-=v.y;z-=v.z;return *this; }
    vector3d &operator*=(const vector3d &v) {x*=v.x;y*=v.y;z*=v.z;return *this; }
    vector3d &operator/=(const vector3d &v) { x/=v.x; y/=v.y; z/=v.z; return *this; }

    // Product functions
    T dot(const vector3d<T>&);
    vector3d<T> cross(const vector3d<T>&);

    T magnitude();
    vector3d<T> normalization();
    T square();

    T distance(const vector3d<T>& v) {
        vector3d<T> d=*this-v;
        return d.magnitude();
    }

};

template<class T>
T vector3d<T>::dot(const vector3d<T>& v) {
    return ((x * v.x) + (y * v.y) + (z * v.z));
}

template<class T>
vector3d<T> vector3d<T>::cross(const vector3d<T>& v) {
    T ni=y*v.z-z*v.y;
    T nj=z*v.x-x*v.z;
    T nk=x*v.y-y*v.x;
    return vector3d<T>(ni,nj,nk);
}

template<class T>
T vector3d<T>::magnitude() {
    return sqrt(square());
}

template<class T>
vector3d<T> vector3d<T>::normalization() {
    assert(magnitude()!=0);
    *this/=magnitude();
    return *this;
}

template<class T>
T vector3d<T>::square() {
    return x*x+y*y+z*z;
}

#endif /* VECTOR3D_HPP_ */
