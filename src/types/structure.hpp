#pragma once
#include <vector>
#include <types/joint.hpp>


struct structure {
    std::vector<joint> joints;
    structure() {}
    structure(std::vector<joint> joints) 
        : joints(joints) {} 
};
