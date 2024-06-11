import math
from ..datatypes import point, vec2f
from .vec import vec_utils
from typing import List, Tuple
from .math import math_utils

class point_utils:
    @staticmethod
    def distance(p1:point, p2:point):
        return math.sqrt((p2.pos.x-p1.pos.x)**2 + (p2.pos.y-p1.pos.y)**2)

    @staticmethod
    def angle_rad(p1: point, p2: point):
        return math.atan2(p2.pos.y-p1.pos.y, p2.pos.x - p1.pos.x)

    @staticmethod
    def angle_deg(p1: point, p2: point):
        return math.degrees(math.atan2(p2.pos.y-p1.pos.y, p2.pos.x - p1.pos.x))

    @classmethod
    def add_neighbour(cls, p: point, neighbour: point, angle_range_rad: Tuple[float, float]=(-0.17453292519943295, 0.17453292519943295), repeling_force=(1, 1)):
        p.neighbors.append(neighbour)
        p.lenghts.append(cls.distance(p, neighbour))
        p.angles_rad.append(cls.angle_rad(p, neighbour))
        p.angle_ranges_rad.append(angle_range_rad)
        p.repeling_forces.append(vec2f(*repeling_force))

    @staticmethod
    def str(p: point):
        return f"point(x{p.pos.x:4.4f} y{p.pos.y:4.4f} n{len(p.neighbors)})"

    @staticmethod
    def multiply_vector(p: point, vec: vec2f):
        p.vel = p.vel * vec
        
    @classmethod
    def multiply_vector_array(cls, points: List[point], vec: vec2f):
        for p in points:
            cls.multiply_vector(p, vec)

    @staticmethod
    def apply_vector(p: point, vec:vec2f):
        p.vel = p.vel + vec
    
    @classmethod
    def apply_vector_to_array(cls, parray, vec):
        for point_ in parray:
            cls.apply_vector(point_, vec)
    
    
    @staticmethod
    def apply_velocity(p: point, dt, max_velocity=1000):
        x = math_utils.clip(p.vel.x * dt, -max_velocity, max_velocity)
        y = math_utils.clip(p.vel.y * dt, -max_velocity, max_velocity)
        p.pos += vec2f(x, y)

    @classmethod
    def apply_velocity_to_array(cls, parray, dt, max_velocity=1000):
        for point_ in parray:
            cls.apply_velocity(point_, dt, max_velocity)
    

    @classmethod
    def tight_point_structure(cls, p: point, power=1.0, startpoint=None):
        if startpoint is None:
            startpoint = p

        for i, (neighbour, repeling_force, angle_range) in enumerate(zip(p.neighbors, p.repeling_forces, p.angle_ranges_rad)):
        
            unitvector = vec_utils.direction(p.pos, neighbour.pos)
            angle_to_neighbor = math.atan2(unitvector.y, unitvector.x)

            #if not (angle_range[0] <= angle_to_neighbor <= angle_range[1]):
            #    continue  # Skip this neighbor if the angle is outside the allowed range

            cls.apply_vector(
                p,
                (unitvector * power * neighbour.mass)/p.mass + -(unitvector * repeling_force / point_utils.distance(p, neighbour))
            )

            # Update the angle_range based on the new position
            p.angle_ranges_rad[i] = cls.update_angle_range(p, neighbour, angle_range)
            if neighbour is not startpoint:
                cls.tight_point_structure(neighbour, power, startpoint)

    @classmethod
    def update_angle_range(cls, p1: point, p2: point, angle_range: Tuple[float, float]) -> Tuple[float, float]:
        unitvector = vec_utils.direction(p1.pos, p2.pos)
        angle_to_neighbor = math.atan2(unitvector.y, unitvector.x)

        # Update the angle range based on the new positions
        new_angle_range = (angle_to_neighbor - 0.1, angle_to_neighbor + 0.1)  # Adjust the range as needed

        return new_angle_range