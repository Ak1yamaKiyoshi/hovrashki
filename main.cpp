#include <SFML/Graphics.hpp>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <chrono>



const int SCREEN_HEIGHT = 800, SCREEN_WIDTH=800;
struct vector2dim {
    double x, y;
    vector2dim() {}
    vector2dim(double x, double y) : x(x), y(y) {}
};


struct point { 
    double x, y,
    velocity_x, velocity_y, 
    target_x, target_y,
    weight /* int? */, hardness /*0 ... 1*/;
    short *color; // RGB
    point() {}
    point(double x, double y, double weight, double hardness, short *color)
        : x(x), y(y), weight(weight), hardness(hardness), target_x(x), target_y(y),
          velocity_x(0.f), velocity_y(0.f), color(color) {}
};


double euclidian_distance(vector2dim vec0, vector2dim vec1) {
    return sqrt(pow((vec0.x - vec1.x), 2) 
    + pow((vec0.y - vec1.y), 2));
}


struct mesh {
    double dumping = 0.11;
    std::vector<point> points;
    mesh(std::vector<point> points) {
        this->points = points;
     }

    /**
     * @brief  (dx, dy) to velocity of each point
     * @warning delta time should be handled outside */
    void apply_force(vector2dim unit_vector, double force) {
        for (auto &cur_point: this->points) {
            cur_point.velocity_x += unit_vector.x * force;
            cur_point.velocity_y += unit_vector.y * force;
        }
    }

    vector2dim calculate_average_position() {
        vector2dim average_position;
        average_position.x = 0;
        average_position.y = 0;
        size_t num_points = this->points.size();

        for (const auto &cur_point : this->points) {
            average_position.x += cur_point.x;
            average_position.y += cur_point.y;
        }

        average_position.x /= num_points;
        average_position.y /= num_points;

        return average_position;
    }


    /**
     * @brief adds (dx, dy) to velocity of nearest point */
    void apply_force_at_point(vector2dim unit_vector,
                double force, vector2dim g_pos) {
        //int *distances = new int[this->points.size()];
        float min_distance; 
        point closest_point;
        size_t amount_of_points = (size_t)this->points.size();
        for (size_t i = 0; i < amount_of_points; i++) {
            vector2dim point_global_pos;
            point_global_pos.x = this->points[i].x;
            point_global_pos.y = this->points[i].y;

            double distance = euclidian_distance(
                this->calculate_average_position(), 
                point_global_pos
            );
            if (i == 0 || distance < min_distance) {
                min_distance = distance;
                closest_point = this->points[i];
            }
            // TODO: APPLY ON NEAREST POINTS TOO
            // dx / distance(current, original)^2
        }
        closest_point.velocity_x += unit_vector.x * force;
        closest_point.velocity_y += unit_vector.y * force;
    }
void update(double delta) {
    // Define constants
    const double gravity = 9.81; // Adjust as needed
    const double max_speed = 200.0; // Adjust as needed

    // Iterate through points
    for (auto &cur_point : this->points) {
        // Calculate gravity buffer
        double gravity_buffer = gravity * delta * cur_point.weight;

        // Update target position considering gravity
        cur_point.target_y += gravity_buffer;

        // Check for collisions with screen edges
        if (cur_point.target_x < 0)
            cur_point.target_x = 0;
        else if (cur_point.target_x > SCREEN_WIDTH)
            cur_point.target_x = SCREEN_WIDTH;

        // Ensure points stay above the ground level
        if (cur_point.target_y > SCREEN_HEIGHT) {
            cur_point.target_y = SCREEN_HEIGHT;
        }

        // Calculate velocity components
        double dx = cur_point.target_x - cur_point.x;
        double dy = cur_point.target_y - cur_point.y;
        double distance = sqrt(dx * dx + dy * dy);

        if (distance > 0) {
            double acceleration = 1000.0; // Adjust as needed

            double vx = (dx / distance) * acceleration;
            double vy = (dy / distance) * acceleration;

            // Update velocity
            cur_point.velocity_x += vx * delta;
            cur_point.velocity_y += vy * delta;

            // Limit velocity to max_speed
            double total_velocity = sqrt(cur_point.velocity_x * cur_point.velocity_x + cur_point.velocity_y * cur_point.velocity_y);
            if (total_velocity > max_speed) {
                cur_point.velocity_x = (cur_point.velocity_x / total_velocity) * max_speed;
                cur_point.velocity_y = (cur_point.velocity_y / total_velocity) * max_speed;
            }

            // Apply damping
            cur_point.velocity_x *= (1.0 - this->dumping);
            cur_point.velocity_y *= (1.0 - this->dumping);
        }

        // Update point position
        cur_point.x += cur_point.velocity_x * delta;
        cur_point.y += cur_point.velocity_y * delta;
    }

    // Check if any point touches the ground
    bool ground_collision = false;
    for (const auto &cur_point : this->points) {
        if (cur_point.y >= SCREEN_HEIGHT) {
            ground_collision = true;
            break;
        }
    }

    // If ground collision detected, rotate the structure
    if (ground_collision) {
        // Calculate average position of the structure
        vector2dim average_position = calculate_average_position();

        // Calculate rotation angle based on the difference in y-coordinate from the ground
        double angle = atan2(average_position.y - SCREEN_HEIGHT, average_position.x - SCREEN_WIDTH / 2);
        
        // Rotate the structure
        apply_rotation(angle);
    }
}


