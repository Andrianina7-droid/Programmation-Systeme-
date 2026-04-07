import socket

# Charger IP autorisées et noms
clients = {}
with open("add_autoris.txt") as f:
    for ligne in f:
        ip, nom = ligne.strip().split()
        clients[ip] = nom

HOST = '0.0.0.0'
PORT = 12346

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print(f"Serveur en écoute sur {PORT}")
    conn, addr = s.accept()
    with conn:
        ip_client = addr[0]
        if ip_client in clients:
            msg = f"Bienvenue {clients[ip_client]} !\n"
            conn.sendall(msg.encode())
            print(f"Client {ip_client} connecté et autorisé")
        else:
            msg = "Vous n'êtes pas autorisé !\n"
            conn.sendall(msg.encode())
            print(f"Client {ip_client} refusé")
            conn.close()