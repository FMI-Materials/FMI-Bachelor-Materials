import math

import numpy as np

from util import input_int


class Point:
    def __init__(self, x: float = None, y: float = None):
        self.x = x
        self.y = y

    def dist(self, point) -> float:
        return math.sqrt((self.x - point.x) ** 2 + (self.y - point.y) ** 2)

    def center(self, point):
        return Point((self.x + point.x) / 2, (self.y + point.y) / 2)

    def slope(self, point):
        if point.x - self.x == 0:
            return 1e9
        return (point.y - self.y) / (point.x - self.x)

    def extract(self, axis: str):
        if axis == 'x':
            return self.x
        return self.y

    @classmethod
    def read(cls, name="P"):
        print(f"Punctul {name}")
        x = input_int("x = ")
        y = input_int("y = ")
        return cls(x, y)

    @staticmethod
    def compute_turn(p, q, r):
        delta = np.array([[1, 1, 1], [p.x, q.x, r.x], [p.y, q.y, r.y]])
        det = np.linalg.det(delta)
        if det < 0:
            return -1
        if det > 0:
            return 1
        return 0

    @staticmethod
    def on_segment(p, q, r):
        if ((q.x <= max(p.x, r.x)) and (q.x >= min(p.x, r.x)) and
                (q.y <= max(p.y, r.y)) and (q.y >= min(p.y, r.y))):
            return True
        return False

    def __str__(self):
        return f"Point({round(self.x, 2)}, {round(self.y, 2)})"

    def __repr__(self):
        return f"Point({round(self.x, 2)}, {round(self.y, 2)})"


class HalfPlane:
    vertical = False

    def __init__(self, x: int, y: int, b: int):
        if (abs(x) <= 0 and abs(y) <= 0) or (abs(x) > 0 and abs(y) > 0):
            Exception("Semiplan invalid")
        if abs(x) <= 0:
            self.vertical = True
            self.a = y
        else:
            self.a = x
        self.b = b

    @classmethod
    def read(cls, name="H"):
        print(f"Semiplanul {name}")
        a = input_int("a = ")
        b = input_int("b = ")
        c = input_int("c = ")
        return cls(a, b, c)

    def contains_point(self, point: Point):
        if self.vertical:
            return self.a * point.y + self.b < 0
        return self.a * point.x + self.b < 0

    def get_line(self):
        return -self.b / self.a

    def __str__(self):
        return f"HalfPlane(a = {self.a}, b = {self.b})"

    def __repr__(self):
        return f"HalfPlane(a = {self.a}, b = {self.b})"
