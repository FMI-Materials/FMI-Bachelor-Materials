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


print(get_ip_address("apple.com"))
