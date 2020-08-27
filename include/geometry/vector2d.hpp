/*
 * vector2d.hpp
 *
 *  Created on: 2020. 6. 4.
 *      Author: pino7
 */

#ifndef VECTOR2D_HPP_
#define VECTOR2D_HPP_

#include <cmath>
#include <cfloat>
#include <climits>
#include <tuple>

/*****
 The vector2d class is an object consisting of simply an x and y value.
 Certain operators are overloaded to make it easier for vector math operations
 to be performed.
 *****/

template<class T>
class vector2d {
public:

    // The x and y values are public to give easier access foroutside funtions.
    // Accessors and mutators are not really necessary.
    T x;
    T y;

    // Constructor assigns the inputs to x and y.
    vector2d(): x(T(0)), y(T(0)) {}
    vector2d(const T& vx, const T& vy): x(vx), y(vy) {}
    vector2d(const vector2d& v):x(v.x), y(v.y){}

    T& operator[](int i) { return (i == 0)?x:y; }
    T operator[](int i) const { return (i== 0)?x:y;}

    // The following operators simply return vector2ds that
    // have operations performed on the relative (x, y) values
    vector2d& operator+=(const vector2d& v) { x += v.x; y += v.y; return *this; }
    vector2d& operator-=(const vector2d& v) { x -= v.x; y -= v.y; return *this; }
    vector2d& operator*=(const vector2d& v) { x *= v.x; y *= v.y; return *this; }
    vector2d& operator/=(const vector2d& v) { x /= v.x; y /= v.y; return *this; }

    // Check if the Vectors have the same values (uses pairwise comparison of `std::tuple` on the x,y values of L and R.
    friend bool operator==(const vector2d& L, const vector2d& R) { return std::tie(L.x, L.y) == std::tie(R.x, R.y); }
    friend bool operator!=(const vector2d& L, const vector2d& R) { return !(L == R); }

    // Check if the Vectors have the same values (uses pairwise comparison of `std::tuple` on the x,y values of L and R.
    friend bool operator< (const vector2d& L, const vector2d& R) { return std::tie(L.x, L.y) < std::tie(R.x, R.y); }
    friend bool operator>=(const vector2d& L, const vector2d& R) { return !(L < R); }
    friend bool operator> (const vector2d& L, const vector2d& R) { return   R < L ; }
    friend bool operator<=(const vector2d& L, const vector2d& R) { return !(R < L); }

    // Negate both the x and y values.
    vector2d operator-() const { return vector2d(-x, -y); }

    // Apply scalar operations.
    vector2d& operator*=(const T& s) { x *= s; y *= s; return *this; }
    vector2d& operator/=(const T& s) { x /= s; y /= s; return *this; }

    /* utility functions */

    // roate
    void rotate(float angle_degrees);

    // return roated vector
    vector2d<T> rotated(float angle_degrees);

    // Product functions
    T dot(const vector2d<T>&, const vector2d<T>&);
    T cross(const vector2d<T>&, const vector2d<T>&);

    // Returns the length of the vector from the origin.
    T length(const vector2d<T>& v);

    // set length of the vector
    T length() { return sqrt((this->x * this->x) + (this->y * this->y)); }

    // get distance between objects
    T get_distance(const vector2d<T>& other) {
        return sqrt(pow((x - other[0]),2) + pow((y - other[1]),2));
    }

    // nomalized vector
    void normalized();
    vector2d<T> normalized(const vector2d<T>& v);

    // Return a vector perpendicular to the left.
    vector2d<T> perpendicular() { return vector2d<T>(y, -x); }

    // Return true if two line segments intersect.
    bool intersect(const vector2d<T>&, const vector2d<T>&, const vector2d<T>&, const vector2d<T>&);

    // Return the point where two lines intersect.
    vector2d<T> get_intersect(const vector2d<T>&, const vector2d<T>&, const vector2d<T>&, const vector2d<T>&);

    // return the angle
    float get_angle() {
        if (this->length() == 0) return 0;
        float angle =  atan2(y, x);
        return angle/M_PI*180;
    }

    // return the angle between two vectors
    float get_angle_between(const vector2d<T>&);

    // get the opposite direction vector
    vector2d<T> get_reflection() {
        return vector2d(-x, -y);
    }

};


