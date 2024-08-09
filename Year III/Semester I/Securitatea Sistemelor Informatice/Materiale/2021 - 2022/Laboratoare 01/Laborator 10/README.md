## Ex 2 (de verificat)


```
openssl genrsa -out alice_sk.pem 2048
```

Rezultat:

```
Generating RSA private key, 2048 bit long modulus
............+++
.....+++
e is 65537 (0x10001)
```

 - Valoarea exponentului de criptare: e = 65537

```
openssl rsa -in alice_sk.pem -text
```

 -  Decodați această cheie. Aflați valoarea modulului N și a celor două numere prime p și q:
```
modulus:
    00:e8:bd:c2:32:e5:c4:2b:3b:1f:cf:f1:12:98:a2:
    3d:e8:15:f0:e0:ef:ff:5f:f8:1d:3d:41:b1:67:cb:
    4a:e5:73:7c:1c:c3:07:e6:61:72:a8:df:43:74:10:
    ff:5f:7f:53:8a:e5:7c:79:60:c0:80:9f:8f:e0:e1:
    76:dc:f5:a3:1b:38:b9:d0:fb:a6:56:0b:3b:87:8a:
    a6:0b:a8:d8:8f:e3:bb:2b:24:1c:0f:12:9f:1f:06:
    7f:1c:23:a2:a8:0a:4e:2a:1f:2a:66:29:47:60:6f:
    55:a2:20:f9:38:59:7b:9a:ac:d5:35:1e:d0:28:40:
    40:c5:5b:2c:03:73:99:ce:59:5e:f8:3f:45:1c:36:
    e8:18:05:ec:12:08:c5:02:cd:c6:3e:26:92:d2:a8:
    75:89:3b:7a:81:cf:48:df:94:58:b1:e7:bd:4d:71:
    c2:16:c3:4a:b3:ca:36:ee:c0:85:04:78:1f:95:af:
    43:2c:84:58:1a:17:1e:42:ca:6a:eb:14:45:b1:71:
    1e:72:c5:59:1f:f3:89:14:5e:37:2b:bb:a3:1c:cb:
    46:f5:6f:b9:5a:29:13:ca:ac:80:73:da:1a:24:59:
    d6:a5:e7:3e:68:75:ea:1b:3e:03:72:24:57:39:b0:
    d0:a5:fb:92:d1:70:18:69:87:d6:80:bc:96:20:08:
    72:87
prime1:
    00:ff:2d:7c:68:f8:f8:52:a6:25:8b:1c:05:38:a5:
    32:90:6f:80:26:43:30:0d:42:27:d9:de:98:08:aa:
    40:2c:7a:09:7f:ca:53:b8:ae:82:f2:17:57:57:10:
    a6:79:c6:cd:c5:3c:40:b4:24:ea:5f:0c:76:01:81:
    5f:89:b2:fc:25:b6:9b:58:0f:6c:5a:0d:cf:ec:e0:
    d0:89:7a:0c:3b:4c:80:9e:f1:36:53:27:5a:3a:5d:
    d0:ef:a8:9c:0f:de:7a:f7:78:d4:20:81:c5:96:cc:
    c2:44:e6:47:f5:0e:13:85:4f:e0:e2:2b:4c:5b:5a:
    34:ea:c7:38:63:e1:f2:0b:5b
prime2:
    00:e9:7d:c3:62:46:f5:5a:aa:e0:bc:ea:72:3d:fc:
    c2:f5:40:35:91:b4:ae:d5:36:05:60:0a:a5:48:1f:
    69:f6:5a:af:ea:0b:49:79:ac:bf:86:a9:f8:a7:e0:
    74:52:41:bd:ce:9a:f8:f4:40:dd:39:f1:04:08:92:
    83:c7:be:f5:11:26:eb:72:2e:7a:3e:6c:50:6f:6b:
    2c:64:47:8e:df:e5:b6:40:71:59:97:69:71:68:2f:
    03:7f:5d:12:03:2a:3a:6d:0d:4c:97:31:84:26:4f:
    a3:0f:cd:30:3c:4c:2e:93:e8:4f:90:95:90:b1:4b:
    53:79:9f:bb:b1:dc:a6:99:45
```

 - Cheia lui Alice nu este protejată în niciun fel, deci este vulnerabilă. Alegeți o parolă puternică și generați o nouă cheie protejată folosind această parolă și AES256.
