#include <SFML/Graphics.hpp>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <chrono>


struct Point {
    float x;
    float y;
    Point(float x, float y) : x(x), y(y) {}
};

class Trace {
private:
    std::vector<Point> points;

public:
    Trace(std::vector<Point> pts) : points(pts) {}
    friend std::ostream& operator<<(std::ostream& os, const Trace& trace);
    const std::vector<Point>& getPoints() const { return points; }
    std::vector<Point> getMutablePoints() { return points; }

    void reassignPoint(size_t index, float newX, float newY) {
        if (index < points.size()) {
            points[index].x = newX;
            points[index].y = newY;
        }
    }
};

std::ostream& operator<<(std::ostream& os, const Trace& trace) {
    os << "Trace(";
    for (size_t i = 0; i < trace.points.size(); ++i) {
        const auto& point = trace.points[i];
        os << "(" << point.x << " " << point.y << ")";
        if (i != trace.points.size() - 1) {
            os << " ";
        }
    }
    os << ")";
    return os;
}

int main() {
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Line Example");

    std::vector<Point> pts = {
        Point(0.0, 0.0),
        Point(10.0, 0.0),
        Point(20.0, 20.0),
    };

    Trace complexLine(pts);

    float lineThickness = 15.f;
    float roundingQuality = 10;
    float offsetX = 100;
    float offsetY = 100;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        window.clear();

        const std::vector<Point>& points = complexLine.getPoints();
        for (size_t i = 0; i < points.size() - 1; ++i) {
            const Point& startPoint = points[i];
            const Point& endPoint = points[i + 1];

            float dx = endPoint.x - startPoint.x;
            float dy = endPoint.y - startPoint.y;
            float lineLength = std::sqrt(dx * dx + dy * dy);
            float angle = std::atan2(dy, dx);
            sf::Vector2f direction(dx / lineLength, dy / lineLength);

            for (float t = 0.0f; t <= lineLength; t += lineThickness/roundingQuality ) {
                sf::CircleShape segment(lineThickness / 2.0f);
                segment.setPosition(startPoint.x + offsetX + (t * direction.x) - (lineThickness / 2.0f), startPoint.y + offsetY + (t * direction.y) - (lineThickness / 2.0f));
                segment.setFillColor(sf::Color::White);
                window.draw(segment);
            }


        }

        window.display();
        std::vector<Point> mutable_points = complexLine.getMutablePoints();
        for (size_t i = 0; i < points.size() - 1; i++) {
            complexLine.reassignPoint(i, 
            mutable_points[i].x + (float)(rand() % 1000) /  100000 - 0.005, 
            mutable_points[i].y + (float)(rand() % 1000) / 100000 - 0.005
        );
        }


    }

    return 0;
}