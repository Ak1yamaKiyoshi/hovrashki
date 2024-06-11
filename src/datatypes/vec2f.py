from dataclasses import dataclass
from typing import List, Tuple, Union

@dataclass
class vec2f:
    x: float = 0.0
    y: float = 0.0

    def __add__(self, other: Union['vec2f', float]) -> 'vec2f':
        if isinstance(other, vec2f):
            return vec2f(self.x + other.x, self.y + other.y)
        elif isinstance(other, float):
            return vec2f(self.x + other, self.y + other)
        else:
            raise TypeError(f"Unsupported operand type(s) for +: 'vec2f' and '{type(other)}'")

    def __sub__(self, other: Union['vec2f', float]) -> 'vec2f':
        if isinstance(other, vec2f):
            return vec2f(self.x - other.x, self.y - other.y)
        elif isinstance(other, float):
            return vec2f(self.x - other, self.y - other)
        else:
            raise TypeError(f"Unsupported operand type(s) for -: 'vec2f' and '{type(other)}'")

    def __mul__(self, other: Union['vec2f', float]) -> 'vec2f':
        if isinstance(other, vec2f):
            return vec2f(self.x * other.x, self.y * other.y)
        elif isinstance(other, float):
            return vec2f(self.x * other, self.y * other)
        else:
            raise TypeError(f"Unsupported operand type(s) for *: 'vec2f' and '{type(other)}'")

    def __truediv__(self, other: float) -> 'vec2f':
        if isinstance(other, float):
            return vec2f(self.x / other, self.y / other)
        else:
            raise TypeError(f"Unsupported operand type(s) for /: 'vec2f' and '{type(other)}'")

    def __neg__(self) -> 'vec2f':
        return vec2f(-self.x, -self.y)

    def __eq__(self, other: 'vec2f') -> bool:
        if isinstance(other, vec2f):
            return self.x == other.x and self.y == other.y
        else:
            raise TypeError(f"Unsupported operand type(s) for ==: 'vec2f' and '{type(other)}'")
    def __pow__(self, other):
        if isinstance(other, float):
            return vec2f(self.x ** other, self.y ** other)
        else:
            raise TypeError(f"Unsupported operand type(s) for **: 'vec2f' and '{type(other)}'")
