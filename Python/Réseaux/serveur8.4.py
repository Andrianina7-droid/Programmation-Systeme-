# serveur8.4.py
import socket
import os

HOST = '0.0.0.0'
PORT = 12347
rep_serveur = "/chemin/vers/le/repertoire/serveur"

os.makedirs(rep_serveur, exist_ok=True)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print(f"Serveur en écoute sur {PORT}...")

    conn, addr = s.accept()
    with conn:
        print(f"Client connecté : {addr[0]}")
        # Sauvegarder archive reçue
        archive = os.path.join(rep_serveur, "rep.tgz")
        with open(archive, "wb") as f:
            while True:
                data = conn.recv(4096)
                if not data:
                    break
                f.write(data)

        # Décompresser l'archive et supprimer le fichier
        os.system(f"cd {rep_serveur} && tar zxvf rep.tgz && rm rep.tgz")
        print("Archive décompressée sur le serveur.")