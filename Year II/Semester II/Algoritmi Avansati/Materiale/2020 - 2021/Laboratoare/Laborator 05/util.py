def input_int(out):
    while True:
        try:
            return int(input(out))
        except Exception:
            print("Input invalid")


def read_point(name):
    print(f"Punctul {name}")
    x = input_int("x = ")
    y = input_int("y = ")
    return x, y


def read_points():
    n = input_int("n = ")
    points = list()
    for i in range(n):
        points.append(read_point(f"p{i}"))
    return points
