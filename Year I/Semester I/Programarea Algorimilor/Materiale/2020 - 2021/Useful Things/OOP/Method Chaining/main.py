# method chaining = calling multiple methods sequentially,
#                   each call performs an action on the same object and returns self

class Car:
    def turn_on(self):
        print("You start the engine!")
        return self

    def drive(self):
        print("You drive the car!")
        return self

    def brake(self):
        print("You step on the brakes!")
        return self

    def turn_off(self):
        print("You turn off the engine!")
        return self

car = Car()

# NOTE: We need return self
car.turn_on().drive()                               # it prints "You start the engine!"
                                                    #           "You drive the car!"

car.brake().turn_off()                              # it prints "You step on the brakes!"
                                                    #           "You turn off the engine!"

car.turn_on().drive().brake().turn_off()            # it prints "You step on the brakes!"
                                                    #           "You turn off the engine!"
                                                    #           "You step on the brakes!"
                                                    #           "You turn off the engine!"

# another way to write it
# it prints the same

car.turn_on()\
    .drive()\
    .brake()\
    .turn_off()

# it more easy to read it now :)