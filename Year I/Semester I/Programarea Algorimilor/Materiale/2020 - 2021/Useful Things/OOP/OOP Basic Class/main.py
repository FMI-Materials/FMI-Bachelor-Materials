from car import Car

car_test = Car("Mercedes-Benz", "S-Klasse", 2022, "black")
car_test2 = Car("Lamborghini", "Urus", 2021, "red")

print(car_test.make)
print(car_test.model)
print(car_test.year)
print(car_test.color)

car_test.drive()
car_test.stop()

# modifiy class variable
car_test.wheels = 2

print(car_test.wheels) # it prints 2 now
print(car_test2.wheels) # it prints 4

# now we modified the wheels for every object
Car.wheels = 2

print(car_test.wheels) # it prints 2 now
print(car_test2.wheels) # it prints 2 now