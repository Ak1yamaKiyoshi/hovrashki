

class ObjectStore:
    _instance = None
    _objects = []

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
        return cls._instance

    def add(self, obj):
        self._objects.append(obj)

    def get_objects(self):
        return self._objects
