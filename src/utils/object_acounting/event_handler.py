
from typing import Callable, Dict, Tuple
import pygame
#pygame.init()


class EventHandler:
    _instance = None
    _events_to_handle: Dict[int, Tuple[Callable[[], None], int]] = {}
    _next_id = 1

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super(EventHandler, cls).__new__(cls)
        return cls._instance

    def register_event(self, event_handler: Callable[[], None], event_type: int) -> int:
        event_id = self._next_id
        self._events_to_handle[event_id] = (event_handler, event_type)
        self._next_id += 1
        return event_id

    def remove_event(self, event_id: int):
        if event_id in self._events_to_handle:
            del self._events_to_handle[event_id]

    def handle_events(self):
        for event in pygame.event.get():
            for event_handler, event_type in self._events_to_handle.values():
                if event.type == event_type:
                    event_handler()
            if event.type == pygame.QUIT:
                running = False
                break