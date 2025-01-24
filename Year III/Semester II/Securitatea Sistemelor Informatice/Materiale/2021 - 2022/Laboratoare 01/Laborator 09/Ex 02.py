from Crypto.Cipher import AES

# key = b'O cheie oarecare'
# data = b'testtesttesttesttesttesttesttesttesttesttesttesttesttesttesttest'
#
# cipher = AES.new(key, AES.MODE_ECB)
# res = cipher.encrypt(data)
# print(res)

key = b'O cheie oarecare'
data = b'test'

cipher = AES.new(key, AES.MODE_CCM)
res = cipher.encrypt(data)
print(res)