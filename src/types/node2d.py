from dataclasses import dataclass
import numpy as np

class node2d:
    def __init__(self, id: int, angle: float = 0.0, velocity: np.ndarray = None, position: np.ndarray = None, weight: float = 1.0) -> None:
        self.id = id
        self.angle = angle
        self.velocity = np.zeros((1, 2)) if velocity is None else velocity
        self.position = np.zeros((1, 2)) if position is None else position
        self.weight = weight

    def __hash__(self) -> int:
        return hash(self.id)

    def __eq__(self, other: 'node2d') -> bool:
        if not isinstance(other, node2d):
            return NotImplemented
        return (
            self.id == other.id
            and np.array_equal(self.velocity, other.velocity)
            and np.array_equal(self.position, other.position)
            and self.angle == other.angle
            and self.weight == other.weight)


class node2d_actions:
    @staticmethod
    def update(node: node2d, damping: float, delta_time: float):
        node.velocity = node.velocity * np.power(damping, delta_time)
        node.position += node.velocity * delta_time