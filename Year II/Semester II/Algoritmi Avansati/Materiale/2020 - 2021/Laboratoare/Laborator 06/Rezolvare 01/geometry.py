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


class Polygon:
    def __init__(self, edges: [Point]):
        self.size = len(edges)
        self.edges = edges

    @classmethod
    def read(cls):
        n = input_int("n = ")
        points = []
        for i in range(n):
            points.append(Point.read(str(i)))
        return cls(points)

    def __str__(self):
        return f"Polygon({', '.join([str(point) for point in self.edges])})"

    def __repr__(self):
        return f"Polygon({', '.join([str(point) for point in self.edges])})"


class Line:
    def __init__(self, A: Point, B: Point):
        self.A = A
        self.B = B

    def dist(self) -> float:
        return self.A.dist(self.B)

    def center(self) -> Point:
        return self.A.center(self.B)

    def slope(self):
        return self.A.slope(self.B)

    def intersect(self, line) -> bool:
        slope1 = self.slope()
        slope2 = line.slope()

        if slope1 == slope2:
            return False

        t1 = Point.compute_turn(self.A, self.B, line.A)
        t2 = Point.compute_turn(self.A, self.B, line.B)
        t3 = Point.compute_turn(line.A, line.B, self.A)
        t4 = Point.compute_turn(line.A, line.B, self.B)

        if (t1 != t2) and (t3 != t4):
            return True
        if (t1 == 0) and Point.on_segment(self.A, line.A, self.B):
            return True
        if (t2 == 0) and Point.on_segment(self.A, line.B, self.B):
            return True
        if (t3 == 0) and Point.on_segment(line.A, self.A, line.B):
            return True
        if (t4 == 0) and Point.on_segment(line.A, self.B, line.B):
            return True

        return False

    def __str__(self):
        return f"Line({self.A}, {self.B})"

class Triangle:
    def __init__(self, A: Point, B: Point, C: Point):
        self.A = A
        self.B = B
        self.C = C

    def __str__(self):
        return f"Triangle({self.A}, {self.B}, {self.C})"

    def __repr__(self):
        return f"Triangle({self.A}, {self.B}, {self.C})"

class Circle:
    def __init__(self, U: Point, r: float):
        self.U = U
        self.r = r

    @classmethod
    def get_circumscribed_from_triangle(cls, triangle: Triangle):
        A = triangle.A
        B = triangle.B
        C = triangle.C

        AB = A.dist(B)
        BC = B.dist(C)
        AC = A.dist(C)

        D = 2 * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y))

        U = Point()
        U.x = ((A.x ** 2 + A.y ** 2) * (B.y - C.y) + (B.x ** 2 + B.y ** 2) * (C.y - A.y) + (C.x ** 2 + C.y ** 2) * (
                    A.y - B.y)) / D
        U.y = ((A.x ** 2 + A.y ** 2) * (C.x - B.x) + (B.x ** 2 + B.y ** 2) * (A.x - C.x) + (C.x ** 2 + C.y ** 2) * (
                    B.x - A.x)) / D

        r = (AB * BC * AC) / abs(D)
        return cls(U, r)

    def __str__(self):
        return f"Circle({self.U}, {round(self.r, 2)})"

    def __repr__(self):
        return f"Circle({self.U}, {round(self.r, 2)})"