    void apply_rotation(double theta_degrees) {
        float radians = theta_degrees * M_PI / 180.0;
        float cos_angle = cos(radians);
        float sin_angle = sin(radians);    
        float center_x, center_y;

        vector2dim center = calculate_average_position();
        center_x = center.x;
        center_y = center.y;

        for (auto &cur_point: this->points) {
            float x_relative = cur_point.x - center_x;
            float y_relative = cur_point.y - center_y;

            float new_x = x_relative * cos_angle - y_relative * sin_angle;
            float new_y = x_relative * sin_angle + y_relative * cos_angle;

            cur_point.target_x = new_x + center_x;
            cur_point.target_y = new_y + center_y;
        }
    }

    void apply_rotation_force(double theta_degrees, double force) {
        vector2dim center = calculate_average_position();
        float radians = theta_degrees * M_PI / 180.0;
        float cos_angle = cos(radians);
        float sin_angle = sin(radians);    

        float center_x = center.x;
        float center_y = center.y;

        for (auto &cur_point: this->points) {
            float x_relative = cur_point.x - center_x;
            float y_relative = cur_point.y - center_y;

            float new_vx = cur_point.velocity_x * cos_angle - cur_point.velocity_y * sin_angle;
            float new_vy = cur_point.velocity_x * sin_angle + cur_point.velocity_y * cos_angle;

            cur_point.velocity_x += new_vx * force;
            cur_point.velocity_y += new_vy * force;

        }
    }

        
    void apply_displacement(vector2dim unit_vector, double multiplier) {
        for (auto &cur_point: this->points) {
            cur_point.target_x += unit_vector.x * multiplier;
            cur_point.target_y += unit_vector.y * multiplier;
        }
    }
};



mesh triangle_mesh() {
    short color_values[] = {255, 255, 255};
    point p1(200+0.0, 200+120.0,  100,0.1, color_values); 
    point p2(200+12.0, 200+0.0,   100,0.1, color_values); 
    point p3(200+200.5, 200+44.0, 100,0.1, color_values);
    
    std::vector<point> triangle_points = {p1, p2, p3};

    mesh triangle(triangle_points);
    return triangle;
}



void drawMesh(sf::RenderWindow& window, const mesh m, sf::Color color = sf::Color::White) {
    size_t numPoints = m.points.size();
    if (numPoints < 2) {
        return; 
    }

    sf::VertexArray lines(sf::LineStrip, numPoints);
    for (size_t i = 0; i < numPoints; ++i) {
        const point& p = m.points[i];
        lines[i].position = sf::Vector2f(p.x, p.y);
        lines[i].color = color;
        
    }

    window.draw(lines);
}



void handleMousePress(sf::RenderWindow& window, sf::Event& event, mesh& structure) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        vector2dim avg_pos = structure.calculate_average_position();
        sf::Vector2f structurePos(avg_pos.x, avg_pos.y);

        sf::Vector2f directionVector(mousePos.x - structurePos.x, mousePos.y - structurePos.y);
        float magnitude = sqrt(directionVector.x * directionVector.x + directionVector.y * directionVector.y);

        if (magnitude > 0) {
            sf::Vector2f unitVector(directionVector.x / magnitude, directionVector.y / magnitude);
            vector2dim unitVec2d(unitVector.x, unitVector.y);

            structure.apply_force(unitVec2d, 100.0f); // Example: Apply force in the direction of the unit vector
        }
    }
}


void handleButtonPress(sf::RenderWindow& window, sf::Event& event, mesh& structure) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::R) {
            structure.apply_rotation_force(90.0, 10);
        }
    }
}


int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_HEIGHT, SCREEN_WIDTH), "Mesh Drawing");

    mesh structure = triangle_mesh();
    size_t numPoints = structure.points.size();

    // Variables for controlling frame rate
    constexpr double frameRate = 120.0;
    const std::chrono::duration<double> frameDuration(1.0 / frameRate);
    std::chrono::time_point<std::chrono::steady_clock> lastFrameTime = std::chrono::steady_clock::now();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                handleMousePress(window, event, structure);
            } else if (event.type == sf::Event::KeyPressed) {
                handleButtonPress(window, event, structure);
            }
        }

        // Calculate elapsed time since last frame
        std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsedTime = currentTime - lastFrameTime;

        // If enough time has passed, update the structure and render
        if (elapsedTime >= frameDuration) {
            structure.update(elapsedTime.count()); // Pass elapsed time to update function
            lastFrameTime = currentTime;

            window.clear();
            drawMesh(window, structure, sf::Color::Green); 
            window.display();
        }
    }

    return 0;
}
