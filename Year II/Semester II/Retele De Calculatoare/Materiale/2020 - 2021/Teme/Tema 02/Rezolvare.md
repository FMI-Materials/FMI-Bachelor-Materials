# Tema 2

- [Controlul congestiei (25%)](#congestion)
- [HTTP API (25%)](#http)
- [ARP Spoofing (25%)](#arp_spoof)
- [TCP Hijacking (25%)](#tcp_hij)


<a name="congestion"></a> 
## 1. Controlul congestiei (25%)

### 1.1 Diagrama pentru RENO este:

![alt text](https://github.com/retele/tema-2-python3-tema-la-retele-py/blob/master/images/reno.png)

- Slow Start
În etapa de Slow Start, de fiecare dată când un ACK este primit, CWND-ul este crescut cu numărul de segmente confirmate. 
Astfel, creșterea CWND-ului este una exponențială, nu liniară ca în cazul AIMD (additive increase multiplicative decrease).
Slow Start este specific pentru parte numită "congestion control". Această etapă continuă până când CWND-ul ajunge la ceva numit
"slow start treshold". Din acel punct începe etapa de "congestion avoidance", în care se trece la metoda AIMD,
care asigură o creștere liniară. 

În momentul în care un pachet este pierdut, valoarea treshold-ului devine o fracție din CWND-ul curent.

Partea de Slow Start poate fi observată pe grafic între început șî până la punctul marcat cu 2.

- Congestion Avoidance
În această etapă se încearcă adaptarea vitezei de transmitere a pachetelor astfel încât să se evite congestia. Pentru aceasta se folosește o fereastră 
CWND (de obicei un multiplu de MSS), care limiteaza numărul de pachete neconfirmate care pot exista la un moment dat.

Practic problema se reduce la adaptarea ferestrei. Pentru aceasta se poate folosi algotimul AIMD (additive increase multiplicative decrease).
Acesta funcționează în felul următor:
	- la fiecare RTT la care nu se pierde un pachet, CWND-ul este crescut cu o constantâ aditivă
	- la fiecare RTT la care un pachet este pierdut, CWND-ul este micșorat în raport cu o constantă multiplicativă
	
Această etapâ poate fi observată în grafic începând de la punctul marcat cu 2 până la final

- Fast Retransmit/Fast Recovery
Fast Retransmit sau Fast Recovery reprezintă un moment în care se deduce că unele pachete au fost pierdute înainte de a primi timeout.
Acest lucru se realizează în momentul în care se primesc ACK-uri duplicate. În algoritmul TCP Reno, măsurile corespunzătoare unei pierderi de pachete
se iau la 3 ACK-uri duplicate.

Se poate face o ierarhizare a gravității pierderilor pachetelor după modul în care ne dăm seama că s-au pierdut. Astfel:
	- în momentul în care primim un timeout considerăm că congestia este mai gravă, deoarece toate pachetele de după cel dropped sunt congestionate.
	  În acest caz în TCP Reno, CWND-ul este redus la minim și se continuă cu un Slow Start (un astfel de moment pe grafic este punctul 1 marcat cu roșu)
	- în momentul în care primim duplicare, congestia este consideratâ mai puțin gravă. În acest caz CWND-ul este redus la Slow Start Treshold și se continuă
	cu congestion avoidance. Aceste momente de timp se numesc "Fast Retransmit" sau "Fast Recovery", iar pe grafic, ele sunt reprezentate cu verde (punctele
	4, 6 și 8)

### 1.2 Diagrame pentru CUBIC, HYBLA si VEGAS

- CUBIC
![alt text](https://github.com/retele/tema-2-python3-tema-la-retele-py/blob/master/images/cubic.png)

Acest algoritm este e versiune mai puțin agresivă a algoritmului BIC (binary increase congestion). În cardul acestui algoritm, CWND-ul este o funcție de gradul 3 care depinde de ultimul moment de timp la care s-a detectat o congestie. Algoritmul este folosit ca algoritm implicit pentru controlul congestiei în Kernel-ul de linux (între versiunile 2.6.19 și 3.2).

Spre deosebire de RENO, putem observa că aici etapa de "Slow Start" se termină relativ devreme și fără ca vreun pachet să ia timeout. Urmează în continuare partea de "Congestion Avoidance". Aici se pot remarca mult mai multe puncte de "Fast Recovery" (cele marcate cu vedre). În general CWND-ul fluctuează între 50 șî 80, spre deosebire de graficul anterior, unde acesta atingea valori puțin mai mici. Se remarcă de asemena o frecvență mai mare în apariția punctelor de "Fast Recovery" și a celor în care sunt primite ACK-uri duplicate față de algoritmii RENO sau HYBLA, de unde putem deduce că acest algoritm se apropie mai mult de limita superioară a capacității rețelei. Totuși se poate observa că CWND-ul nu este capabil să conveargă spre o valoare anume. Deși acest lucru poate fi interpretat ca un neajuns al algoritmului, trebuie să luăm în calcul că parametrii rețelei sunt în continuă schimbare, astfel valoarea maxim admisibilă a CWND-ului este dinamică.

- HYBLA
![alt text](https://github.com/retele/tema-2-python3-tema-la-retele-py/blob/master/images/hybla.png)

Algoritmul HYBLA își propune să elimine penalizările creeate de conexiunile TCP care provoacă un latency ridicat. Avantajele pe care le aduce acest algoritm sunt bazate pe evaluarea analitică a dinamicii CWND-ului.

Putem observa că graficul este oarecum asemănător cu cel de la algoritmul RENO, partea de "Slow Start" fiind similară ca durată, în ambele cazuri având loc o detectare de congestie prin timeout-ul unui pachet. O particularitate este faptul că se prezintă un singur punct de "Fast Recovery" (punctul 4, marcat cu verde). Partea de AIMD este bine ilustrată, fiind evidente două porțiuni ale graficului în care CWND-ul crește aproximativ liniar. În general CWND-ul fluctuează între 30 (în punctul minim de "Fast Recovery") și 75 (în punctul 3, în care se primesc ACK-uri duplicate). Spre deosebire de CUBIC, aici putem spune că CWND-ul tinde să conveargă către o valoare în jur de 70, înainte să fie detectată o congestie. O diferență vizibilă între cei doi algoritmi este viteza cu care CWND-ul se modifică, CUBIC prefetând să determine o congestie, după care să ajusteze CWND-ul, iar HYBLA preferând să evite congestiile cu costul unei creșteri mai lente a CWND-ului. Acestea fiind spuse, putem remarca cum algoritmul RENO se situează undeva între cele două extreme din acest punct de vedere.

- VEGAS
![alt text](https://github.com/retele/tema-2-python3-tema-la-retele-py/blob/master/images/vegas.png)

Algoritmul VEGAS a fost introdus la sfârșitul anilor '90, la universitare din Arizona. Difierența dintre acest algoritm și predecesorii săi este că VEGAS setează timeout-ul și măroară round trip time-ul luând în considerare fiecare pachet din buffer-ul de transmitere, spre deosebire de algoritmii mai vechi care făceau acest lucru doar în funcție de ultimul pachet din buffer. Acesta este considerat ca fiind cel mai "neted" algoritm de "Congestion Control", urmat de CUBIC. Cu toate acestea, algoritmul nu s-a bucurat de o mare popularitate, el nefiind foarte folosit în afara laboratorului universității.

Pe grafic putem remarca cum partea de slow start se termină mai târziu decât la ceilalți algoritmi (axa orizontală cuprinde aici un spectru mult mai larg) în momentul detectârii unui timeout. Urmază un punct de "Fast Recovery", după care o lunga perioadă în care CWND-ul fluctuează între valorile 5 și 7. În acest interval punctele de "Fast Recovery" apar periodic și regulat, cu o frecvență ridicată. Se remarcă stabilitatea algorimului și capacitatea acestuia de a nu provoca congestii repetate pe rețea. Graficul prezent este fundamental diferit de toate cele anterioare (RENO, CUBIC și HYBLA), similaritățile fiind aproape inexistente, niciunul dintre grafice prezentând o regularitate la fel de evidentă ca cel în cauză.


<a name="http"></a> 
## 2. HTTP API (25%)

Aplicația poate fi accesata la adresa:

[http://ec2-3-80-109-111.compute-1.amazonaws.com](http://ec2-3-80-109-111.compute-1.amazonaws.com)

<a name="arp_spoof"></a> 
## 3. ARP Spoofing (25%)

Scrieție mesajele primite de server, client și printați acțiunile pe care le face middle.
```
[*] Starting script: arp_poison.py
[*] Enabling IP forwarding
[*] Gateway IP address: 198.10.0.2
[*] Target IP address: 198.10.0.1
[*] Gateway MAC address: 02:42:c6:0a:00:02
[*] Target MAC address: 02:42:c6:0a:00:01
[*] Started ARP poison attack [CTRL-C to stop]
[*] Starting network capture. Packet Count: 1000. Filter: ip host 198.10.0.1
```

Rulați pe `middle` comanda `tcpdump -SntvXX -i any` și salvați log-urile aici. Încercați să salvați doar cateva care conțin HTML-ul de la request-ul din server.
```
IP (tos 0x0, ttl 63, id 44087, offset 0, flags [DF], proto TCP (6), length 40)
    198.10.0.3.57304 > 193.226.51.15.80: Flags [.], cksum 0xbb19 (incorrect -> 0x46e6), ack 452897411, win 492, length 0
	0x0000:  0004 0001 0006 0242 c60a 0003 0000 0800  .......B........
	0x0010:  4500 0028 ac37 4000 3f06 d499 c60a 0003  E..(.7@.?.......
	0x0020:  c1e2 330f dfd8 0050 1161 f4f7 1afe aa83  ..3....P.a......
	0x0030:  5010 01ec bb19 0000                      P.......
IP (tos 0x0, ttl 37, id 44669, offset 0, flags [none], proto TCP (6), length 1316)
    193.226.51.15.80 > 198.10.0.3.57304: Flags [P.], cksum 0x006b (correct), seq 452897411:452898687, ack 291632375, win 65535, length 1276: HTTP
	0x0000:  0000 0001 0006 0242 6f67 db57 0000 0800  .......Bog.W....
	0x0010:  4500 0524 ae7d 0000 2506 2758 c1e2 330f  E..$.}..%.'X..3.
	0x0020:  c60a 0003 0050 dfd8 1afe aa83 1161 f4f7  .....P.......a..
	0x0030:  5018 ffff 006b 0000 706f 6d65 6c6e 6963  P....k..pomelnic
	0x0040:  2069 6d67 7b0a 0909 0909 626f 7264 6572  .img{.....border
	0x0050:  3a20 3070 783b 7d0a 0909 0923 666f 6f74  :.0px;}....#foot
	0x0060:  6572 207b 0a09 0909 0966 6f6e 742d 6661  er.{.....font-fa
	0x0070:  6d69 6c79 3a20 5665 7264 616e 612c 2041  mily:.Verdana,.A
	0x0080:  7269 616c 2c20 4865 6c76 6574 6963 612c  rial,.Helvetica,
	0x0090:  2073 616e 732d 7365 7269 663b 0a09 0909  .sans-serif;....
	0x00a0:  0966 6f6e 742d 7369 7a65 3a20 302e 3765  .font-size:.0.7e
	0x00b0:  6d3b 7d0a 0909 0923 666f 6f74 6572 2070  m;}....#footer.p
	0x00c0:  0a09 0909 7b09 7061 6464 696e 672d 746f  ....{.padding-to
	0x00d0:  703a 2030 7078 3b0a 0909 0909 7061 6464  p:.0px;.....padd
	0x00e0:  696e 672d 626f 7474 6f6d 3a20 3070 783b  ing-bottom:.0px;
	0x00f0:  0a09 0909 096d 6172 6769 6e2d 746f 703a  .....margin-top:
	0x0100:  2030 7078 3b0a 0909 0909 6d61 7267 696e  .0px;.....margin
	0x0110:  2d62 6f74 746f 6d3a 2032 7078 3b7d 0a09  -bottom:.2px;}..
	0x0120:  093c 2f73 7479 6c65 3e0a 093c 7363 7269  .</style>..<scri
	0x0130:  7074 2074 7970 653d 2274 6578 742f 6a61  pt.type="text/ja
	0x0140:  7661 7363 7269 7074 2220 7372 633d 2268  vascript".src="h
	0x0150:  7474 703a 2f2f 6f6c 642e 666d 692e 756e  ttp://old.fmi.un
	0x0160:  6962 7563 2e72 6f2f 6761 2e6a 7322 3e3c  ibuc.ro/ga.js"><
	0x0170:  2f73 6372 6970 743e 0a09 3c2f 6865 6164  /script>..</head
	0x0180:  3e0a 0a09 3c62 6f64 7920 6f6e 6c6f 6164  >...<body.onload
	0x0190:  3d22 7261 6e64 6f6d 496d 6167 6528 293b  ="randomImage();
	0x01a0:  223e 0a09 3c64 6976 2069 643d 2263 6f6e  ">..<div.id="con
	0x01b0:  7465 6e74 223e 0a09 093c 6469 7620 6964  tent">...<div.id
	0x01c0:  3d22 7465 7874 6622 3e0a 0909 093c 703e  ="textf">....<p>
	0x01d0:  4661 6375 6c74 6174 6561 2064 6520 4d61  Facultatea.de.Ma
	0x01e0:  7465 6d61 7469 6361 2073 6920 496e 666f  tematica.si.Info
	0x01f0:  726d 6174 6963 612c 2055 6e69 7665 7273  rmatica,.Univers
	0x0200:  6974 6174 6561 2042 7563 7572 6573 7469  itatea.Bucuresti
	0x0210:  3c2f 703e 0a09 0909 3c70 3e46 6163 756c  </p>....<p>Facul
	0x0220:  7479 206f 6620 4d61 7468 656d 6174 6963  ty.of.Mathematic
	0x0230:  7320 616e 6420 436f 6d70 7574 6572 2053  s.and.Computer.S
	0x0240:  6369 656e 6365 2c20 556e 6976 6572 7369  cience,.Universi
	0x0250:  7479 206f 6620 4275 6368 6172 6573 743c  ty.of.Bucharest<
	0x0260:  2f70 3e0a 0909 3c2f 6469 763e 0a09 093c  /p>...</div>...<
	0x0270:  6469 7620 6964 3d22 6368 6f6f 7365 223e  div.id="choose">
	0x0280:  0a09 0909 3c75 6c3e 0a09 0909 093c 6c69  ....<ul>.....<li
	0x0290:  3e3c 6120 6964 3d22 726f 6d61 6e61 2220  ><a.id="romana".
	0x02a0:  6872 6566 3d22 726f 2f22 3e52 6f6d 616e  href="ro/">Roman
	0x02b0:  613c 2f61 3e3c 2f6c 693e 0a09 0909 093c  a</a></li>.....<
	0x02c0:  6c69 3e3c 6120 6964 3d22 656e 676c 657a  li><a.id="englez
	0x02d0:  6122 2068 7265 663d 2265 6e2f 223e 456e  a".href="en/">En
	0x02e0:  676c 6973 683c 2f61 3e3c 2f6c 693e 0a09  glish</a></li>..
	0x02f0:  0909 3c2f 756c 3e0a 0909 3c2f 6469 763e  ..</ul>...</div>
	0x0300:  0a09 093c 6469 7620 6964 3d22 706f 7a61  ...<div.id="poza
	0x0310:  223e 0a09 093c 2f64 6976 3e0a 0909 3c64  ">...</div>...<d
	0x0320:  6976 2069 643d 2261 6472 6573 6122 3e0a  iv.id="adresa">.
	0x0330:  0909 093c 703e 3c73 7472 6f6e 673e 4661  ...<p><strong>Fa
	0x0340:  6375 6c74 6174 6561 2064 6520 4d61 7465  cultatea.de.Mate
	0x0350:  6d61 7469 6361 2073 6920 496e 666f 726d  matica.si.Inform
	0x0360:  6174 6963 6120 2d20 556e 6976 6572 7369  atica.-.Universi
	0x0370:  7461 7465 6120 6469 6e20 4275 6375 7265  tatea.din.Bucure
	0x0380:  7374 693c 2f73 7472 6f6e 673e 3c2f 703e  sti</strong></p>
	0x0390:  0a09 0909 3c70 3e3c 7374 726f 6e67 3e41  ....<p><strong>A
	0x03a0:  6472 6573 613a 3c2f 7374 726f 6e67 3e20  dresa:</strong>.
	0x03b0:  5374 722e 2041 6361 6465 6d69 6569 206e  Str..Academiei.n
	0x03c0:  722e 3134 2c20 7365 6374 6f72 2031 2c20  r.14,.sector.1,.
	0x03d0:  432e 502e 2030 3130 3031 342c 2042 7563  C.P..010014,.Buc
	0x03e0:  7572 6573 7469 2c20 526f 6d61 6e69 613c  uresti,.Romania<
	0x03f0:  2f70 3e0a 0909 093c 703e 3c73 7472 6f6e  /p>....<p><stron
	0x0400:  673e 5465 6c3a 3c2f 7374 726f 6e67 3e20  g>Tel:</strong>.
	0x0410:  2834 2d30 3231 2920 3331 3420 3335 3038  (4-021).314.3508
	0x0420:  2c20 3c73 7472 6f6e 673e 4661 783a 3c2f  ,.<strong>Fax:</
	0x0430:  7374 726f 6e67 3e20 2834 2d30 3231 2920  strong>.(4-021).
	0x0440:  3331 3520 3639 3930 2c20 3c73 7472 6f6e  315.6990,.<stron
	0x0450:  673e 452d 6d61 696c 3a3c 2f73 7472 6f6e  g>E-mail:</stron
	0x0460:  673e 2073 6563 7265 7461 7269 6174 266e  g>.secretariat&n
	0x0470:  6273 703b 4026 6e62 7370 3b66 6d69 2e75  bsp;@&nbsp;fmi.u
	0x0480:  6e69 6275 632e 726f 3c2f 703e 0a09 093c  nibuc.ro</p>...<
	0x0490:  2f64 6976 3e0a 0909 3c64 6976 2069 643d  /div>...<div.id=
	0x04a0:  2270 6f6d 656c 6e69 6322 3e0a 0909 093c  "pomelnic">....<
	0x04b0:  703e 266e 6273 703b 3c2f 703e 0a3c 212d  p>&nbsp;</p>.<!-
	0x04c0:  2d0a 0909 092f 5374 6172 7420 5472 6166  -..../Start.Traf
	0x04d0:  6963 2e72 6f2f 0a09 0909 093c 7363 7269  ic.ro/.....<scri
	0x04e0:  7074 2074 7970 653d 2274 6578 742f 6a61  pt.type="text/ja
	0x04f0:  7661 7363 7269 7074 223e 745f 7269 643d  vascript">t_rid=
	0x0500:  2266 6d69 756e 6962 7563 223b 3c2f 7363  "fmiunibuc";</sc
	0x0510:  7269 7074 3e0a 0909 0909 3c73 6372 6970  ript>.....<scrip
	0x0520:  7420 7479 7065 3d22 7465 7874 2f6a 6176  t.type="text/jav
	0x0530:  6173 6372                                ascr
```
Puteți pune și capturi de ecran din wireshark prin orice alte metode de prezentare.

<a name="tcp_hij"></a> 
## 4. TCP Hijacking (25%)
Scrieție mesajele primite de server, client și printați acțiunile pe care le face middle.

![alt text](https://github.com/retele/tema-2-python3-tema-la-retele-py/blob/master/images/hijack.png)

Rulați pe `middle` comanda `tcpdump -SntvXX -i any` și salvați log-urile aici. Încercați să salvați doar cateva care conțin HTML-ul de la request-ul din server.
```
IP (tos 0x0, ttl 63, id 54031, offset 0, flags [DF], proto TCP (6), length 66)
    198.10.0.1.43524 > 198.10.0.2.10000: Flags [P.], cksum 0x8c4c (incorrect -> 0x7f09), seq 31080211:31080237, ack 280043010, win 64240, length 26
	0x0000:  0000 0001 0006 0242 c60a 0001 0000 0800  .......B........
	0x0010:  4500 0042 d30f 4000 3f06 dc8e c60a 0001  E..B..@.?.......
	0x0020:  c60a 0002 aa04 2710 01da 3f13 10b1 1e02  ......'...?.....
	0x0030:  5018 faf0 8c4c 0000 4120 666f 7374 206f  P....L..A.fost.o
	0x0040:  6461 7461 2063 6120 696e 2070 6f76 6573  data.ca.in.poves
	0x0050:  7469                                     ti
IP (tos 0x0, ttl 64, id 1, offset 0, flags [none], proto TCP (6), length 73)
    198.10.0.1.43524 > 198.10.0.2.10000: Flags [P.], cksum 0xa644 (correct), seq 31080211:31080244, ack 280043010, win 8192, length 33
	0x0000:  0004 0001 0006 0242 c60a 0003 0000 0800  .......B........
	0x0010:  4500 0049 0001 0000 4006 ee96 c60a 0001  E..I....@.......
	0x0020:  c60a 0002 aa04 2710 01da 3f13 10b1 1e02  ......'...?.....
	0x0030:  5018 2000 a644 0000 4861 636b 6564 2041  P....D..Hacked.A
	0x0040:  2066 6f73 7420 6f64 6174 6120 6361 2069  .fost.odata.ca.i
	0x0050:  6e20 706f 7665 7374 69                   n.povesti
IP (tos 0x0, ttl 64, id 33970, offset 0, flags [DF], proto TCP (6), length 40)
    198.10.0.2.10000 > 198.10.0.1.43524: Flags [.], cksum 0x8c32 (incorrect -> 0xe816), ack 31080244, win 64207, length 0
	0x0000:  0000 0001 0006 0242 c60a 0002 0000 0800  .......B........
	0x0010:  4500 0028 84b2 4000 4006 2a06 c60a 0002  E..(..@.@.*.....
	0x0020:  c60a 0001 2710 aa04 10b1 1e02 01da 3f34  ....'.........?4
	0x0030:  5010 facf 8c32 0000                      P....2..
IP (tos 0x0, ttl 64, id 33971, offset 0, flags [DF], proto TCP (6), length 98)
    198.10.0.2.10000 > 198.10.0.1.43524: Flags [P.], cksum 0x8c6c (incorrect -> 0xb62e), seq 280043010:280043068, ack 31080244, win 64207, length 58
	0x0000:  0000 0001 0006 0242 c60a 0002 0000 0800  .......B........
	0x0010:  4500 0062 84b3 4000 4006 29cb c60a 0002  E..b..@.@.).....
	0x0020:  c60a 0001 2710 aa04 10b1 1e02 01da 3f34  ....'.........?4
	0x0030:  5018 facf 8c6c 0000 5365 7276 6572 2061  P....l..Server.a
	0x0040:  2070 7269 6d69 7420 6d65 7361 6a75 6c3a  .primit.mesajul:
	0x0050:  2048 6163 6b65 6420 4120 666f 7374 206f  .Hacked.A.fost.o
	0x0060:  6461 7461 2063 6120 696e 2070 6f76 6573  data.ca.in.poves
	0x0070:  7469                                     ti
IP (tos 0x0, ttl 64, id 1, offset 0, flags [none], proto TCP (6), length 40)
    198.10.0.2.10000 > 198.10.0.1.43524: Flags [.], cksum 0xc2ed (correct), ack 31080237, win 8192, length 0
	0x0000:  0004 0001 0006 0242 c60a 0003 0000 0800  .......B........
	0x0010:  4500 0028 0001 0000 4006 eeb7 c60a 0002  E..(....@.......
	0x0020:  c60a 0001 2710 aa04 10b1 1e02 01da 3f2d  ....'.........?-
	0x0030:  5010 2000 c2ed 0000                      P.......
IP (tos 0x0, ttl 64, id 1, offset 0, flags [none], proto TCP (6), length 105)
    198.10.0.2.10000 > 198.10.0.1.43524: Flags [P.], cksum 0xeb41 (correct), seq 280043010:280043075, ack 31080237, win 8192, length 65
	0x0000:  0004 0001 0006 0242 c60a 0003 0000 0800  .......B........
	0x0010:  4500 0069 0001 0000 4006 ee76 c60a 0002  E..i....@..v....
	0x0020:  c60a 0001 2710 aa04 10b1 1e02 01da 3f2d  ....'.........?-
	0x0030:  5018 2000 eb41 0000 4861 636b 6564 2053  P....A..Hacked.S
	0x0040:  6572 7665 7220 6120 7072 696d 6974 206d  erver.a.primit.m
	0x0050:  6573 616a 756c 3a20 4861 636b 6564 2041  esajul:.Hacked.A
	0x0060:  2066 6f73 7420 6f64 6174 6120 6361 2069  .fost.odata.ca.i
	0x0070:  6e20 706f 7665 7374 69                   n.povesti
IP (tos 0x0, ttl 63, id 54032, offset 0, flags [DF], proto TCP (6), length 40)
    198.10.0.1.43524 > 198.10.0.2.10000: Flags [.], cksum 0x8c32 (incorrect -> 0xe7fc), ack 280043075, win 64175, length 0
	0x0000:  0000 0001 0006 0242 c60a 0001 0000 0800  .......B........
	0x0010:  4500 0028 d310 4000 3f06 dca7 c60a 0001  E..(..@.?.......
	0x0020:  c60a 0002 aa04 2710 01da 3f2d 10b1 1e43  ......'...?-...C
	0x0030:  5010 faaf 8c32 0000                      P....2..
IP (tos 0x0, ttl 64, id 1, offset 0, flags [none], proto TCP (6), length 40)
    198.10.0.1.43524 > 198.10.0.2.10000: Flags [.], cksum 0xc2ac (correct), ack 280043068, win 8192, length 0
	0x0000:  0004 0001 0006 0242 c60a 0003 0000 0800  .......B........
	0x0010:  4500 0028 0001 0000 4006 eeb7 c60a 0001  E..(....@.......
	0x0020:  c60a 0002 aa04 2710 01da 3f34 10b1 1e3c  ......'...?4...<
	0x0030:  5010 2000 c2ac 0000                      P.......
IP (tos 0x0, ttl 63, id 54033, offset 0, flags [DF], proto TCP (6), length 59)
    198.10.0.1.43524 > 198.10.0.2.10000: Flags [P.], cksum 0x8c45 (incorrect -> 0x47ae), seq 31080237:31080256, ack 280043075, win 64175, length 19
	0x0000:  0000 0001 0006 0242 c60a 0001 0000 0800  .......B........
	0x0010:  4500 003b d311 4000 3f06 dc93 c60a 0001  E..;..@.?.......
	0x0020:  c60a 0002 aa04 2710 01da 3f2d 10b1 1e43  ......'...?-...C
	0x0030:  5018 faaf 8c45 0000 4120 666f 7374 2063  P....E..A.fost.c
	0x0040:  6120 6e69 6369 6f64 6174 61              a.niciodata
IP (tos 0x0, ttl 64, id 1, offset 0, flags [none], proto TCP (6), length 66)
    198.10.0.1.43524 > 198.10.0.2.10000: Flags [P.], cksum 0x5db9 (correct), seq 31080244:31080270, ack 280043068, win 8192, length 26
	0x0000:  0004 0001 0006 0242 c60a 0003 0000 0800  .......B........
	0x0010:  4500 0042 0001 0000 4006 ee9d c60a 0001  E..B....@.......
	0x0020:  c60a 0002 aa04 2710 01da 3f34 10b1 1e3c  ......'...?4...<
	0x0030:  5018 2000 5db9 0000 4861 636b 6564 2041  P...]...Hacked.A
	0x0040:  2066 6f73 7420 6361 206e 6963 696f 6461  .fost.ca.nicioda
	0x0050:  7461                                     ta
```
Puteți pune și capturi de ecran din wireshark prin orice alte metode de prezentare.
