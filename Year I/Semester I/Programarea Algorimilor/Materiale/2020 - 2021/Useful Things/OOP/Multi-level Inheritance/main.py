# multi-level inheritance = when a derived (child) class inherits another derived (child) class

class Organism:
    alive = True

class Animal(Organism):
    def eat(self):
        print("This animal is eating!")

class Dog(Animal):
    def bark(self):
        print("This dog is barking!")

dog = Dog()

print(dog.alive)    # it prints True
                    # inherited from the Organism class

dog.eat()           # it prints "This animal is eating!"
                    # inherited from the Animal class

dog.bark()          # it prints "This dog is barking!"
                    # defined in Dog class