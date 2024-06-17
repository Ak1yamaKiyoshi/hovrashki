
import pygame
from src.utils import ObjectStore
from .node2d import node2d, node2d_actions
import numpy as np
import time

from config import WINDOW_HEIGHT, WINDOW_WIDTH

class controllable(node2d):
    def __init__(self, id):
        super().__init__(self, id)
        self.jump_cooldown_s = 1
        self.dash_duration = 2
        self.dash_cooldown = 1
        self.last_dash = time.time() - self.dash_cooldown
        self.last_jump = time.time() - self.jump_cooldown_s

class controllable_actions(node2d_actions):
    @staticmethod
    def update(obj:controllable, damping, dt):
        obj.velocity += np.array([0, 9.81])
        obj.velocity = np.clip(obj.velocity, -550, 550)
        obj.position[0] = np.clip(obj.position[0], 0, WINDOW_WIDTH)
        obj.position[1] = np.clip(obj.position[1], 0, WINDOW_HEIGHT)
        node2d_actions.update(obj, damping, dt)

class controllable_events:
    @staticmethod
    def move(event):
        node = ObjectStore().get_objects()[0]
        key = pygame.key.get_pressed()
        current_time = time.time()

        if key[pygame.K_UP]:
            node.velocity  += np.array([0, -1]) * 30/5
        if key[pygame.K_DOWN]:
            node.velocity  += np.array([0, 1]) * 100/5
        if key[pygame.K_LEFT]:
            node.velocity  += np.array([-1, 0]) * 100/5
        if key[pygame.K_RIGHT]:
            node.velocity  += np.array([1, 0]) * 100/5
        if key[pygame.K_LSHIFT] and key[pygame.K_LEFT] or key[pygame.K_LSHIFT] and key[pygame.K_RIGHT]:
            if current_time - node.last_dash <  node.dash_duration:
                node.velocity  += node.velocity*np.array([2, 0])
            if current_time - node.last_dash > (node.dash_cooldown + node.dash_duration):
                node.last_dash = current_time

        if key[pygame.K_SPACE] and current_time - node.last_jump > node.jump_cooldown_s:
            node.velocity  += np.array([0, -1]) * 3000/5
            node.last_jump = current_time