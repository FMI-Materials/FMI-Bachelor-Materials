from geometry import Point, Line, Polygon


def check_position(polygon: Polygon, start: Point):
    end = Point(999999, 9999999)
    intersections = 0

    for i in range(polygon.size):
        p1 = polygon.edges[i]
        p2 = polygon.edges[(i + 1) % polygon.size]
        if Point.compute_turn(p1, p2, start) == 0:
            return 0
        if Line(p1, p2).intersect(Line(start, end)):
            intersections += 1

    if intersections % 2 == 0:
        return -1
    return 1


def main():
    # polygon = Polygon.read()
    # q = Point.read("Q")

    polygon = Polygon ([Point(0, 6), Point(0, 0), Point(6, 0), Point(6, 6), Point(2, 6), Point(2, 2), Point(4, 2), Point(4, 5), Point(5, 5), Point(5, 1), Point(1, 1), Point(1, 6)])
    q = Point(3, 4)  # Punctul se află în interiorul poligonului
    # q = Point(7, 3)  # Punctul se află în exteriorul poligonului
    # q = Point(3, 2)  # Punctul se află pe latura poligonului

    pos = check_position(polygon, q)
    if pos == 1:
        print("Punctul se află în interiorul poligonului")
        return
    if pos == -1:
        print("Punctul se află în exteriorul poligonului")
        return
    print("Punctul se află pe latura poligonului")


if __name__ == '__main__':
    main()
