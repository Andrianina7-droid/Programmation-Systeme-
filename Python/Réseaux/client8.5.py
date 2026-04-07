import socket
import threading

PORT = 12348
BUFFER = 1024

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('127.0.0.1', PORT))

def recv_thread():
    while True:
        data = s.recv(BUFFER)
        if data:
            print("L'autre client dit :", data.decode())

threading.Thread(target=recv_thread, daemon=True).start()

while True:
    msg = input("Saisissez votre message : ")
    s.send(msg.encode())