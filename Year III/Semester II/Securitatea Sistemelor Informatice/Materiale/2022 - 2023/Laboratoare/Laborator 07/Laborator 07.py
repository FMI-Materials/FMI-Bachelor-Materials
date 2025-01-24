import hashlib

with open("malware", "rb") as f:
    bytes = f.read()
    readable_hash = hashlib.sha256(bytes).hexdigest()
    print(f"SHA-256 value: {readable_hash}")