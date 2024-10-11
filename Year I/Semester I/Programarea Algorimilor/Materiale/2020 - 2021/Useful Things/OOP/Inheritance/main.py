class Animal:
    alive = True

    def eat(self):
        print("This animal is eating!")

    def sleep(self):
        print("This animal is sleeping!")

class Rabbit(Animal):
    def run(self):
        print("This rabbit is running!")

class Fish(Animal):
    def swim(self):
        print("This fish is swimming!")

class Hawk(Animal):
    def fly(self):
        print("This hawk is flying!")

rabbit = Rabbit()
fish = Fish()
hawk = Hawk()

print(rabbit.alive)     # it prints True
fish.eat()              # it prints "This animal is eating!"
hawk.sleep()            # it prints "This animal is sleeping!"

rabbit.run()            # it prints "This rabbit is running!"
fish.swim()             # it prints "This fish is swimming!"
hawk.fly()              # it prints "This hawk is flying!"
