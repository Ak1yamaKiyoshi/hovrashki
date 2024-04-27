#pragma once
#include <vector>
#include <types/joint.hpp>


struct structure {
    std::vector<joint> joints;
    structure() {}
    structure(std::vector<joint> joints) 
        : joints(joints) {} 


    friend std::ostream& operator<<(std::ostream& os, const structure& s);
};


std::ostream& operator<<(std::ostream& os, const structure& s) {
    os << "structure(\n";
    for (auto &j: s.joints)
        os << "  " << j << "\n";
    os << ")\n";
    return os;
}


/*
structure s = structure({
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
*/