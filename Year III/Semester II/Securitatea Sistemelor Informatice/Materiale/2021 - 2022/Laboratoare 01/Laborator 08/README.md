## Ex 2 (nerezolvat)

 - Exemplu parola corecta diferita de ```fmiSSI```: ```fmiSSIhelloworld```


## Ex 3 (de verificat)

```
def getFileSha256(file_path):
    with open(file_path, "rb") as f:
        readable_hash = hashlib.sha256(f.read()).hexdigest()
    return readable_hash
```

```
def getFileInfo(file_path):
    api_url = 'https://www.virustotal.com/api/v3/files'
    headers = {'x-apikey': '104855077ddf5881a40aa80187c251e63c2315b1540acf5dde0a2e02ac756554'}
    with open(file_path, 'rb') as file:
        files = {'file': ('malware.png', file)}
        response = requests.post(api_url, headers=headers, files=files)
        if response.status_code == 200:
            file_identifier = getFileSha256(file_path)
            url = f"https://www.virustotal.com/api/v3/files/{file_identifier}"
            response2 = requests.request("GET", url, headers=headers)
            if response2.status_code == 200:
                return response2.json()
    return None
```

## Ex 4 (de verificat)


Data la care a fost compilat programul:
```
compiler-stamp: 0x61AFAB7D (Tue Dec 07 20:44:13 2021)
```

 - Scrisa in little endian, aceasta devine: ```7DABAF61``` si se poate gasi in HxD (offset 88).
 - Valoarea hex convertita in decimal este: ```2108403553```
 - Valoarea decimal reprezinta timestamp-ul la care a fost compilat programul. Acesta timestamp este convertit prin [https://www.epochconverter.com/hex](https://www.epochconverter.com/hex).





