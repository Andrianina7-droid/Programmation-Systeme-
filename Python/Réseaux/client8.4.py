# client8.4.py
import socket
import os

HOST = '127.0.0.1'
PORT = 12347

# Chemin vers le répertoire client
rep_client = "/chemin/vers/le/repertoire/client"
archive = "/tmp/rep.tgz"

# Créer une archive tar.gz du répertoire
os.system(f"tar zcvf {archive} {rep_client}")

# Envoyer l'archive au serveur
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    with open(archive, "rb") as f:
        data = f.read()
        s.sendall(data)

print("Archive envoyée !")