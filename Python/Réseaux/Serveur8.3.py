import socket
import os
import time

HOST = '0.0.0.0'
PORT = 12347
SAVE_DIR = '/home/save/'

os.makedirs(SAVE_DIR, exist_ok=True)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print(f"Serveur en écoute sur le port {PORT}")
    conn, addr = s.accept()
    with conn:
        ip_client = addr[0]
        t = time.localtime()
        filename = f"{SAVE_DIR}{ip_client}_{t.tm_year}_{t.tm_mon:02}_{t.tm_mday:02}.txt"
        with open(filename,"wb") as f:
            while True:
                data = conn.recv(1024)
                if not data:
                    break
                f.write(data)
        print(f"Fichier reçu et sauvegardé dans {filename}")