template<class T>
vector2d<T> operator+(const vector2d<T>& L, const vector2d<T>& R) {
    return vector2d<T>(L) += R;
}

template<class T>
vector2d<T> operator-(const vector2d<T>& L, const vector2d<T>& R) {
    return vector2d<T>(L)-= R;
}

template<class T>
vector2d<T> operator*(const vector2d<T>& L, const vector2d<T>& R) {
    return vector2d<T>(L)*= R;
}

template<class T>
vector2d<T> operator/(const vector2d<T>& L, const vector2d<T>& R) {
    return vector2d<T>(L)/= R;
}

template<class T>
vector2d<T> operator*(const T& s, const vector2d<T>& v) {
    return vector2d<T>(v) *= s;
}

template<class T>
vector2d<T> operator*(const vector2d<T>& v, const T& s) {
    return vector2d<T>(v) *= s;
}

template<class T>
vector2d<T> operator/(const T& s, const vector2d<T>& v) {
    return vector2d<T>(v) /= s;
}

template<class T>
vector2d<T> operator/(const vector2d<T>& v, const T& s) {
    return vector2d<T>(v) /= s;
}

template<class T>
T dot(const vector2d<T>& a, const vector2d<T>& b) {
    return ((a.x * b.x) + (a.y * b.y));
}

template<class T>
T cross(const vector2d<T>& a, const vector2d<T>& b) {
    return ((a.x * b.y) - (a.y * b.x));
}

template<class T>
T length(const vector2d<T>& v) { return sqrt((v.x * v.x) + (v.y * v.y)); }

template<class T> vector2d<T> normalized(const vector2d<T>& v) {
    T  magnitude = length(v);
    return vector2d<T>(v.x / magnitude, v.y / magnitude);
}

template<class T> void vector2d<T>::normalized() {
    T magnitude = this->length();
    if (magnitude != 0) {
        x /= magnitude;
        y /= magnitude;
    } else {
        x = 0;
        y = 0;
    }
}

template<class T>
bool vector2d<T>::intersect(const vector2d<T>&aa, const vector2d<T>&ab, const vector2d<T>&ba, const vector2d<T>&bb) {
    vector2d<T> p = aa;
    vector2d<T> r = ab - aa;
    vector2d<T> q = ba;
    vector2d<T> s = bb - ba;

    float t = cross((q - p), s) / cross(r, s);
    float u = cross((q - p), r) / cross(r, s);

    return (0.0 <= t && t <= 1.0) && (0.0 <= u && u <= 1.0);
}

template<class T>
vector2d<T> vector2d<T>::get_intersect(const vector2d<T>&aa, const vector2d<T>&ab, const vector2d<T>&ba, const vector2d<T>&bb) {
    T pX = (aa.x*ab.y - aa.y*ab.x)*(ba.x - bb.x) - (ba.x*bb.y - ba.y*bb.x)*(aa.x - ab.x);
    T pY = (aa.x*ab.y - aa.y*ab.x)*(ba.y - bb.y) -(ba.x*bb.y - ba.y*bb.x)*(aa.y - ab.y);
    T denominator = (aa.x - ab.x)*(ba.y - bb.y) -
            (aa.y - ab.y)*(ba.x - bb.x);
    return vector2d<T>(pX / denominator, pY / denominator);
}

template<class T>
void vector2d<T>::rotate(float angle_degrees) {
    T radians = angle_degrees/180*M_PI;
    T co = cos(radians);
    T sn = sin(radians);
    T xx = x*co - y*sn;
    T yy = x*sn + y*co;
    x = xx;
    y = yy;
}

template<class T>
vector2d<T> vector2d<T>::rotated(float angle_degrees) {
    float radians = angle_degrees/180*M_PI;
    float co = cos(radians);
    float sn = sin(radians);
    T xx = x*co - y*sn;
    T yy = x*sn + y*co;
    return vector2d(xx, yy);
}

template<class T>
float vector2d<T>::get_angle_between(const vector2d<T>& other) {
    T cross = x*other[1] - y*other[0];
    T dot = x*other[0] + y*other[1];
    return atan2(cross, dot)/M_PI*180;
}

#endif /* VECTOR2D_HPP_ */
