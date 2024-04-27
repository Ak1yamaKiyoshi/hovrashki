#pragma once
#include <iostream>



struct vec2f {
    float x, y;

    vec2f() : x(0), y(0) {}
    vec2f(float x, float y) : x(x), y(y) {}

    friend vec2f operator+(const vec2f& lhs, const vec2f& rhs) {
        return vec2f(lhs.x + rhs.x, lhs.y + rhs.y);
    }

    friend vec2f operator-(const vec2f& lhs, const vec2f& rhs) {
        return vec2f(lhs.x - rhs.x, lhs.y - rhs.y);
    }

    friend vec2f operator-(const vec2f& v) {
        return vec2f(-v.x, -v.y);
    }

    friend vec2f operator*(const vec2f& v, float scalar) {
        return vec2f(v.x * scalar, v.y * scalar);
    }

    friend vec2f operator*(float scalar, const vec2f& v) {
        return v * scalar;
    }

    friend vec2f operator/(const vec2f& v, float scalar) {
        return vec2f(v.x / scalar, v.y / scalar);
    }

    friend vec2f& operator+=(vec2f& lhs, const vec2f& rhs) {
        lhs.x += rhs.x;
        lhs.y += rhs.y;
        return lhs;
    }

    friend vec2f& operator-=(vec2f& lhs, const vec2f& rhs) {
        lhs.x -= rhs.x;
        lhs.y -= rhs.y;
        return lhs;
    }

    friend vec2f& operator*=(vec2f& v, float scalar) {
        v.x *= scalar;
        v.y *= scalar;
        return v;
    }

    friend vec2f& operator/=(vec2f& v, float scalar);

    friend std::ostream& operator<<(std::ostream& os, const vec2f& v);
    friend std::istream& operator>>(std::istream& is, vec2f& v);   
};


std::ostream& operator<<(std::ostream& os, const vec2f& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

std::istream& operator>>(std::istream& is, vec2f& v) {
    char dummy;
    is >> dummy >> v.x >> dummy >> v.y >> dummy;
    return is;
}
