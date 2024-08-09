import hashlib
import requests


def getFileSha256(file_path):
    with open(file_path, "rb") as f:
        readable_hash = hashlib.sha256(f.read()).hexdigest()
    return readable_hash


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


if __name__ == '__main__':
    file_info = getFileInfo("malware.png")
    if file_info is None:
        print("An error occured")
    else:
        print(file_info['data']['attributes']['last_analysis_stats']['suspicious'])
