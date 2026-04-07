# serveur_ip.py
import socket


# Charger les IP autorisées
def load_allowed_ips(filename):
    allowed = {}
    with open(filename, 'r') as f:
        for line in f:
            parts = line.strip().split()
            if len(parts) == 2:
                ip, name = parts
                allowed[ip] = name
    return allowed

host = '0.0.0.0'
port = 5001
allowed_ips = load_allowed_ips('add_autoris.txt')

# Création serveur TCP
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((host, port))
s.listen(5)
print(f"Serveur lancé sur {host}:{port}")

while True:
    client, addr = s.accept()
    ip_client = addr[0]
    print(f"Connexion de {ip_client}")

    if ip_client in allowed_ips:
        # Client autorisé
        name = allowed_ips[ip_client]
        client.send(f"Bienvenue {name} !\n".encode())
        print(f"Client {name} connecté")
    else:
        # Client refusé
        client.send("Accès refusé.\n")
        print(f"Client {ip_client} non autorisé")
        client.close()