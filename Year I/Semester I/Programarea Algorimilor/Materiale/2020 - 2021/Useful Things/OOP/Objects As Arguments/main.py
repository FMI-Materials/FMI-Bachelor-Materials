class Car:
    color = None

class Motorcycle:
    color = None

def change_color(vehicle, color):
    vehicle.color = color

car_1 = Car()
car_2 = Car()
car_3 = Car()

bike_1 = Motorcycle()

change_color(car_1, "red")
change_color(car_2, "white")
change_color(car_3, "blue")
change_color(bike_1, "black")

print(car_1.color)  # it prints "red"
print(car_2.color)  # it prints "white"
print(car_3.color)  # it prints "blue"
print(bike_1.color) # it prints "black"