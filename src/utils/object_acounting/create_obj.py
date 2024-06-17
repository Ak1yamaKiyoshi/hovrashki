from .id_generator import IdGenerator
from .store import ObjectStore

def create_object(T, *args):
    id_generator = IdGenerator()
    obj_id = id_generator()
    
    obj = T(obj_id, *args)
    store = ObjectStore()
    store.add(obj)
    
    return obj