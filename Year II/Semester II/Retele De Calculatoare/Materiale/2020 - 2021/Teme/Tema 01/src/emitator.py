# emitator Reliable UDP
import random
import traceback

from helper import *
from argparse import ArgumentParser
import socket
import time
import logging
from datetime import datetime

logging.basicConfig(format=u'[LINE:%(lineno)d]# %(levelname)-8s [%(asctime)s]  %(message)s', level=logging.NOTSET)

RTO = 3
SRTT = 0

def connect(sock, adresa_receptor):
    global SRTT, RTO

    seq_nr = random.randint(0, MAX_UINT32)
    segment = b''
    seq_nr = (seq_nr + len(segment)) % MAX_UINT32
    flags = 'S'

    initial_time = datetime.now().timestamp()

    octeti_header_fara_checksum = create_header_emitator(seq_nr, 0, flags)
    mesaj = octeti_header_fara_checksum + segment
    checksum = calculeaza_checksum(mesaj)
    octeti_header_cu_checksum = create_header_emitator(seq_nr, checksum, flags)
    mesaj = octeti_header_cu_checksum + segment

    sock.settimeout(RTO)
    sock.sendto(mesaj, adresa_receptor)

    try:
        data, server = sock.recvfrom(MAX_SEGMENT)
        SRTT = datetime.now().timestamp() - initial_time
        RTO = calculate_rto(SRTT)
    except socket.timeout as e:
        logging.warning("Connection timed out, retrying...")
        RTO *= 2
        return connect(sock, adresa_receptor)

    if verifica_checksum(data) is False:
        return -1, -1

    ack_nr, checksum, window = parse_header_receptor(data)

    return ack_nr, window


def finalize(sock, adresa_receptor, seq_nr):
    global RTO, SRTT

    flags = 'F'
    segment = b''
    seq_nr = (seq_nr + len(segment)) % MAX_UINT32

    octeti_header_fara_checksum = create_header_emitator(seq_nr, 0, flags)
    mesaj = octeti_header_fara_checksum + segment
    checksum = calculeaza_checksum(mesaj)
    octeti_header_cu_checksum = create_header_emitator(seq_nr, checksum, flags)
    mesaj = octeti_header_cu_checksum + segment

    sock.settimeout(RTO)
    sock.sendto(mesaj, adresa_receptor)

    try:
        data, server = sock.recvfrom(MAX_SEGMENT)
    except socket.timeout as e:
        logging.warning("Closing connection timed out, retrying...")
        # Double new RTO
        RTO *= 2
        return finalize(sock, adresa_receptor, seq_nr)

    if verifica_checksum(data) is False:
        return -1, -1

    ack_nr, checksum, window = parse_header_receptor(data)

    return ack_nr, window


def send(sock, adresa_receptor, seq_nr, window, octeti_payload):
    global RTO, SRTT

    flags = 'P'

    current_window = window
    current_seq_nr = seq_nr

    ack_nrs = set()
    seq_nrs = set()
    initial_time = datetime.now().timestamp()

    for i in range(window):
        current_seq_nr = (current_seq_nr + len(octeti_payload[i])) % MAX_UINT32
        seq_nrs.add(current_seq_nr)
        octeti_header_fara_checksum = create_header_emitator(current_seq_nr, 0, flags)
        mesaj = octeti_header_fara_checksum + octeti_payload[i]
        checksum = calculeaza_checksum(mesaj)
        octeti_header_cu_checksum = create_header_emitator(current_seq_nr, checksum, flags)
        mesaj = octeti_header_cu_checksum + octeti_payload[i]

        sock.settimeout(RTO)
        sock.sendto(mesaj, adresa_receptor)

    for i in range(window):
        try:
            data, server = sock.recvfrom(MAX_SEGMENT)

            # Calculate new RTO
            SRTT = datetime.now().timestamp() - initial_time
            RTO = calculate_rto(SRTT)

            # Verify checksum
            if verifica_checksum(data):
                ack_nr, _, current_window = parse_header_receptor(data)
                # Remember ack numbers - only if their are correct
                if ack_nr in seq_nrs:
                    ack_nrs.add(ack_nr)
        except socket.timeout as e:
            logging.warning("Socket timed out on payload %d ", i + 1)

    # If at least one package was lost, resend entire window
    if len(ack_nrs) != len(seq_nrs):
        # Double new RTO
        RTO *= 2
        logging.warning("Missed %d package(s), resending window...", abs(len(seq_nrs) - len(ack_nrs)))
        return send(sock, adresa_receptor, seq_nr, window, octeti_payload)

    return max(ack_nrs), current_window


def main():
    parser = ArgumentParser(usage=__file__ + ' '
                                             '-a/--adresa IP '
                                             '-p/--port PORT'
                                             '-f/--fisier FILE_PATH',
                            description='Reliable UDP Emitter')

    parser.add_argument('-a', '--adresa',
                        dest='adresa',
                        default=DEFAULT_ADDRESS,
                        help='Adresa IP a receptorului (IP-ul containerului, localhost sau altceva)')

    parser.add_argument('-p', '--port',
                        dest='port',
                        default='10000',
                        help='Portul pe care asculta receptorul pentru mesaje')

    parser.add_argument('-f', '--fisier',
                        dest='fisier',
                        default='test.txt',
                        help='Calea catre fisierul care urmeaza a fi trimis')

    # Parse arguments
    args = vars(parser.parse_args())

    ip_receptor = args['adresa']
    port_receptor = int(args['port'])
    fisier = args['fisier']

    adresa_receptor = (ip_receptor, port_receptor)
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, proto=socket.IPPROTO_UDP)
    # setam timeout pe socket in cazul in care recvfrom nu primeste nimic in 3 secunde
    sock.settimeout(RTO)
    try:
        '''
        TODO:
        1. initializeaza conexiune cu receptor
        2. deschide fisier, citeste segmente de octeti
        3. trimite `window` segmente catre receptor,
         send trebuie sa trimită o fereastră de window segmente
         până primșete confirmarea primirii tuturor segmentelor
        4. asteapta confirmarea segmentelor, 
        in cazul pierderilor, retransmite fereastra sau doar segmentele lipsa
        5. in functie de diferenta de timp dintre trimitere si receptia confirmarii,
        ajusteaza timeout
        6. la finalul trimiterilor, notifica receptorul ca fisierul s-a incheiat
        '''
        seq_nr, window = connect(sock, adresa_receptor)
        logging.info("Connection initialized")
        logging.info('Ack Nr: "%d"', seq_nr)
        logging.info('Window: "%d"', window)

        with open_data_file(fisier, 'rb') as file_in:
            segments = read_segments(file_in, window)
            while len(segments) > 0:
                window = min(len(segments), window)
                seq_nr, current_window = send(sock, adresa_receptor, seq_nr, window, segments)
                logging.info("%d messages send, %d windows available", window, current_window)
                logging.info("Current seq number: %d", seq_nr)
                window = current_window
                segments = read_segments(file_in, window)

        finalize(sock, adresa_receptor, seq_nr)
        logging.info("Connection closed")
    except Exception as e:
        logging.exception(traceback.format_exc())
        sock.close()


if __name__ == '__main__':
    main()
