# Soluție

## 1. DNS over HTTPS
Am implementat funcția aici:
```python
import requests
import json

def get_ip_address(name):
    headers = {
        "Accept": "application/dns-json"
    }
    response = requests.get('https://cloudflare-dns.com/dns-query?name=' + name, headers=headers)

    response_data = json.loads(response.text)

    if "Answer" in response_data:
        answers = response_data["Answer"]
        if len(answers) > 0:
            answer = answers[0]
            return answer["data"]
    return None
```
iar aici e un exemplu de execuție
```python
print(get_ip_address("darius.buhai.ro"))
```

## 2. Traceroute

Am implementat soluția iar aici este output-ul:

### Ruta către 185.57.83.167
```
62.217.248.130 - Bucharest, Bucuresti, Romania
93.122.133.92 - Cluj-Napoca, Cluj, Romania
185.1.103.6 - None, None, Romania
89.238.235.98 - Dumbravita, Hunedoara, Romania
185.193.54.58 - None, None, Romania
84.239.0.138 - None, None, Romania
185.57.83.167 - None, None, Romania
```

### Ruta către 172.217.19.100
```
81.196.21.100 - Rosiorii de Vede, Teleorman, Romania
108.170.252.1 - None, None, United States
108.170.252.19 - None, None, United States
108.170.236.250 - None, None, United States
74.125.242.225 - None, None, United States
216.239.35.183 - None, None, United States
172.217.19.100 - None, None, United States
```

### Ruta către 139.99.183.16
```
195.66.224.177 - None, None, United Kingdom
202.84.178.13 - None, None, Hong Kong
202.84.140.141 - None, None, Hong Kong
202.84.143.157 - None, None, Hong Kong
202.84.219.173 - None, None, Hong Kong
54.36.50.141 - None, None, France
54.36.50.141 - None, None, France
103.5.15.51 - Central, Central and Western District, Hong Kong
103.5.14.219 - Central, Central and Western District, Hong Kong
```


## 3. Reliable UDP

### Emițător - mesaje de logging
Rulăm `docker-compose logs emitator` și punem rezultatul aici:
```
Attaching to tema1-unibucperformance_emitator_1
emitator_1  | + ip route del default
emitator_1  | + ip route add default via 172.8.0.1
emitator_1  | + echo 'nameserver 8.8.8.8'
emitator_1  | + iptables -A OUTPUT -p tcp --tcp-flags RST RST -j DROP
emitator_1  | + sleep infinity
```

