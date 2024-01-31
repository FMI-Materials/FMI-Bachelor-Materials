# TCP Server
import socket
import logging
import time
import os

logging.basicConfig(format = u'[LINE:%(lineno)d]# %(levelname)-8s [%(asctime)s]  %(message)s', level = logging.NOTSET)

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, proto=socket.IPPROTO_TCP)

port = 10000
adresa = '0.0.0.0'
server_address = (adresa, port)
sock.bind(server_address)
logging.info("Serverul a pornit pe %s si portnul portul %d", adresa, port)
sock.listen(5)

try:
    while True:
        logging.info('Asteptam conexiui...')
        conexiune, address = sock.accept()
        logging.info("Handshake cu %s", address)
        time.sleep(2)

        curr_time = time.time()
        while True:
            if time.time() - curr_time > 2:
                break
            data = conexiune.recv(1024)
            if len(data) > 0:
                curr_time = time.time()
                logging.info('Content primit: "%s"', data)
                conexiune.send(b"Server a primit mesajul: " + data)
        conexiune.close()
finally:
    logging.info('closing socket')
    sock.close()
    pid = os.getpid()
    logging.info('PID: ' + str(pid))
