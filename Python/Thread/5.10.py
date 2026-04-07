import threading
import time
import random

BUFFER_SIZE = 10
buffer = []  # tampon partagé
mutex = threading.Lock()           # mutex pour protéger le buffer
full = threading.Semaphore(0)      # nombre d'éléments disponibles
empty = threading.Semaphore(BUFFER_SIZE)  # nombre de places libres


def producer(id):
    while True:
        item = random.randint(0, 255)      # produire un octet aléatoire
        empty.acquire()                     # attendre qu'il y ait une place libre
        with mutex:                         # début section critique
            buffer.append(item)             # ajouter l'élément
            print(f"Producteur {id} produit {item}, taille buffer={len(buffer)}")
        full.release()                      # signaler qu'un élément est disponible
        time.sleep(random.randint(1,3))     # pause aléatoire


def consumer(id):
    while True:
        full.acquire()                      # attendre qu'un élément soit disponible
        with mutex:                         # début section critique
            item = buffer.pop()             # retirer l'élément
            print(f"Consommateur {id} consomme {item}, taille buffer={len(buffer)}")
        empty.release()                     # signaler qu'une place est libre
        time.sleep(random.randint(1,3))     # pause aléatoire

N_PRODUCERS = 2
N_CONSUMERS = 2

# Création des threads producteurs
for i in range(N_PRODUCERS):
    t = threading.Thread(target=producer, args=(i,), daemon=True)
    t.start()

# Création des threads consommateurs
for i in range(N_CONSUMERS):
    t = threading.Thread(target=consumer, args=(i,), daemon=True)
    t.start()

# Garder le programme vivant
while True:
    time.sleep(1)