Rulăm `docker-compose exec emitator bash -c "python3 /elocal/src/emitator.py -p 10000"` și punem rezultatul aici:
```
[LINE:41]# WARNING  [2021-04-05 07:07:25,509]  Connection timed out, retrying...
[LINE:41]# WARNING  [2021-04-05 07:07:31,517]  Connection timed out, retrying...
[LINE:184]# INFO     [2021-04-05 07:07:31,620]  Connection initialized
[LINE:185]# INFO     [2021-04-05 07:07:31,621]  Ack Nr: "3344299577"
[LINE:186]# INFO     [2021-04-05 07:07:31,621]  Window: "5"
[LINE:124]# WARNING  [2021-04-05 07:07:31,902]  Socket timed out on payload 5 
[LINE:130]# WARNING  [2021-04-05 07:07:31,902]  Missed 1 package(s), resending window...
[LINE:124]# WARNING  [2021-04-05 07:07:32,364]  Socket timed out on payload 4 
[LINE:124]# WARNING  [2021-04-05 07:07:32,717]  Socket timed out on payload 5 
[LINE:130]# WARNING  [2021-04-05 07:07:32,718]  Missed 2 package(s), resending window...
[LINE:124]# WARNING  [2021-04-05 07:07:33,170]  Socket timed out on payload 5 
[LINE:130]# WARNING  [2021-04-05 07:07:33,171]  Missed 1 package(s), resending window...
[LINE:124]# WARNING  [2021-04-05 07:07:33,618]  Socket timed out on payload 5 
[LINE:130]# WARNING  [2021-04-05 07:07:33,618]  Missed 1 package(s), resending window...
[LINE:193]# INFO     [2021-04-05 07:07:33,727]  5 messages send, 1 windows available
[LINE:194]# INFO     [2021-04-05 07:07:33,728]  Current seq number: 3344306577
[LINE:193]# INFO     [2021-04-05 07:07:33,835]  1 messages send, 5 windows available
[LINE:194]# INFO     [2021-04-05 07:07:33,835]  Current seq number: 3344307977
[LINE:193]# INFO     [2021-04-05 07:07:33,953]  5 messages send, 4 windows available
[LINE:194]# INFO     [2021-04-05 07:07:33,953]  Current seq number: 3344314977
[LINE:193]# INFO     [2021-04-05 07:07:34,066]  4 messages send, 3 windows available
[LINE:194]# INFO     [2021-04-05 07:07:34,066]  Current seq number: 3344320577
[LINE:193]# INFO     [2021-04-05 07:07:34,180]  3 messages send, 2 windows available
[LINE:194]# INFO     [2021-04-05 07:07:34,180]  Current seq number: 3344324777
[LINE:193]# INFO     [2021-04-05 07:07:34,296]  2 messages send, 5 windows available
[LINE:194]# INFO     [2021-04-05 07:07:34,297]  Current seq number: 3344327577
[LINE:124]# WARNING  [2021-04-05 07:07:34,589]  Socket timed out on payload 5 
[LINE:130]# WARNING  [2021-04-05 07:07:34,589]  Missed 1 package(s), resending window...
[LINE:193]# INFO     [2021-04-05 07:07:34,702]  5 messages send, 4 windows available
[LINE:194]# INFO     [2021-04-05 07:07:34,702]  Current seq number: 3344334577
[LINE:193]# INFO     [2021-04-05 07:07:34,820]  4 messages send, 3 windows available
[LINE:194]# INFO     [2021-04-05 07:07:34,821]  Current seq number: 3344340177
[LINE:193]# INFO     [2021-04-05 07:07:34,932]  3 messages send, 2 windows available
[LINE:194]# INFO     [2021-04-05 07:07:34,932]  Current seq number: 3344344377
[LINE:124]# WARNING  [2021-04-05 07:07:35,104]  Socket timed out on payload 1 
[LINE:124]# WARNING  [2021-04-05 07:07:35,271]  Socket timed out on payload 2 
[LINE:130]# WARNING  [2021-04-05 07:07:35,271]  Missed 2 package(s), resending window...
[LINE:193]# INFO     [2021-04-05 07:07:35,379]  2 messages send, 2 windows available
[LINE:194]# INFO     [2021-04-05 07:07:35,379]  Current seq number: 3344347177
[LINE:193]# INFO     [2021-04-05 07:07:35,385]  2 messages send, 2 windows available
[LINE:194]# INFO     [2021-04-05 07:07:35,385]  Current seq number: 3344349977
[LINE:124]# WARNING  [2021-04-05 07:07:35,493]  Socket timed out on payload 2 
[LINE:130]# WARNING  [2021-04-05 07:07:35,493]  Missed 1 package(s), resending window...
[LINE:130]# WARNING  [2021-04-05 07:07:35,604]  Missed 1 package(s), resending window...
[LINE:193]# INFO     [2021-04-05 07:07:35,711]  2 messages send, 5 windows available
[LINE:194]# INFO     [2021-04-05 07:07:35,711]  Current seq number: 3344352777
[LINE:124]# WARNING  [2021-04-05 07:07:35,996]  Socket timed out on payload 5 
[LINE:130]# WARNING  [2021-04-05 07:07:35,996]  Missed 1 package(s), resending window...
[LINE:124]# WARNING  [2021-04-05 07:07:36,475]  Socket timed out on payload 5 
[LINE:130]# WARNING  [2021-04-05 07:07:36,475]  Missed 1 package(s), resending window...
[LINE:124]# WARNING  [2021-04-05 07:07:36,914]  Socket timed out on payload 5 
[LINE:130]# WARNING  [2021-04-05 07:07:36,914]  Missed 1 package(s), resending window...
[LINE:124]# WARNING  [2021-04-05 07:07:37,351]  Socket timed out on payload 5 
[LINE:130]# WARNING  [2021-04-05 07:07:37,352]  Missed 1 package(s), resending window...
[LINE:193]# INFO     [2021-04-05 07:07:37,462]  5 messages send, 4 windows available
[LINE:194]# INFO     [2021-04-05 07:07:37,462]  Current seq number: 3344359777
[LINE:124]# WARNING  [2021-04-05 07:07:37,742]  Socket timed out on payload 4 
[LINE:130]# WARNING  [2021-04-05 07:07:37,743]  Missed 1 package(s), resending window...
[LINE:193]# INFO     [2021-04-05 07:07:37,854]  4 messages send, 5 windows available
[LINE:194]# INFO     [2021-04-05 07:07:37,855]  Current seq number: 3344365377
[LINE:193]# INFO     [2021-04-05 07:07:37,973]  5 messages send, 4 windows available
[LINE:194]# INFO     [2021-04-05 07:07:37,973]  Current seq number: 3344372377
[LINE:124]# WARNING  [2021-04-05 07:07:38,272]  Socket timed out on payload 4 
[LINE:130]# WARNING  [2021-04-05 07:07:38,273]  Missed 1 package(s), resending window...
[LINE:193]# INFO     [2021-04-05 07:07:38,389]  4 messages send, 4 windows available
[LINE:194]# INFO     [2021-04-05 07:07:38,389]  Current seq number: 3344377977
[LINE:193]# INFO     [2021-04-05 07:07:38,509]  4 messages send, 5 windows available
[LINE:194]# INFO     [2021-04-05 07:07:38,509]  Current seq number: 3344383577
[LINE:193]# INFO     [2021-04-05 07:07:38,622]  5 messages send, 5 windows available
[LINE:194]# INFO     [2021-04-05 07:07:38,623]  Current seq number: 3344390577
[LINE:124]# WARNING  [2021-04-05 07:07:38,911]  Socket timed out on payload 5 
[LINE:130]# WARNING  [2021-04-05 07:07:38,911]  Missed 1 package(s), resending window...
[LINE:124]# WARNING  [2021-04-05 07:07:39,341]  Socket timed out on payload 5 
[LINE:130]# WARNING  [2021-04-05 07:07:39,342]  Missed 1 package(s), resending window...
[LINE:193]# INFO     [2021-04-05 07:07:39,450]  5 messages send, 5 windows available
[LINE:194]# INFO     [2021-04-05 07:07:39,450]  Current seq number: 3344397577
[LINE:124]# WARNING  [2021-04-05 07:07:39,716]  Socket timed out on payload 5 
[LINE:130]# WARNING  [2021-04-05 07:07:39,716]  Missed 1 package(s), resending window...
[LINE:124]# WARNING  [2021-04-05 07:07:40,138]  Socket timed out on payload 5 
[LINE:130]# WARNING  [2021-04-05 07:07:40,138]  Missed 1 package(s), resending window...
[LINE:193]# INFO     [2021-04-05 07:07:40,246]  5 messages send, 3 windows available
[LINE:194]# INFO     [2021-04-05 07:07:40,246]  Current seq number: 3344404577
[LINE:193]# INFO     [2021-04-05 07:07:40,352]  3 messages send, 1 windows available
[LINE:194]# INFO     [2021-04-05 07:07:40,353]  Current seq number: 3344408777
[LINE:193]# INFO     [2021-04-05 07:07:40,358]  1 messages send, 4 windows available
[LINE:194]# INFO     [2021-04-05 07:07:40,359]  Current seq number: 3344410177
[LINE:124]# WARNING  [2021-04-05 07:07:40,573]  Socket timed out on payload 4 
[LINE:130]# WARNING  [2021-04-05 07:07:40,573]  Missed 1 package(s), resending window...
[LINE:193]# INFO     [2021-04-05 07:07:40,681]  4 messages send, 2 windows available
[LINE:194]# INFO     [2021-04-05 07:07:40,681]  Current seq number: 3344415777
[LINE:193]# INFO     [2021-04-05 07:07:40,793]  2 messages send, 2 windows available
[LINE:194]# INFO     [2021-04-05 07:07:40,794]  Current seq number: 3344418577
[LINE:193]# INFO     [2021-04-05 07:07:40,901]  2 messages send, 3 windows available
[LINE:194]# INFO     [2021-04-05 07:07:40,901]  Current seq number: 3344421377
[LINE:193]# INFO     [2021-04-05 07:07:40,908]  3 messages send, 3 windows available
[LINE:194]# INFO     [2021-04-05 07:07:40,908]  Current seq number: 3344425577
[LINE:193]# INFO     [2021-04-05 07:07:41,021]  3 messages send, 5 windows available
[LINE:194]# INFO     [2021-04-05 07:07:41,021]  Current seq number: 3344429777
[LINE:193]# INFO     [2021-04-05 07:07:41,143]  5 messages send, 4 windows available
[LINE:194]# INFO     [2021-04-05 07:07:41,144]  Current seq number: 3344436777
[LINE:124]# WARNING  [2021-04-05 07:07:41,435]  Socket timed out on payload 4 
[LINE:130]# WARNING  [2021-04-05 07:07:41,436]  Missed 1 package(s), resending window...
[LINE:193]# INFO     [2021-04-05 07:07:41,543]  4 messages send, 2 windows available
[LINE:194]# INFO     [2021-04-05 07:07:41,543]  Current seq number: 3344442377
[LINE:193]# INFO     [2021-04-05 07:07:41,652]  1 messages send, 1 windows available
[LINE:194]# INFO     [2021-04-05 07:07:41,652]  Current seq number: 3344442484
[LINE:199]# INFO     [2021-04-05 07:07:41,758]  Connection closed
```

