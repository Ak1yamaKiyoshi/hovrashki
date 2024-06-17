

## Дані та логіка
Дані та їх використання повинні бути відділені. 
Тобто, умовно, точка повинна містити у собі лише дані
І ніяких функцій накшталт *перемістити точку до гравця


```py
@dataclass
class point:
  pos: Tuple[float, float]
  vel: Tuple[float, float]


class point_actions:
    @staticmethod
    def move_point(p: point, x:float, y:float):
        p.pos[0] = x
        p.pos[1] = y
```

## Об'єкти
Вирішуватиметься це