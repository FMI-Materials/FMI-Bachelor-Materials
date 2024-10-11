# multiple inheritance = when a child class is derived from more than one parent class

class Prey:
    def flee(self):
        print("This animal flees!")

class Predator:
    def hunt(self):
        print("This animal is hunting!")

class Rabbit(Prey):
    pass

class Hawk(Predator):
    pass

class Fish(Prey, Predator):
    pass

rabbit = Rabbit()
hawk = Hawk()
fish = Fish()

rabbit.flee()   # it prints "This animal flees!"
hawk.hunt()     # it prints "This animal is hunting!"
fish.flee()     # it prints "This animal flees!"
fish.hunt()     # it prints "This animal is hunting!"