#pragma once
#include <types/vec2f.hpp>

#include <iostream>

struct point {
    vec2f pos;
    vec2f velocity;
    float weight;
    float hardness;

    point() {}
    point(vec2f pos, vec2f velocity, float weight, float hardness)
        : pos(pos), velocity(velocity), weight(weight), hardness(hardness) {}

    friend std::ostream& operator<<(std::ostream& os, const point& p) {
        os << "point(pos: " << p.pos << ", velocity: " << p.velocity << ", weight: " << p.weight << ", hardness: " << p.hardness << ")";
        return os;
    }
};