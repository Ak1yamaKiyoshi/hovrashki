#pragma once
#include <types/point.hpp>
#include <iostream>


struct joint {
    point start;
    point end;
    joint() {}
    joint(point start, point end)
        : start(start), end(end) {}

    friend std::ostream& operator<<(std::ostream& os, const joint& j);
};

std::ostream& operator<<(std::ostream& os, const joint& j) {
    os << "joint(\n    "<< j.start << "\n    " << j.end << "\n  )";
    return os;
}