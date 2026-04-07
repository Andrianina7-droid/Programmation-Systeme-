import os
import time
import random

# Début du programme
debut = int(time.time())

# Création du premier fils
pid_1 = os.fork()

if pid_1 == 0:
    # FILS 1
    random.seed(os.getpid())  # seed différent
    t = random.randint(1, 10)
    print(f"Fils 1 dort pendant {t} secondes")
    time.sleep(t)
    print("Fils 1 terminé")
    os._exit(0)  # IMPORTANT (équivalent de exit en C)

else:
    # PÈRE
    pid_2 = os.fork()

    if pid_2 == 0:
        # FILS 2
        random.seed(os.getpid())
        t = random.randint(1, 10)
        print(f"Fils 2 dort pendant {t} secondes")
        time.sleep(t)
        print("Fils 2 terminé")
        os._exit(0)

# Code exécuté par le PÈRE uniquement

os.wait()  # attendre un fils
os.wait()  # attendre le deuxième

fin = int(time.time())

print(f"Durée totale d'exécution : {fin - debut} secondes")