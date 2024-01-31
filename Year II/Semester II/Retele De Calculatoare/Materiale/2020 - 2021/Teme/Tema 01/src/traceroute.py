import socket
import random
import struct

import requests
import json
import traceback

MAX_SEGMENT = 63535

# socket de UDP
udp_send_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, proto=socket.IPPROTO_UDP)

# socket RAW de citire a raspunsurilor ICMP
icmp_recv_socket = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_ICMP)
# setam timout in cazul in care socketul ICMP la apelul recvfrom nu primeste nimic in buffer
icmp_recv_socket.settimeout(3)


def get_location_info(ip):
    api_token = "d3942PoeQC5qY70alstZ4TvFe97vasXS"

    headers = {
        "Accept": "application/json"
    }
    response = requests.get('https://api.ip2loc.com/' + api_token + '/' + ip, headers=headers)
    response_data = json.loads(response.text)
    location_details = response_data["location"]

    oras = location_details["city"]
    regiune = location_details["country"]["subdivision"]
    tara = location_details["country"]["name"]
    return oras, regiune, tara


def get_random_port():
    return random.randint(33434, 33534)


def traceroute(ip, port, TTL=1):
    '''Functie care are ca scop afisarea locatiilor geografice 
    de pe rutele pachetelor.
    '''

    if TTL > 16:
        return

    udp_send_sock.setsockopt(socket.IPPROTO_IP, socket.IP_TTL, TTL)

    # trimite un mesaj UDP catre un tuplu (IP, port)
    udp_send_sock.sendto(b'hello', (ip, port))

    # asteapta un mesaj ICMP de tipul ICMP TTL exceeded messages
    # aici nu verificam daca tipul de mesaj este ICMP
    # dar ati putea verifica daca primul byte are valoarea Type == 11
    # https://tools.ietf.org/html/rfc792#page-5
    # https://en.wikipedia.org/wiki/Internet_Control_Message_Protocol#Header
    addr = 'done!'
    try:
        data, addr = icmp_recv_socket.recvfrom(MAX_SEGMENT)
    except Exception as e:
        # print("Socket timeout ", str(e))
        return traceroute(ip, get_random_port(), TTL+1)

    adresa_ip = addr[0]

    oras, regiune, tara = get_location_info(adresa_ip)

    if oras is not None or regiune is not None or tara is not None:
        print(adresa_ip, " - ", oras, ", ", regiune, ", ", tara, sep="", end="\n")

    if data[20] != 11 or adresa_ip == ip:
        return

    traceroute(ip, get_random_port(), TTL + 1)


# traceroute("185.57.83.167", get_random_port())
# traceroute("80.249.166.52", get_random_port())
# traceroute("18.200.8.190", get_random_port())
# traceroute("172.217.18.68", get_random_port())
traceroute("172.217.19.100", get_random_port())