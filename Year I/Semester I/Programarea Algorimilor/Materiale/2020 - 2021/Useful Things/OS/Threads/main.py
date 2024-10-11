import threading
import time


def eat_breakfast():
    time.sleep(3)
    print("You eat breakfast!")


def drink_coffe():
    time.sleep(4)
    print("You drank coffe!")


def study():
    time.sleep(5)
    print("You finish study!")


x = threading.Thread(target=eat_breakfast, args=())
x.start()

y = threading.Thread(target=drink_coffe, args=())
y.start()

z = threading.Thread(target=study, args=())
z.start()

# eat_breakfast()
# drink_coffe()
# study()

x.join()
y.join()
z.join()

print(threading.active_count())
print(threading.enumerate())
print(time.perf_counter())
