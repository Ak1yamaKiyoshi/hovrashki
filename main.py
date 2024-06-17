import numpy as np
import pygame

from src.types import node2d, node2d_actions, controllable_events, controllable, controllable_actions
from src.utils.object_acounting import EventHandler, ObjectStore, IdGenerator
from src.events import event_quit

from config import *



pygame.init()
class Game:
    def __init__(self):
        self.window = None
        self.event_handler  = None
        self.setup()
    
    def setup_objects(self):
        self.object_store.add(controllable(self.id_generator()))
    
    def setup_events(self):
        self.event_handler.register_event(event_quit, pygame.QUIT)
        self.event_handler.register_event(controllable_events.move, -1)

    def setup_pygame(self):
        self.window = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
        pygame.display.set_caption("")
    
    def setup_accounting(self):
        self.id_generator = IdGenerator()
        self.event_handler = EventHandler()
        self.object_store = ObjectStore()
    
    def setup(self):
        self.setup_pygame()
        self.setup_accounting()
        self.setup_events()
        self.setup_objects()
    
    def update(self, dt):
        for obj in self.object_store.get_objects():
            if type(obj) == controllable:
                controllable_actions.update(obj, DAMPING, dt)

    def draw(self):
        for obj in self.object_store.get_objects():
            if type(obj) == controllable:
                controllable_actions.draw(obj, self.window)
    
    def mainloop(self):
        running = True
        clock = pygame.time.Clock()
        previous_time = pygame.time.get_ticks()
        
        while running:
            self.event_handler.handle_events()

            current_time = pygame.time.get_ticks()
            delta_time = (current_time - previous_time) / 1000.0 
            previous_time = current_time

            self.update(delta_time)
            self.window.fill(DEFAULT_FILL_COLOR)
            self.draw()
            
            pygame.display.flip()
            clock.tick(TARGET_FPS) 
        pygame.quit()
        
if __name__ == "__main__":
    Game().mainloop()