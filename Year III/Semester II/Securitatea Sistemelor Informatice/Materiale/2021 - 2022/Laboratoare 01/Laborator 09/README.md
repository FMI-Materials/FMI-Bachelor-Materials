## Ex 2 (de verificat)


```
from Crypto.Cipher import AES

key = b'O cheie oarecare'
data = b'testtesttesttesttesttesttesttesttesttesttesttest'

cipher = AES.new(key, AES.MODE_ECB)
cipher.encrypt(data)
```

 - Secventa de mai sus creeaza un text codat simetric (din cheia primita)
 - Algoritmul dat foloseste modul de operare **ECB** (Electronic Code Book). 
 - Nu, modul de operare **ECB** este nesigur deoarece texte identice sunt codate exact la fel, indiferent de lungimea lor. Astfel un atacator poate observa modele intre mesaje criptate. Exemplu:

```

b'testtesttesttesttesttesttesttesttesttesttesttesttesttesttesttest'

b'testtesttesttesttesttesttesttesttesttesttesttest'

b'\x88\x10\x86\xe2\xf3\xaai)\x9fz\xcb\xf0h4\xa4\xec\x88\x10\x86\xe2\xf3\xaai)\x9fz\xcb\xf0h4\xa4\xec\x88\x10\x86\xe2\xf3\xaai)\x9fz\xcb\xf0h4\xa4\xec\x88\x10\x86\xe2\xf3\xaai)\x9fz\xcb\xf0h4\xa4\xec'
b'\x88\x10\x86\xe2\xf3\xaai)\x9fz\xcb\xf0h4\xa4\xec\x88\x10\x86\xe2\xf3\xaai)\x9fz\xcb\xf0h4\xa4\xec\x88\x10\x86\xe2\xf3\xaai)\x9fz\xcb\xf0h4\xa4\xec'

```
 - Dimensiune cheie si bloc: 16

```
key = b'O cheie oarecare'
data = b'test'

cipher = AES.new(key, AES.MODE_CCM)
res = cipher.encrypt(data)
print(res)
```

 - Am folosit modul de operare CCM ce suporta blocuri de orice dimensiune (counter with cipher block chaining message authentication code; counter with CBC-MAC) 

## Ex 3 (de verificat)

Fie codul de encriptare

```
from Crypto.Cipher import DES

key1 = '\x10\x00\x00\x00\x00\x00\x00\x00'
key2 = '\x20\x00\x00\x00\x00\x00\x00\x00'

cipher1 = DES.new(key1, DES.MODE_ECB)
cipher2 = DES.new(key2, DES.MODE_ECB)

plaintext = "Provocare MitM!!"
ciphertext = cipher2.encrypt(cipher1.encrypt(plaintext))

print(ciphertext)
```

```
def encodeText(k: int, text):
    key = format(k, 'x') + '\x00\x00\x00\x00\x00\x00\x00'
    cipher1 = DES.new(key.encode(), DES.MODE_ECB)
    return cipher1.encrypt(text)


def decodeText(k: int, text):
    key = format(k, 'x') + '\x00\x00\x00\x00\x00\x00\x00'
    cipher1 = DES.new(key.encode(), DES.MODE_ECB)
    return cipher1.decrypt(text)

```
Pentru cautarea valorilor i si j, vom rula urmatorul algoritm brute force.
```
def bruteForce(plaintext_result, ciphertext):
    for i in range(16):
        for j in range(16):
            plaintext = decodeText(j, decodeText(i, ciphertext))
            if plaintext == plaintext_result:
                return i, j
    return False
```

Un algoritm mai eficient va fii Meet in the middle, descris mai jos:

```
def mitm(plaintext, ciphertext_result):
    A = dict()
    candidates = list()

    def testCandidate(candidate):
        return decodeText(candidate[1], decodeText(candidate[0], ciphertext_result)) == plaintext

    for i in range(16):
        a = encodeText(i, plaintext)
        if a not in A:
            A[a] = i
    for j in range(16):
        b = decodeText(j, ciphertext_result)
        if b in A:
            candidate = (j, A[b])
            if testCandidate(candidate):
                candidates.append(candidate)
    if len(candidates) == 0:
        return False
    return candidates
```

Acesta cripteaza si decripteaza cate 2^k+1 key. In total au fost testate 32 de chei.
