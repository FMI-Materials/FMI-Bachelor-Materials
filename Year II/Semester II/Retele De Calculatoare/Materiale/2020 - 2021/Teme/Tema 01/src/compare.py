from helper import *
from argparse import ArgumentParser
import logging

logging.basicConfig(format=u'[LINE:%(lineno)d]# %(levelname)-8s [%(asctime)s]  %(message)s', level=logging.NOTSET)


def main():
    parser = ArgumentParser(usage=__file__ + ' '
                                             '-f1/--file1 FILE_PATH'
                                             '-f2/--file2 FILE_PATH',
                            description='Files comparator')

    parser.add_argument('-f1', '--file1',
                        dest='file1',
                        default='test.txt',
                        help='File 1')

    parser.add_argument('-f2', '--file2',
                        dest='file2',
                        default='output.txt',
                        help='File 2')

    args = vars(parser.parse_args())

    file_1 = open_data_file(args["file1"], "r", False)
    file_2 = open_data_file(args["file2"], "r", False)

    content_1 = file_1.read()
    content_2 = file_2.read()

    if len(content_1) > len(content_2):
        logging.warning("The first file has %d more characters" % (len(content_1) - len(content_2)))
    elif len(content_1) < len(content_2):
        logging.warning("The first file has %d less characters" % (len(content_2) - len(content_1)))
    elif content_1 == content_2:
        logging.info("Files are the same! Congrats!")
    else:
        logging.warning("File contents are different!")

    file_1.close()
    file_2.close()


if __name__ == '__main__':
    main()
