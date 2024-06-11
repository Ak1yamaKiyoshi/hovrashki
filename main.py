import pygame
from dataclasses import dataclass
from typing import List, Tuple, Union
import time
import math
pygame.init()
from src.datatypes import vec2f, point
from src.utils import vec_utils, point_utils, math_utils


GRAVITY = 0
DUMPING = 1 - 0.034
MAX_VELOCITY = 100


# Initialize Pygame
pygame.init()
WINDOW_SIZE = (800, 600)
screen = pygame.display.set_mode(WINDOW_SIZE)
pygame.display.set_caption("Point Simulation")
clock = pygame.time.Clock()

# Define colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)

# Set up points
p1 = point(vec2f(100+0, 100+0), vel=vec2f(-1, 1), mass=100.0)
p2 = point(vec2f(100+10, 100+10), vel=vec2f(1, -1), mass=64.0)
p3 = point(vec2f(100+10, 100+-10), vel=vec2f(0.1, -1), mass=85.0)
p4 = point(vec2f(100+-10, 100+-50), vel=vec2f(5, -0.1), mass=95.0)


point_utils.add_neighbour(p1, p2, repeling_force=[50.4], angle_range_rad=(-math.pi, math.pi))
point_utils.add_neighbour(p2, p3, repeling_force=[50.4], angle_range_rad=(-math.pi, math.pi))
point_utils.add_neighbour(p3, p4, repeling_force=[50.4], angle_range_rad=(-math.pi, math.pi))
point_utils.add_neighbour(p4, p1, repeling_force=[50.4], angle_range_rad=(-math.pi, math.pi))

points: List[point] = [p1, p2, p3, p4,]

screen_width = 1900
screen_height = 1000
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption("Points Simulation")

BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)



def draw_points(points: List[point]):
    for p in points:
        x, y = int(p.pos.x), int(p.pos.y)
        color = (math_utils.clip(int(abs(p.vel.x/MAX_VELOCITY//5)*255), 50, 255), math_utils.clip(int(abs(p.vel.y/MAX_VELOCITY//5)*255), 50, 255), 150)
        pygame.draw.circle(
            screen, 
            color,
            (x, y), 
            int(p.mass//10)
        )


clock = pygame.time.Clock()
running = True
while running:
    clock.tick(144)  
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.MOUSEMOTION:
            mouse_x, mouse_y = pygame.mouse.get_pos()
            vec = vec_utils.direction(p1.pos, vec2f(float(mouse_x), float(mouse_y))) * 40.0
            point_utils.apply_vector(p1, vec)

    # Clear the screen
    screen.fill(BLACK)

    # Update point positions
    point_utils.apply_vector_to_array(points, vec2f(y=GRAVITY))
    point_utils.tight_point_structure(p1, power=30.0)
    point_utils.multiply_vector_array(points, vec2f(DUMPING, DUMPING))
    point_utils.apply_velocity_to_array(points, 1/90, max_velocity=MAX_VELOCITY)


    draw_points(points)

    pygame.display.flip()

# Quit Pygame
pygame.quit()
