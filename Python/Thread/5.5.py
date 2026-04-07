import threading
import time
import random
import sys

compt = 0
mutex = threading.Lock()  # Mutex pour protéger l'accès
limite = int(sys.argv[1])  # Valeur limite depuis ligne de commande

def incrementer():
    global compt
    while True:
        with mutex:  # Début section critique
            if compt >= limite:
                break
            compt += 1
        time.sleep(random.randint(1,5))  # Attend 1 à 5 secondes

def afficher():
    while True:
        with mutex:
            if compt >= limite:
                break
            print("Compteur =", compt)
        time.sleep(2)  # Affiche toutes les 2 secondes

# Création des threads
t_inc = threading.Thread(target=incrementer)
t_aff = threading.Thread(target=afficher)
t_inc.start()
t_aff.start()
t_inc.join()
t_aff.join()