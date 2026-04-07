import socket
import threading

PORT = 12348
BUFFER = 1024

clients = []
pairs = {}
lock = threading.Lock()

def handle_client(conn, idx):
    while True:
        try:
            data = conn.recv(BUFFER)
            if not data:
                break
            # envoyer au partenaire
            with lock:
                if idx in pairs:
                    partner = pairs[idx]
                    partner.sendall(data)
        except:
            break
    conn.close()
    with lock:
        if idx in pairs:
            del pairs[idx]
        clients[idx] = None
    print(f"Client {idx} déconnecté")

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('0.0.0.0', PORT))
s.listen()
print(f"Serveur en écoute sur {PORT}")

while True:
    conn, addr = s.accept()
    with lock:
        idx = len(clients)
        clients.append(conn)
        # Relier les paires
        for i, c in enumerate(clients[:-1]):
            if c is not None and i not in pairs:
                pairs[i] = conn
                pairs[idx] = c
                break
    threading.Thread(target=handle_client, args=(conn, idx)).start()