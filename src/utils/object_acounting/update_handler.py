from typing import Callable, Dict

class UpdateHandler:
    _instance = None
    _update_objects: Dict[int, Callable[[], None]] = {}
    _next_id = 1

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super(UpdateHandler, cls).__new__(cls)
        return cls._instance

    def register_update(self, update_func: Callable[[], None]) -> int:
        update_id = self._next_id
        self._update_objects[update_id] = update_func
        self._next_id += 1
        return update_id

    def remove_update(self, update_id: int):
        if update_id in self._update_objects:
            del self._update_objects[update_id]

    def update(self):
        for update_func in self._update_objects.values():
            update_func()