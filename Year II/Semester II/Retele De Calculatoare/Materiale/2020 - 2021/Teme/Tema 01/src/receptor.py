# receptor Reliable UDP
import random

from helper import *
from argparse import ArgumentParser
import socket
import logging

logging.basicConfig(format=u'[LINE:%(lineno)d]# %(levelname)-8s [%(asctime)s]  %(message)s', level=logging.NOTSET)


def send_confirmation(sock, emitator, ack_nr, window):
    header_fara_checksum = create_header_receptor(ack_nr, 0, window)

    checksum = calculeaza_checksum(header_fara_checksum)

    header_cu_checksum = create_header_receptor(ack_nr, checksum, window)

    sock.sendto(header_cu_checksum, emitator)
    pass


def main():
    parser = ArgumentParser(usage=__file__ + ' '
                                             '-p/--port PORT'
                                             '-f/--fisier FILE_PATH',
                            description='Reliable UDP Receptor')

    parser.add_argument('-p', '--port',
                        dest='port',
                        default='10000',
                        help='Portul pe care sa porneasca receptorul pentru a primi mesaje')

    parser.add_argument('-f', '--fisier',
                        dest='fisier',
                        default='output.txt',
                        help='Calea catre fisierul in care se vor scrie octetii primiti')

    # Parse arguments
    args = vars(parser.parse_args())
    port = int(args['port'])
    fisier = args['fisier']

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, proto=socket.IPPROTO_UDP)

    adresa = DEFAULT_ADDRESS
    server_address = (adresa, port)
    sock.bind(server_address)
    window = random.randint(1, 5)
    logging.info("The server has started on %s and port %d", adresa, port)
    logging.info("Window has been set to %d", window)

    ack_nrs = set()

    file_out = None

    logging.info('Waiting for messages..')

    while True:
        data, address = sock.recvfrom(MAX_SEGMENT + 8)
        '''
        TODO: pentru fiecare mesaj primit
        1. verificam checksum
        2. parsam headerul de la emitator
        3. trimitem confirmari cu ack = seq_nr+1 daca mesajul e de tip S sau F
                               cu ack = seq_nr daca mesajul e de tip P
        4. scriem intr-un fisier octetii primiti
        5. verificam la sfarsit ca fisierul este la fel cu cel trimis de emitator
        '''
        if verifica_checksum(data) is True:
            header = data[:8]
            mesaj = data[8:]

            seq_nr, checksum, flags = parse_header_emitator(header)

            ack_nr = seq_nr

            if flags == 'S':
                logging.info('Connection initialized')
                ack_nr = seq_nr + 1
                ack_nrs.clear()
                file_out = open_data_file(fisier, "wb")
            elif flags == 'F':
                logging.info('Connection closed')
                ack_nr = seq_nr + 1
                file_out.close()
            elif flags == 'P':
                logging.info('Message received. Seq no: %d, message size: %d bytes.', seq_nr, len(mesaj))
                if seq_nr not in ack_nrs:
                    file_out.write(mesaj)
                    ack_nrs.add(seq_nr)
                # Generate a random window
                window = random.randint(1, 5)

            send_confirmation(sock, address, ack_nr, window)


if __name__ == '__main__':
    main()
