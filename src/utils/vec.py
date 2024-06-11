import math
from ..datatypes import vec2f

class vec_utils:

    @staticmethod    
    def magnitude(self) -> float:
        return math.sqrt(self.x ** 2 + self.y ** 2)

    @classmethod
    def normalize(cls, self) -> vec2f:
        mag = cls.magnitude(self)
        if mag == 0:
            return vec2f(0, 0)
        return vec2f(self.x / mag, self.y / mag)

    @classmethod
    def direction(cls, vec1: vec2f, vec2: vec2f) -> vec2f:
        direction = vec2 - vec1
        return cls.normalize(direction)
