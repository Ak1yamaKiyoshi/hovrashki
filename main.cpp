#include <SFML/Graphics.hpp>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <chrono>

const int SCREEN_HEIGHT = 800, SCREEN_WIDTH=800;



struct vec2f {
    float x, y;

    vec2f() : x(0), y(0) {}
    vec2f(float x, float y) : x(x), y(y) {}

    vec2f operator+(const vec2f& other) const {
        return vec2f(x + other.x, y + other.y);
    }

    vec2f operator-(const vec2f& other) const {
        return vec2f(x - other.x, y - other.y);
    }

    vec2f operator-() const {
        return vec2f(-x, -y);
    }

    vec2f operator*(float scalar) const {
        return vec2f(x * scalar, y * scalar);
    }

    vec2f operator/(float scalar) const {
        return vec2f(x / scalar, y / scalar);
    }

    vec2f& operator+=(const vec2f& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    vec2f& operator-=(const vec2f& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    vec2f& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    vec2f& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }
};

struct point { 
    vec2f pos;
    vec2f velocity;
    float weight;
    float hardness;

    point() {}
    point(vec2f pos, vec2f velocity, float weight, float hardness)
        : pos(pos), velocity(velocity), 
        weight(weight), hardness(hardness) {}
};

struct joint {
    point start;
    point end;
    joint() {}
    joint(point start, point end)
        : start(start), end(end) {}
};

struct structure {
    std::vector<joint> joints;
    structure() {}
    structure(std::vector<joint> joints) 
        : joints(joints) {} 
};
