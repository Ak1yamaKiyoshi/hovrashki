import numpy as np
import pygame

from src.types import node2d, node2d_actions
from src.utils.object_acounting import EventHandler, ObjectStore
from src.events import event_quit


pygame.init()

TARGET_FPS = 60
WINDOW_WIDTH = 800
WINDOW_HEIGHT = 600
DEFAULT_FILL_COLOR = (60, 60, 60)
DAMPING = 0.95

class Game:
    def __init__(self):
        self.window = None
        self.event_handler  = None
        self.setup()
    
    def setup_objects(self):
        self.object_store.add(node2d)
    
    def setup_events(self):
        self.event_handler.register_event(event_quit, pygame.QUIT)
    

    def setup_pygame(self):
        self.window = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
        pygame.display.set_caption("")
    
    def setup_accounting(self):
        self.event_handler = EventHandler()
        self.object_store = ObjectStore()
    
    def setup(self):
        self.setup_accounting()
        self.setup_pygame()
        self.setup_events()
    
    def update(self, dt):
        for obj in self.object_store.get_objects():
            if isinstance(obj, node2d):
                node2d_actions.update(obj, DAMPING, dt)
    
    def draw(self):
        pass
    
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
        
Game().mainloop()