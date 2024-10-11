from ex3 import *


def main():
    """
    A = Point.read("A")
    B = Point.read("B")
    C = Point.read("C")
    D = Point.read("D")
    """
    A = Point(1, 1)
    B = Point(3, 1)
    C = Point(2, 4)
    D = Point(1, 2)

    if check_position_to_circle(Triangle(A, B, C), D) == -1:
        print("Muchia AC este ilegala")
    else:
        print("Muchia AC este legala")

    if check_position_to_circle(Triangle(A, B, D), C) == -1:
        print("Muchia BD este ilegala")
    else:
        print("Muchia BD este legala")


if __name__ == '__main__':
    main()
