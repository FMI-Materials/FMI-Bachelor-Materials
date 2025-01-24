## Ex 1

 - Candidate 1 returneaza 0 (converge spre 0)
 - Candidate 2 Converge spre infinit - crestere liniara usor predictibila
 - Candidate 3 returneaza un singur rezultat - output > input

Pentru a determina un PRNG, ar trebui sa returneze o secventa de numere pseudo-random 

## Ex 2

```python
import secrets
def generatePassword():
    alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    numbers = "1234567890"
    characters = alphabet.lower() + alphabet + numbers + ".!$@"
    base = ''.join([secrets.choice(l) for l in [alphabet.lower(), alphabet, numbers, ".!$@"]])
    return base + ''.join(secrets.choice(characters) for _ in range(6))
```
Ex. Utilizare: Generare parole random (securizate) pentru utilizatori (Buton generare parola random in aplicatie).

```python
secrets.token_urlsafe(32)
```
Ex. Utilizare: Token asignat sesiunii de autentificare a unui utilizator

```python
secrets.token_hex(32)
```
Ex. Utilizare: Generare key random pentru criptarea unor mesaje

```python
def check(a, b):
    return secrets.compare_digest(a, b)
```

```python
secrets.randbits(100 * 8)
```

```python
import hashlib
import os
def hashPassword(password):
    salt = os.urandom(32)
    key = hashlib.pbkdf2_hmac(
        'sha256',
        password.encode('utf-8'),
        salt,
        100000
    )
    return salt, key
```
Am folosit libraria _**hashlib**_ pentru hashuirea parolelor 
