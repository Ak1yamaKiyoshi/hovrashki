#include <SFML/Graphics.hpp>
#include "types/types.hpp"

#include <vector>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <chrono>

const int SCREEN_HEIGHT = 800, SCREEN_WIDTH=800;

int main() {

    joint j(
        point({vec2f(100.f, 100.f), vec2f({0.f, 0.f}), 10.f, 0.5f}), 
        point({vec2f(100.f, 100.f), vec2f({0.f, 0.f}), 10.f, 0.5f})
    );

    std::cout << j <<"\n";



    return 0;
}