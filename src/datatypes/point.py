from dataclasses import dataclass
from typing import List, Tuple, Union
from .vec2f import vec2f

@dataclass
class point:
    pos: vec2f = vec2f()
    vel: vec2f = vec2f()
    mass: float = 1.0
    neighbors: List['point'] = None
    lenghts: List[float] = None
    angles_rad: List[float] = None
    angle_ranges_rad: List[Tuple[float]] = None
    repeling_forces: List[vec2f]= None


    def __post_init__(self):
        
        if self.neighbors is None:
            self.neighbors = []

        if self.lenghts is None:
            self.lenghts = []

        if self.angles_rad is None:
            self.angles_rad = []

        if self.angle_ranges_rad is None:
            self.angle_ranges_rad = []

        if self.repeling_forces  is None:
            self.repeling_forces = []
