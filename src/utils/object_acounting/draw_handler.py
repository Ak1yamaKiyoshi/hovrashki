from typing import Callable, Dict

class DrawHandler:
    _instance = None
    _draw_objects: Dict[int, Callable[[], None]] = {}
    _next_id = 1

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super(DrawHandler, cls).__new__(cls)
        return cls._instance

    def register_draw(self, draw_func: Callable[[], None]) -> int:
        draw_id = self._next_id
        self._draw_objects[draw_id] = draw_func
        self._next_id += 1
        return draw_id

    def remove_draw(self, draw_id: int):
        if draw_id in self._draw_objects:
            del self._draw_objects[draw_id]

    def draw(self):
        for draw_func in self._draw_objects.values():
            draw_func()
