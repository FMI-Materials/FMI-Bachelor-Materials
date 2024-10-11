from geometry import Point, Polygon


def check_monotony(polygon: Polygon, axis='x') -> bool:
    mini = 1e9
    idx = 0
    for i in range(len(polygon.edges)):
        if polygon.edges[i].extract(axis) < mini:
            mini = polygon.edges[i].extract(axis)
            idx = i

    rising = True
    last = polygon.edges[idx].extract(axis)
    for j in range(1, len(polygon.edges)):
        i = (j + idx) % len(polygon.edges)
        current = polygon.edges[i].extract(axis)
        if current < last:
            rising = False
        if current > last and not rising:
            return False
        last = current

    return True


def main():
    # polygon = Polygon.read()
    polygon = Polygon([Point(4, 5), Point(5, 7), Point(5, 9), Point(2, 5), Point(4, 2), Point(6, 3)])
    # polygon = Polygon([Point(8, 7), Point(7, 5), Point(4, 5), Point(3, 9), Point(0, 1), Point(5, 2), Point(3, 3), Point(10, 3)])

    x_monotony = check_monotony(polygon, 'x')
    y_monotony = check_monotony(polygon, 'y')

    if x_monotony:
        print("Poligonul este x-monoton")
    else:
        print("Poligonul dat nu este x-monoton")
    if y_monotony:
        print("Poligonul este y-monoton")
    else:
        print("Poligonul dat nu este y-monoton")


if __name__ == '__main__':
    main()
