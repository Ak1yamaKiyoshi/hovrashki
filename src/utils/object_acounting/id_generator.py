class IdGenerator:
    _instance = None
    _id = 0

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
        return cls._instance

    def __call__(self):
        self._id += 1
        return self._id
