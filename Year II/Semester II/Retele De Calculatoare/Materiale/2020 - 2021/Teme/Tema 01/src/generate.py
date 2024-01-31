from helper import *


def main():
    with open_data_file("test.txt", "w", False) as file_out:
        for i in range(4000):
            file_out.write("This is line no. %d, hello world!\n" % i)
        file_out.write("\n\nFile ends here!")


if __name__ == '__main__':
    main()
