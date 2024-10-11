from geometry import Point, Circle, Triangle


def check_position_to_circle(triangle: Triangle, D: Point) -> int:
    circumscribed = Circle.get_circumscribed_from_triangle(triangle)
    dist = circumscribed.U.dist(D)
    if round(dist - circumscribed.r, 2) == 0:
        return 0
    if dist < circumscribed.r:
        return -1
    return 1


def main():
    """
    A = Point.read("A")
    B = Point.read("B")
    C = Point.read("C")
    D = Point.read("D")
    """
    A = Point(7, 3)
    B = Point(5, 5)
    C = Point(3, 3)
    D = Point(4, 2)  # in interior
    # D = Point(5, 1)  # pe cerc
    # D = Point(7, 1)  # in exterior

    pos = check_position_to_circle(A, B, C, D)
    if pos == -1:
        print("Punctul se află în interiorul cercului circumscris")
        return
    if pos == 1:
        print("Punctul se află în exteriorul cercului circumscris")
        return
    print("Punctul se află pe latura cercului circumscris")


if __name__ == '__main__':
    main()
