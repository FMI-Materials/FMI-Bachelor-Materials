from multiprocessing import Process, cpu_count
import time

def counter(num):
    count = 0
    while count < num:
        count += 1

def main():
    print(cpu_count())

    process_1 = Process(target=counter, args=(1250000,))
    process_2 = Process(target=counter, args=(1250000,))
    process_3 = Process(target=counter, args=(1250000,))
    process_4 = Process(target=counter, args=(1250000,))
    process_5 = Process(target=counter, args=(1250000,))
    process_6 = Process(target=counter, args=(1250000,))
    process_7 = Process(target=counter, args=(1250000,))
    process_8 = Process(target=counter, args=(1250000,))

    process_1.start()
    process_2.start()
    process_3.start()
    process_4.start()
    process_5.start()
    process_6.start()
    process_7.start()
    process_8.start()

    process_1.join()
    process_2.join()
    process_3.join()
    process_4.join()
    process_5.join()
    process_6.join()
    process_7.join()
    process_8.join()

    print("Finished in: ", time.perf_counter(), " seconds.")

if __name__ == '__main__':
    main()