```
openssl genrsa -aes256 -out alice_sk.pem 2048 
```
 - Cheia criptata contine si detalii despre criptare
```
Proc-Type: 4,ENCRYPTED
DEK-Info: AES-256-CBC,AF3F65B7A7B7C0A8C344E97B4D2BC98F
```

 - Pentru a decripta cheia, rulam urmatoarea comanda si introducem parola:
```
openssl rsa -in alice_sk_protected.pem
```
 - Valoarea exponentului de criptare: e = 65537
 - Exportați cheia publică a lui Alice în fișierul alice_pk.pem.
```
openssl rsa -in alice_sk.pem -RSAPublicKey_out -out alice_pk.pem 
```
 - Decodați această cheie pentru a vedea valorile modulului și exponentului.
```
openssl rsa -RSAPublicKey_in -in alice_pk.pem -text
```
```
Public-Key: (2048 bit)
Modulus:
    00:d9:b8:f6:17:18:66:88:33:a4:57:6b:d4:dd:11:
    4c:87:d1:23:b4:4e:cc:06:98:45:e8:5a:22:1e:36:
    58:dd:c9:9f:54:90:5f:5c:09:94:24:53:32:d4:1d:
    8b:6a:35:e8:8d:70:f6:13:de:4d:7d:04:48:d5:3e:
    b1:b9:cb:f4:e4:29:b1:75:cf:62:fa:0a:38:d1:f4:
    d5:b2:f5:14:1d:7a:bd:81:04:3f:6b:ef:75:4a:24:
    e5:c1:ec:a8:24:ea:18:ad:53:44:ea:1b:57:b1:21:
    f5:ec:71:0e:50:c1:f3:fb:53:00:9c:8f:fe:b5:11:
    2a:1c:eb:e8:a8:24:f6:2d:13:d0:93:05:91:e6:24:
    d4:e0:e4:39:27:4c:e7:a4:b2:85:5a:15:6b:34:ad:
    58:16:f0:e2:f8:42:75:85:c4:f9:3f:36:9b:ad:f9:
    0c:3b:10:fd:53:0d:5b:01:89:e2:7b:eb:ed:8b:59:
    44:87:e4:de:b9:8e:20:8a:d2:5e:6e:28:37:ed:56:
    f4:a4:98:66:8a:2f:e8:f1:c4:dd:38:b8:11:7c:32:
    6a:29:04:33:bc:fe:eb:d9:d8:b5:19:46:9a:e4:32:
    c9:c9:e1:39:f8:4a:fa:77:07:2e:82:3a:d6:8d:b5:
    89:b3:00:5f:7e:8b:f7:e6:ad:e8:5e:ba:b8:4d:ca:
    6b:5b
Exponent: 65537 (0x10001)
```


## Ex 3 (de verificat)
 - Criptați fișierul bob_message.txt folosind RSA [4] și cheia generată anterior.
```
openssl pkeyutl -sign -in bob_message.txt -inkey alice_sk.pem -out bob_message_encrypted.txt
```
 - Incercand sa criptam bob_message.rtf, primim urmatoarea eroare: ```data too large for key size```.
 - Generam o cheie simetrica pe 256 biti:
```
openssl rand 32 > bob_symetric_key.key
```
 - Criptam fisierul bob_message.rtf cu AES-CTR.
```
openssl enc -aes256 -a -in bob_message.rtf -out bob_message_encrypted.rtf -kfile bob_symetric_key.key 
```
 - Criptați noua cheie asimetric, folosind RSA.
```
openssl pkeyutl -sign -in bob_symetric_key.key -inkey alice_sk.pem -out bob_symetric_key_encrypted.key
```
 - Folosiți fișierele criptate primite (criptarea cheii AES folosind RSA și criptarea mesajului folosind AES-CTR), decriptați și obțineți mesajul inițial.
```
openssl enc -aes256 -d -in bob_message_encrypted.rtf -kfile bob_symetric_key.key 
```
