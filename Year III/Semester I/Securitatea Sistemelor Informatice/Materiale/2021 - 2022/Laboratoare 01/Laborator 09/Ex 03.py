from Crypto.Cipher import DES


def encodeText(k: int, text):
    key = format(k, 'x') + '\x00\x00\x00\x00\x00\x00\x00'
    cipher1 = DES.new(key.encode(), DES.MODE_ECB)
    return cipher1.encrypt(text)


def decodeText(k: int, text):
    key = format(k, 'x') + '\x00\x00\x00\x00\x00\x00\x00'
    cipher1 = DES.new(key.encode(), DES.MODE_ECB)
    return cipher1.decrypt(text)


def bruteForce(plaintext_result, ciphertext):
    for i in range(16):
        for j in range(16):
            plaintext = decodeText(j, decodeText(i, ciphertext))
            if plaintext == plaintext_result:
                return i, j
    return False


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


if __name__ == '__main__':
    plaintext_ = "Provocare MitM!!".encode()
    ciphertext_result_ = encodeText(8, encodeText(14, plaintext_))
    print(ciphertext_result_)

    # This text does not work, format is wrong
    # \xc4\xba\xa1\xd8\x16O\x15\x8a(\xf0\xc1}U\xb3\xe6\xfb
    # G\xfd\xdfpd\xa5\xc9'C\xe2\xf0\x84)\xef\xeb\xf9
    # ciphertext_result_ = b"G\xfd\xdfpd\xa5\xc9'C\xe2\xf0\x84)\xef\xeb\xf9"

    print(bruteForce(plaintext_, ciphertext_result_))
    print(mitm(plaintext_, ciphertext_result_))
