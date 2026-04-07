import threading
import time
import random


SIZE = 15
data = [0] * SIZE
read_count = 0

mutex = threading.Lock()  # protège read_count
wrt = threading.Lock()    # accès exclusif pour écrivains

def reader(id):
    global read_count

    while True:
        # début section critique
        with mutex:
            read_count += 1
            if read_count == 1:
                wrt.acquire()  # premier lecteur bloque écrivains

        # lecture
        i = random.randint(0, SIZE-1)
        print(f"Lecteur {id} lit data[{i}] = {data[i]}")
        time.sleep(random.randint(1,3))

        # fin lecture
        with mutex:
            read_count -= 1
            if read_count == 0:
                wrt.release()  # dernier lecteur libère écrivains

def writer(id):
    while True:
        wrt.acquire()  # accès exclusif

        i = random.randint(0, SIZE-1)
        data[i] = random.randint(0, 100)
        print(f"Écrivain {id} écrit data[{i}] = {data[i]}")

        wrt.release()
        time.sleep(random.randint(1,5))

N = 3  # lecteurs
M = 2  # écrivains

for i in range(N):
    threading.Thread(target=reader, args=(i,), daemon=True).start()

for i in range(M):
    threading.Thread(target=writer, args=(i,), daemon=True).start()

while True:
    time.sleep(1)