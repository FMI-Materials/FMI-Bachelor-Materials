# Prevents a user from creating an object of that class
# + compels a user to override abstract methods in a child class

# abstract class = a class which containts one or more abstract methods.
# abstract method = a method that has a declaration but does not have an implementation.

from abc import ABC, abstractmethod

class Vehicle(ABC):
    @abstractmethod
    def go(self):
        pass

    @abstractmethod
    def stop(self):
        pass

class Car(Vehicle):
    def go(self):
        print("You drive the car!")

    def stop(self):
        print("This car is stopped!")

class Motorcycle(Vehicle):
    def go(self):
        print("You ride the motorcycle!")

    def stop(self):
        print("This motorcycle is stopped!")

# vehicle = Vehicle()
car = Car()
motorcycle = Motorcycle()

# vehicle.go()
car.go()            # it prints "You drive the car!"
motorcycle.go()     # it prints "You ride the motorcycle!"

car.stop()          # it prints "This car is stopped!"
motorcycle.stop()   # it prints "This motorcycle is stopped!"