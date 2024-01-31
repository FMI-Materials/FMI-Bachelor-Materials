# Tema 2

## Informații temă
**Termen limită**: **14 iunie 2021** 

Punctajul temei este 60% din nota finală de laborator.

Veți fi evaluați individual în funcție de prezentarea temei și commit-uri în repository prin `git blame` și `git-quick-stats -a`. Doar utilizatorii care apar cu modificări în repository vor fi punctați (în funcție de modificările pe care le fac).

Pentru a vă înscrie folosiți acest URL: [https://classroom.github.com/g/JW06XU7c](https://classroom.github.com/g/JW06XU7c)



## Cuprins exerciții

- [Controlul congestiei (25%)](#congestion)
- [Exercițiu la alegere (25%)](#rutare)
  - [Rutare](#rutare)
  - [HTTP service](#http)
- [ARP Spoofing (25%)](#arp_spoof)
- [TCP Hijacking (25%)](#tcp_hij)



<a name="barem"></a> 
## Barem

### 1. Controlul congestiei (25%) 

- completați fișierul Rezolvare.md
- 5p. Plot cwnd - plotarea și explicarea conceptelor de control al congestiei în 1000 de cuvinte 
- 5p. Plot cwnd pentru alte metode de control - plotarea și explicare


### 2. Exercitiu la alegere (25%)

La alegere dintre:

- 10p. completați în Rezolvare.md un mini referat despre protocoale de routare de 1000 de cuvinte prin care să acoperiți cele 5 concepte de rutare (2p fiecare)
- 10p. completați în Rezolvare.md URL-ul de pe amzon pentru un end-point HTTP 


### 3. ARP Spoofing (25%)

- completați fișierul Rezolvare.md
- 10p. execuția și demonstrația atacului (introduceți logs de pe containere, print-screens, etc)
- orice bucată de cod pe care o luați de pe net trebuie însoțită de comments în limba română, altfel nu vor fi punctate


### 4. TCP Hijacking (25%)

- completați fișierul Rezolvare.md
- 10p. execuția și demonstrația atacului de tcp hijacking (introduceți logs de pe containere, print-screens, etc)
- orice bucată de cod pe care o luați de pe net trebuie însoțită de comments în limba română, altfel nu vor fi punctate


<a name="congestion"></a> 
## 1. Controlul congestiei (25%)

Exercițiul se bazează pe [tutorialul prezentat de Fraida Fund](https://witestlab.poly.edu/blog/tcp-congestion-control-basics/) în care sunt extrase informațiile despre cwnd folosind aplicația din linia de comandă ss [socket statistics](https://netbeez.net/blog/how-to-get-ss-socket-statistics-information/): `ss -ein dst IP`. Citiți cu atenție tutorialul înainte de a începe rezolvarea și asigurați-vă că aveți aplicațiile `ss` și `ts` în containerul de docker (rulați `docker-compose build` în directorul [capitolul3](https://github.com/senisioi/computer-networks/tree/2021/capitolul3#intro)).

Setați pe containerul router limitare de bandă cu netem, astfel încât să aveți un bottleneck de 1 Mbp/s și un buffer de 0.1 MB, în ambele direcții de comunicare:
```bash
docker-compose exec router bash -c "/elocal/capitolul3/src/bottleneck.sh"
```

Rulați pe containerul server o aplicație server iperf3
```bash
docker-compose exec server bash -c "iperf3 -s -1"
```

Rulați pe containerul client script-ul de shell care salvează valorile de timestamp și cwnd într-un csv.
```bash
docker-compose exec client bash -c "/elocal/capitolul3/src/capture_stats.sh"
```

Rulați pe containerul client o aplicație client care să comunice cu serverul timp de 60 de secunde și care să folosească TCP Reno:
```bash
docker-compose exec client bash -c "iperf3 -c 198.10.0.2 -t 60 -C reno"
```
După finalizarea transmisiunii, încetați execuția comenzii `capture_stats.sh` prin `Ctrl + C`.

La final veți putea vedea în directorul `capitolul3/congestion` un fișier `socket_stats.csv` care conține timestamp-ul și cwnd la fiecare transmisie. 

### 1.1 Plot cwnd
Scrieți un script care citește fișierul csv și plotează (vezi bibliotecile de python: matplotlib, seaborn sau pandas) cwnd în raport cu timestamp. Identificați fazele Slow Start, Congestion Avoidance, Fast Retransmit și Fast Recovery din graficul obținut și scrieți un comentariu de 400 de cuvinte care descrie procesele anterior menționate și în ce parte a graficului sunt vizibile. 

### 1.2. Plot cwnd pentru alte metode de control
Încercați alte 3 metode de congestion control schimbând parametrul de la iperf3 `-C reno` în altceva. Scrieți un comentariu de aprox. 200 de cuvinte la fiecare grafic obținut prin care să detaliați similaritățile și diferențele în graficele obținute cu diferite metode.



## 2. Exercițiu la alegere (25%)

<a name="rutare"></a> 
### 2.1 Protocoale de routare
Citiți și urmăriți cursurile despre Forwarding si Routing și scrieți o scurtă prezentare de aprox. 1000 de cuvinte în care acoperiți principiile și proprietățile următoarelor protocoale și concepte:

- Forwarding vs. Routing (2p)
- Link State Routing (2p)
- Distance Vector Routing (2p)
- Open Shortest Path First (2p)
- Border Gateway Protocol Routing (2p)



<a name="http"></a> 
### 2.2 HTTP service

Scrieți un end-point HTTP care are ca scop partiționarea unui range de IP-uri în subnets în funcție de numărul de noduri și numărul de subrețele cerute. În [prima parte a acestui tutorial](https://witestlab.poly.edu/blog/designing-subnets/) puteți vedea un exemplu de împărțire manuală.

Pentru acest exercițiu va trebui să folosiți AWS. Dacă rămâneți fără credits sau dacă nu ați primit mail cu invite AWSEducate, vă rog să îmi scrieți pe mail. Predarea soluției se va face ca aplicație server pe AWS și sursele în repository de githubȘ

1) urmăriți [aici un tutorial](https://m.youtube.com/watch?v=MpBKali87YI) silent despre cum să vă configurati un server pe AWS si sa deschideti porturi
2) adăugați sursele modificate sau folosite în directorul `http_api`
2) modificați template-ul Rezolvare.md și completați raportul cu cerințele de acolo.


Puteți folosi template-ul [simple_flask.py](https://github.com/retele/tema2/blob/master/http_api/simple_flask.py) pentru a crea un serviciu HTTP cu o metoda [POST](https://www.w3schools.com/tags/ref_httpmethods.asp). Sau folosiți librăria [fastapi](https://github.com/tiangolo/fastapi) care are integrat și swagger.

Input:
```json
{
	"subnet": "10.189.24.0/24",
	"dim": [10, 10, 100],        
}

// subnet - range-ul de IP-uri initial  
// dim - o lista cu numarul de noduri care trebuie acoperit de fiecare subretea
```

Iar aplicația returnează o împărțire în subrețele în funcție de numărul de elemente de din listă:
```json
{
	"LAN1": "10.189.24.128/28",
	"LAN2": "10.189.24.144/28",
	"LAN3": "10.189.24.0/25"
}
```
În cazul în care împărțirea nu se poate face, returnați o eroare.


#### Indicații de rezolvare

##### Cum transformăm adrese în octeți și invers
Adresele IP pot fi transformate în șiruri de octeți (numere) folosind inet_aton sau inet_ntoa:
```python
import socket

IP = '198.10.0.3'
octeti = socket.inet_aton(IP)
print(octeti)
#b'\xc6\n\x00\x03'

for octet in octeti:
    print(octet)
'''
198
10
0
3
'''

ip_string = socket.inet_ntoa(octeti)
print(ip_string)
#'198.10.0.3'

```

##### Cum testăm aplicația
Testați aplicația folosind requests, header-ul trebuie să fie: `{'Content-Type': 'application/json'}` iar datele trebuie transformate cu `json.dumps()`.
```python
header = {'Content-Type': 'application/json'}
data = {'subnet': '10.189.24.0/24', 'dim': [10, 10, 100]}
url = 'http://ec2-21-12-21-12.compute-1.amazonaws.com' # link-ul catre serverul AWS
response = requests.post(url, headers=header, data=json.dumps(data))
print (response.content)
```

##### Cum executăm scriptul pe serverul AWS
Puteți rula scriptul direct pe server folosind tmux, dar mai întâi trebuie să instalați pip și librăria flask pe server:
```bash
sudo apt-get update
sudo apt install python3-pip
pip3 install flask --user
tmux
python3 http_api/simple_flask.py
# Apas Ctrl+b si apoi d pentru a ma detasa de sesiune
```

Vezi [aici tmux cheatsheet](https://tmuxcheatsheet.com/) sau câteva exemple mai jos: 
```bash
tmux ls - listez toate sesiunile
tmux - creez o noua sesiune cu indicele 0,1,2...
tmux attach -t 0 - ma atasez la sesiunea 0
Ctrl + b apoi apas d - face detach de sesiune
Ctrl + b apoi apas s - face switch de sesiune
Ctrl + b apoi apas [ - pentru scroll up
copy to clipboard - tin apasat Shift, selectez, click dreapta copy
```

##### Cum executăm scriptul din docker pe serverul AWS
Clonăm repository cu tema. Modificăm docker-compose.yml pentru containerul `http_api` ca portul de pe host să fie 80 și de-commentăm partea cu `#command`.


<a name="arp_spoof"></a> 
## 3. ARP Spoofing (25%)
[ARP spoofing](https://samsclass.info/124/proj11/P13xN-arpspoof.html) presupune trimiterea unui pachet ARP de tip reply către o țintă pentru a o informa greșit cu privire la adresa MAC pereche pentru un IP. [Aici](https://medium.com/@ismailakkila/black-hat-python-arp-cache-poisoning-with-scapy-7cb1d8b9d242) și [aici](https://www.youtube.com/watch?v=hI9J_tnNDCc) puteți urmări cum se execută un atac de otrăvire a tabelei cache ARP stocată pe diferite mașini.

Arhitectura containerelor este definită în [capitolul3](https://github.com/senisioi/computer-networks/tree/2021/capitolul3#intro), împreună cu schema prin care `middle` îi informează pe `server` și pe `router` cu privire la locația fizică (adresa MAC) unde se găsesc IP-urile celorlalți. 

Rulati procesul de otrăvire a tabelei ARP din diagrama de mai sus pentru containerele `server` și `router` în mod constant, cu un time.sleep de câteva secunde pentru a nu face flood de pachete. (Hint: puteți folosi două [thread-uri](https://realpython.com/intro-to-python-threading/#starting-a-thread) pentru otrăvirea routerului și a serverului).


Pe lângă print-urile și mesajele de logging din programele voastre, rulați în containerul middle: `tcpdump -SntvXX -i any` iar pe `server` faceți un `wget http://old.fmi.unibuc.ro`. Dacă middle este capabil să vadă conținutul HTML din request-ul server-ului, înseamnă că atacul a reușit. Altfel încercați să faceți clean la cache-ul ARP al serverului.


### Observații
1. E posibil ca tabelel ARP cache ale containerelor `router` și `server` să se updateze mai greu. Ca să nu dureze câteva ore până verificați că funcționează, puteți să le curățați în timp ce, sau înainte de a declanșa atacul folosind [comenzi de aici](https://linux-audit.com/how-to-clear-the-arp-cache-on-linux/)
1. Atacurile implementante aici au un scop didactic, nu încercați să folosiți aceste metode pentru a ataca alte persoane de pe o rețea locală.


<a name="tcp_hij"></a> 
## 4. TCP Hijacking (25%)

Modificați `tcp_server.py` și `tcp_client.py` din repository și rulați-le pe containerul `server`, respectiv `client` ca să-și trimită în continuu unul altuia mesaje random (generați text sau numere, ce vreți voi). Puteți folosi time.sleep de o secundă/două să nu facă flood. Folosiți soluția de la exercițiul anterior pentru a vă interpune în conversația dintre `client` și `server`.
După ce ați reușit atacul cu ARP spoofing și interceptați toate mesajele, modificați conținutul mesajelor trimise de către client și de către server și inserați voi un mesaj adițional în payload-ul de TCP. Dacă atacul a funcționat atât clientul cât și serverul afișează mesajul pe care l-ați inserat. Atacul acesta se numeșete [TCP hijacking](https://www.geeksforgeeks.org/session-hijacking/) pentru că atacatorul devine un [proxy](https://en.wikipedia.org/wiki/Proxy_server) pentru conexiunea TCP dintre client și server.


### Indicații de rezolvare

1. Încercați întâi să captați și să modificați mesajele de pe containerul router pentru a testa captura pacheteleor și TCP hijacking apoi puteți combina exercițiul 1 cu metoda de hijacking.
1. Puteți urmări exemplul din capitolul 3 despre [Netfilter Queue](https://github.com/senisioi/computer-networks/blob/2020/capitolul3/README.md#scapy_nfqueue) pentru a pune mesajele care circulă pe rețeaua voastră într-o coadă ca să le procesați cu scapy.
1. Urmăriți exemplul [DNS Spoofing](https://github.com/senisioi/computer-networks/blob/2020/capitolul3/README.md#scapy_dns_spoofing) pentru a vedea cum puteți altera mesajele care urmează a fi redirecționate într-o coadă și pentru a le modifica payload-ul înainte de a le trimite (adică să modificați payload-ul înainte de a apela `packet.accept()`).
1. Verificați dacă pachetele trimise/primite au flag-ul PUSH setat. Are sens să alterați SYN sau FIN?
1. Țineți cont de lungimea mesajului pe care îl introduceți pentru ajusta Sequence Number (trebuie ajustat și Acknowledgement Number?).
1. Scrieți pe teams orice întrebări aveți, indiferent de cât de simple sau complicate vi se par.
