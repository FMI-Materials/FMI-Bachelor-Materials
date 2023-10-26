""" 15. Ping 
Într-un fisier text se aflã mesajul returnat de o comandã de tip ping. 
Realizati urmãtoarele functii:
a) determina_ip(nume fisier) - primeste ca parametru numele unui fisier text 
de tipul indicat mai sus si returneazã adresa IP si DNS (numele domeniului) 
cãtre care s-a dat comanda ping;

b) nr_pachete(nume_fisier) - primeste ca parametru numele unui fisier text 
de tipul indicat si returneazã numãrul de pachete trimise, respectiv numãrul 
de linii de forma 
64 bytes from 216.58.214.238: icmp_seq=0 ttl=56 time=16.453 ms

c) verificare_timp(nume_fisier) - primeste ca parametru numele unui fisier 
text si returneazã mesaje de eroare daca timpii prezenti pe ultima linie nu 
sunt egali cu timpii din fisier.

Folosind apeluri utile ale functiilor de mai sus, realizati un algoritm ce 
scrie în fisierul “ping.out” numãrul de pachete trimise, timpul minim, maxim, 
mediu, IP ?i DNS.
Rezolvati problema folosind expresii regulate (modulul re).

Exemplu:
ping.in
192-168-0-2:~ mihaela-dianabaldovin$ ping google.com -c 5
PING google.com (216.58.214.238): 56 data bytes
64 bytes from 216.58.214.238: icmp_seq=0 ttl=56 time=16.453 ms
64 bytes from 216.58.214.238: icmp_seq=1 ttl=56 time=16.136 ms
64 bytes from 216.58.214.238: icmp_seq=2 ttl=56 time=15.838 ms
64 bytes from 216.58.214.238: icmp_seq=3 ttl=56 time=16.669 ms
64 bytes from 216.58.214.238: icmp_seq=4 ttl=56 time=15.775 ms
--- google.com ping statistics ---
5 packets transmitted, 5 packets received, 0.0% packet loss
round-trip min/avg/max/stddev = 15.775/16.174/16.669/0.345 ms

ping.out
Timp minim: 15.775 ms
Timp maxim: 16.669 ms
Timp mediu: 16.174 ms
IP: 216.58.214.238
DNS: google.com
"""

import re

def determina_ip(nume_fisier):
    data = open(nume_fisier).read()
    dns = re.findall('(([a-z]{0,61}[a-z]\.)+[a-z]{0,61})', data)[0][0]
    ip = re.findall('([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3})',data)[0]
    return dns, ip

def nr_pachete(nume_fisier):
    data = open(nume_fisier).read()
    pachete = re.findall('icmp_seq', data)
    return (len(pachete))

def verificare_timp(nume_fisier):
    data = open(nume_fisier).read()
    timp = re.findall('time=(\d{1,}.\d{3}) ms', data)
    timp = [float(elem) for elem in timp]
    timp = sorted(timp)
    timp_min = timp[0]
    timp_max = timp[-1]
    timp_mediu = sum(timp)/len(timp)
    timp_mediu = float("{0:.3f}".format(timp_mediu))
    timp_ultima_line = re.findall('(\d{1,}.\d{3})/', data)
    timp_ultima_line = [float(elem) for elem in timp_ultima_line]
    timp_min_ul = timp_ultima_line[0]
    timp_mediu_ul = timp_ultima_line[1]
    timp_max_ul = timp_ultima_line[2]
    assert timp_min == timp_min_ul, "Timpul minim este diferit"
    assert timp_max == timp_max_ul, "Timpul maxim este diferit"
    return timp_min_ul, timp_max_ul, timp_mediu_ul, timp_min, timp_max, timp_mediu

file = 'L4_pb15_ping.in'
dns_addr, ip_addr = determina_ip(file)
nr_pach = nr_pachete(file)
mini, maxi, medi, mini_calc, maxi_calc, medi_calc = verificare_timp(file)
g = open('L4_pb15_ping.out', 'w')
g.write('Timp minim '+str(mini)+' calculat '+str(mini_calc)+'\n')
g.write('Timp maxim '+str(maxi)+' calculat '+str(maxi_calc)+'\n')
g.write('Timp mediu '+str(medi)+' calculat '+str(medi_calc)+'\n')
g.write('IP: '+str(ip_addr)+'\n')
g.write('DNS: '+dns_addr+'\n')
g.write('Numar pachete trimise: '+str(nr_pach))
g.close()