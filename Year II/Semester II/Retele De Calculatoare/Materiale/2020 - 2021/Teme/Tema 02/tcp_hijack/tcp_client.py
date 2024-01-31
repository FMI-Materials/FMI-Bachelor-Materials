# TCP client
import socket
import logging
import time

logging.basicConfig(format = u'[LINE:%(lineno)d]# %(levelname)-8s [%(asctime)s]  %(message)s', level = logging.NOTSET)

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, proto=socket.IPPROTO_TCP)

port = 10000
adresa = '198.10.0.2'
server_address = (adresa, port)
poezie = ["A fost odata ca in povesti",
          "A fost ca niciodata", 
          "Din rude mari, imparatesti",
          "O prea frumoasa fata"]

try:
    logging.info('Handshake cu %s', str(server_address))
    sock.connect(server_address)
    time.sleep(1)

    curr_idx = 0
    curr_time = time.time()
    while True:
        if time.time() - curr_time > 2:
            break

        time.sleep(1)
        mesaj = poezie[curr_idx]
        # mesaj = "Salut"
        curr_idx = (curr_idx + 1) % 4
        sock.send(mesaj.encode('utf-8'))

        data = sock.recv(1024)
        if len(data) > 0:
            curr_time = time.time()
            logging.info('Content primit: "%s"', data)

finally:
    logging.info('closing socket')
    sock.close()
