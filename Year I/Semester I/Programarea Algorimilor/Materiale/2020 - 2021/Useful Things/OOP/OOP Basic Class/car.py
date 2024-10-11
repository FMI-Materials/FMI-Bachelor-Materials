class Car:

    wheels = 4 # class variable

    # Constructor
    def __init__(self, make, model, year, color):
        self.make = make    # instance variable
        self.model = model  # instance variable
        self.year = year    # instance variable
        self.color = color  # instance variable

    def drive(self):
        print("This car " + self.model + " is driving!")

    def stop(self):
        print("This car " + self.model + " is stopped!")
