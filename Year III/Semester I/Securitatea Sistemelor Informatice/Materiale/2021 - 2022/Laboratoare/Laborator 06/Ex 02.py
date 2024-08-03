import secrets
import hashlib
import os


# Generează o parolă de minim 10 caractere care conține cel puțin o literă mare,
# o literă mică, o cifră și un caracter special (.!$@).
def generatePassword():
    alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    numbers = "1234567890"
    characters = alphabet.lower() + alphabet + numbers + ".!$@"
    base = ''.join([secrets.choice(l) for l in [alphabet.lower(), alphabet, numbers, ".!$@"]])
    return base + ''.join(secrets.choice(characters) for _ in range(6))


print(generatePassword())

# Generează un string URL-safe de (cel puțin) 32 caractere.
print(secrets.token_urlsafe(32))

# Generează un token hexazecimal de (cel puțin) 32 cifre hexazecimale.
print(secrets.token_hex(32))

def hashPassword(password):
    salt = os.urandom(32)
    key = hashlib.pbkdf2_hmac(
        'sha256',
        password.encode('utf-8'),
        salt,
        100000
    )
    return salt, key
