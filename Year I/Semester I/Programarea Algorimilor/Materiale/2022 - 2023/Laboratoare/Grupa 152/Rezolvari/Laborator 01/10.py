import math
a, b, c = map(int, input().split())
if not(a):
    if not(b):
        if not(c):
            print("Orice x este solutie")
        else:
            print("Nu exista solutii")
    else:
        print(f"Solutia este {-c / b}")
else:
    delta = b * b - 4 * a * c
    if not(delta):
        print(f"Exista solutia dubla {-b / (2 * a)}")
    elif delta < 0:
        print("Nu exista solutii reale")
    else:
        print(f"Exista doua solutii distince {(-b + math.sqrt(delta)) / (2 * a)} si {(-b - math.sqrt(delta)) / (2 * a)}")