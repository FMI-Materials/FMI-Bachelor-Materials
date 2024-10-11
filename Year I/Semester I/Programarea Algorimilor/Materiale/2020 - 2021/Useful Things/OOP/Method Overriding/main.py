class Animal:
    def eat(self):
        print("This animal is eating!")

# class Rabbit(Animal):
#     pass

# now we rewrite the eat function

class Rabbit(Animal):
    def eat(self):
        print("This rabbit is eating a carrot!")

rabbit = Rabbit()

rabbit.eat()    # it prints "This animal is eating!"
                # after we rewrited eat function for Rabbit class it will prints "This rabbit is eating a carrot!"