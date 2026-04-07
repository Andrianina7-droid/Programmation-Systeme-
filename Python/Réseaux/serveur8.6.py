import socket
import threading

PORT = 12349
BUFFER = 1024

clients = []
lock = threading.Lock()  # mutex pour gérer les clients et l'envoi

def broadcast(msg, sender):
    with lock:
        for c in clients:
            if c != sender:
                c.send(msg)

def handle_client(conn):
    while True:
        try:
            data = conn.recv(BUFFER)
            if not data:
                break
            msg = b"Client: " + data
            broadcast(msg, conn)
        except:
            break
    with lock:
        clients.remove(conn)
    conn.close()

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('0.0.0.0', PORT))
s.listen()
print(f"Serveur forum de chat en écoute sur {PORT}")

while True:
    conn, addr = s.accept()
    with lock:
        clients.append(conn)
    threading.Thread(target=handle_client, args=(conn,), daemon=True).start()