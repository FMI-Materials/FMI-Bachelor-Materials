import struct
from os import getcwd

MAX_UINT32 = 0xFFFFFFFF
MAX_BITI_CHECKSUM = 16
MAX_NUM_CHECKSUM = (1 << MAX_BITI_CHECKSUM) - 1
MAX_SEGMENT = 1400

ALPHA = 0.9
UBOUND = 10
LBOUND = 0.1
BETA = 1.5

DOCKER_MODE = True
DEFAULT_ADDRESS = "198.8.0.2" if DOCKER_MODE else "127.0.0.1"


def create_header_emitator(seq_nr, checksum, flags='S'):
    spf = 0
    if flags == 'S':
        spf = 0b100
    elif flags == 'P':
        spf = 0b010
    elif flags == 'F':
        spf = 0b001
    spf_zero = spf << 13  # muta cei trei biti cu 13 pozitii la stanga

    octeti = struct.pack("!LHH", seq_nr, checksum, spf_zero)
    return octeti


def parse_header_emitator(octeti):
    seq_nr, checksum, spf_zero = struct.unpack("!LHH", octeti)
    flags = ''
    spf = int(spf_zero) >> 13
    if spf & 0b100:
        flags = 'S'
    elif spf & 0b001:
        flags = 'F'
    elif spf & 0b010:
        flags = 'P'
    return seq_nr, checksum, flags


def create_header_receptor(ack_nr, checksum, window):
    octeti = struct.pack("!LHH", ack_nr, checksum, window)
    return octeti


def parse_header_receptor(octeti):
    ack_nr, checksum, window = struct.unpack("!LHH", octeti)
    return ack_nr, checksum, window


def read_segment(file_descriptor):
    return file_descriptor.read(MAX_SEGMENT)


def read_segments(file_descriptor, window):
    segments = []
    segment = read_segment(file_descriptor)
    while segment:
        segments.append(segment)
        window -= 1
        if window == 0:
            break
        segment = read_segment(file_descriptor)
    return segments


def calculeaza_checksum(octeti):
    checksum = 0

    if len(octeti) % 2:
        octeti += b'\x00'

    for i in range(0, len(octeti), 2):
        checksum += (octeti[i] << 8) + octeti[i + 1]

    checksum = checksum % MAX_NUM_CHECKSUM

    return MAX_NUM_CHECKSUM - checksum


def verifica_checksum(octeti):
    if calculeaza_checksum(octeti) == MAX_NUM_CHECKSUM:
        return True
    return False


def open_data_file(name, option, docker_mode=DOCKER_MODE):
    if docker_mode:
        return open("/elocal/data/" + name, option)
    else:
        return open(getcwd() + "/../data/" + name, option)


def calculate_srtt(srtt, rtt):
    return ALPHA * srtt + (1 - ALPHA) * rtt


def calculate_rto(srtt):
    lb = max(LBOUND, BETA * srtt)
    if lb > UBOUND:
        return UBOUND
    return lb
