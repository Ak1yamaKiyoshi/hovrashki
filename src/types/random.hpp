#pragma once
#include "types/types.hpp"

#include <vector>
#include <stdlib.h>
#include <iostream>
#include <cmath>


float random_float(int offset, int limit) {
    return (float) (rand() % limit + offset + ((float)(rand()%100))/100);
}

vec2f random_vec2f(int offset, int limit) {
    return vec2f({random_float(offset, limit), random_float(offset, limit)});
}

point random_point(int offset, int limit) {
    return point({
        random_vec2f(offset, limit), 
        random_vec2f(offset, limit), 
        random_float(0, 100), 
        random_float(0, 1)
    });
}

joint random_joint(int offset, int limit) {
    return joint({
        random_point(offset, limit),
        random_point(offset, limit),
    });
}

structure random_structure(int amount_of_joints, int offset, int limit) {
    std::vector<joint> joints;
    for (int i = 0; i < amount_of_joints; i++)
        joints.push_back(random_joint(offset, limit));
    return structure({joints});
}


structure random_strcuture() {
    return structure({
        std::vector<joint>({
            joint(
                point({vec2f(100.f, 100.f), vec2f({0.f, 0.f}), 10.f, 0.5f}), 
                point({vec2f(100.f, 100.f), vec2f({0.f, 0.f}), 10.f, 0.5f})
            ),
            joint(
                point({vec2f(100.f, 100.f), vec2f({0.f, 0.f}), 10.f, 0.5f}), 
                point({vec2f(100.f, 100.f), vec2f({0.f, 0.f}), 10.f, 0.5f})
            ),
            joint(
                point({vec2f(100.f, 100.f), vec2f({0.f, 0.f}), 10.f, 0.5f}), 
                point({vec2f(100.f, 100.f), vec2f({0.f, 0.f}), 10.f, 0.5f})
            ),
            joint(
                point({vec2f(100.f, 100.f), vec2f({0.f, 0.f}), 10.f, 0.5f}), 
                point({vec2f(100.f, 100.f), vec2f({0.f, 0.f}), 10.f, 0.5f})
            )
        })
    });
}