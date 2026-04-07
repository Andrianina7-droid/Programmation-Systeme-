import socket
import sys

if len(sys.argv)!=2:
    print("Usage: python client.py <fichier_local>")
    sys.exit(1)

HOST = '127.0.0.1'
PORT = 12347

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    with open(sys.argv[1], "rb") as f:
        s.sendall(f.read())

print("Fichier envoyé avec succès.")