### Receptor - mesaje de logging
Rulăm `docker-compose logs receptor` și punem rezultatul aici:
```
Attaching to tema1-unibucperformance_receptor_1
receptor_1  | + ip route del default
receptor_1  | + ip route add default via 198.8.0.1
receptor_1  | + echo 'nameserver 8.8.8.8'
receptor_1  | + iptables -A OUTPUT -p tcp --tcp-flags RST RST -j DROP
receptor_1  | + sleep infinity
```

Rulăm `docker-compose exec receptor bash -c "python3 /elocal/src/receptor.py -p 10000"` și punem rezultatul aici:
```
[LINE:50]# INFO     [2021-04-05 07:11:21,164]  The server has started on 198.8.0.2 and port 10000
[LINE:51]# INFO     [2021-04-05 07:11:21,164]  Window has been set to 3
[LINE:57]# INFO     [2021-04-05 07:11:21,165]  Waiting for messages..
[LINE:79]# INFO     [2021-04-05 07:11:22,688]  Connection initialized
[LINE:88]# INFO     [2021-04-05 07:11:22,796]  Message received. Seq no: 2586892476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:22,797]  Message received. Seq no: 2586893876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:22,797]  Message received. Seq no: 2586895276, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:22,894]  Message received. Seq no: 2586896676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:22,895]  Message received. Seq no: 2586898076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:22,897]  Message received. Seq no: 2586899476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:22,897]  Message received. Seq no: 2586900876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,161]  Message received. Seq no: 2586896676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,162]  Message received. Seq no: 2586898076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,162]  Message received. Seq no: 2586899476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,163]  Message received. Seq no: 2586900876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,267]  Message received. Seq no: 2586902276, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,268]  Message received. Seq no: 2586903676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,271]  Message received. Seq no: 2586905076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,271]  Message received. Seq no: 2586906476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,273]  Message received. Seq no: 2586907876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,383]  Message received. Seq no: 2586909276, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,387]  Message received. Seq no: 2586910676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,388]  Message received. Seq no: 2586912076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,487]  Message received. Seq no: 2586913476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,488]  Message received. Seq no: 2586914876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,596]  Message received. Seq no: 2586916276, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,596]  Message received. Seq no: 2586917676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,599]  Message received. Seq no: 2586919076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,600]  Message received. Seq no: 2586920476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,602]  Message received. Seq no: 2586921876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,711]  Message received. Seq no: 2586923276, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,815]  Message received. Seq no: 2586924676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,816]  Message received. Seq no: 2586926076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,819]  Message received. Seq no: 2586927476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,820]  Message received. Seq no: 2586928876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,824]  Message received. Seq no: 2586930276, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,933]  Message received. Seq no: 2586931676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,938]  Message received. Seq no: 2586933076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,938]  Message received. Seq no: 2586934476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,942]  Message received. Seq no: 2586935876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:23,943]  Message received. Seq no: 2586937276, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:24,049]  Message received. Seq no: 2586938676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:24,049]  Message received. Seq no: 2586940076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:24,052]  Message received. Seq no: 2586941476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:24,518]  Message received. Seq no: 2586938676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:24,519]  Message received. Seq no: 2586940076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:24,520]  Message received. Seq no: 2586941476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:24,631]  Message received. Seq no: 2586942876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:24,634]  Message received. Seq no: 2586944276, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:24,739]  Message received. Seq no: 2586945676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:24,740]  Message received. Seq no: 2586947076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:24,999]  Message received. Seq no: 2586945676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,000]  Message received. Seq no: 2586947076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,109]  Message received. Seq no: 2586948476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,111]  Message received. Seq no: 2586949876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,221]  Message received. Seq no: 2586951276, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,223]  Message received. Seq no: 2586952676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,224]  Message received. Seq no: 2586954076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,327]  Message received. Seq no: 2586955476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,434]  Message received. Seq no: 2586956876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,436]  Message received. Seq no: 2586958276, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,437]  Message received. Seq no: 2586959676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,439]  Message received. Seq no: 2586961076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,544]  Message received. Seq no: 2586962476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,646]  Message received. Seq no: 2586963876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,646]  Message received. Seq no: 2586965276, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,649]  Message received. Seq no: 2586966676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,650]  Message received. Seq no: 2586968076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,652]  Message received. Seq no: 2586969476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,760]  Message received. Seq no: 2586970876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,762]  Message received. Seq no: 2586972276, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,763]  Message received. Seq no: 2586973676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,765]  Message received. Seq no: 2586975076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,865]  Message received. Seq no: 2586976476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,867]  Message received. Seq no: 2586977876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,868]  Message received. Seq no: 2586979276, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:25,869]  Message received. Seq no: 2586980676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:26,127]  Message received. Seq no: 2586976476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:26,127]  Message received. Seq no: 2586977876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:26,128]  Message received. Seq no: 2586979276, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:26,128]  Message received. Seq no: 2586980676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:26,549]  Message received. Seq no: 2586976476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:26,549]  Message received. Seq no: 2586977876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:26,550]  Message received. Seq no: 2586979276, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:26,551]  Message received. Seq no: 2586980676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:26,663]  Message received. Seq no: 2586982076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:26,666]  Message received. Seq no: 2586983476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:26,667]  Message received. Seq no: 2586984876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:26,679]  Message received. Seq no: 2586986276, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:26,797]  Message received. Seq no: 2586987676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:26,799]  Message received. Seq no: 2586989076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:26,801]  Message received. Seq no: 2586990476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:26,802]  Message received. Seq no: 2586991876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:27,107]  Message received. Seq no: 2586987676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:27,108]  Message received. Seq no: 2586989076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:27,108]  Message received. Seq no: 2586990476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:27,109]  Message received. Seq no: 2586991876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:27,847]  Message received. Seq no: 2586987676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:27,847]  Message received. Seq no: 2586989076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:27,848]  Message received. Seq no: 2586990476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:27,848]  Message received. Seq no: 2586991876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:27,961]  Message received. Seq no: 2586993276, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:27,967]  Message received. Seq no: 2586994676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:27,968]  Message received. Seq no: 2586996076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:28,080]  Message received. Seq no: 2586997476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:28,081]  Message received. Seq no: 2586998876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:28,082]  Message received. Seq no: 2587000276, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:28,187]  Message received. Seq no: 2587001676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:28,352]  Message received. Seq no: 2587001676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:28,468]  Message received. Seq no: 2587003076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:28,468]  Message received. Seq no: 2587004476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:28,470]  Message received. Seq no: 2587005876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:28,581]  Message received. Seq no: 2587007276, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:28,585]  Message received. Seq no: 2587008676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:28,586]  Message received. Seq no: 2587010076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:28,859]  Message received. Seq no: 2587007276, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:28,860]  Message received. Seq no: 2587008676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:28,860]  Message received. Seq no: 2587010076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:28,971]  Message received. Seq no: 2587011476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:28,972]  Message received. Seq no: 2587012876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:28,979]  Message received. Seq no: 2587014276, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:29,089]  Message received. Seq no: 2587015676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:29,096]  Message received. Seq no: 2587017076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:29,096]  Message received. Seq no: 2587018476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:29,384]  Message received. Seq no: 2587015676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:29,386]  Message received. Seq no: 2587017076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:29,387]  Message received. Seq no: 2587018476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:29,489]  Message received. Seq no: 2587019876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:29,490]  Message received. Seq no: 2587021276, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:29,593]  Message received. Seq no: 2587022676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:29,593]  Message received. Seq no: 2587024076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:29,596]  Message received. Seq no: 2587025476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:29,708]  Message received. Seq no: 2587026876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:29,709]  Message received. Seq no: 2587028276, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:29,710]  Message received. Seq no: 2587029676, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:29,712]  Message received. Seq no: 2587031076, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:29,815]  Message received. Seq no: 2587032476, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:29,818]  Message received. Seq no: 2587033876, message size: 1400 bytes.
[LINE:88]# INFO     [2021-04-05 07:11:29,818]  Message received. Seq no: 2587033983, message size: 107 bytes.
[LINE:84]# INFO     [2021-04-05 07:11:29,921]  Connection closed
```
