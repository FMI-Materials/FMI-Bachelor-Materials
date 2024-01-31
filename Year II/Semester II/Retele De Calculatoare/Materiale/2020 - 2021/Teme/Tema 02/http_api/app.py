from flask import Flask, jsonify
from flask import request, Response

from subnet import Subnet

app = Flask(__name__)


@app.route('/subnet', methods=['POST'])
def post_method():
    data = request.get_json()
    if "subnet" not in data.keys() or "dim" not in data.keys():
        return Response(status=400)
    subnet = Subnet(data["subnet"], data["dim"])
    partition = subnet.partition()
    if partition is None:
        return jsonify({"error": "Cannot partition subnet"}), 400
    return jsonify(partition)


@app.route('/')
def index():
    return "HTTP Service: <a href='/subnet'>/subnet</a><br>"


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=80)
