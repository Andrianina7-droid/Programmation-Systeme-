import os
import signal
import time
import sys

N = 5  # Nombre de fils
pids = []  # Liste pour stocker les PID des fils

# Handler pour le signal SIGTERM dans le fils
def child_handler(sig, frame):
    print(f"Fils {os.getpid()} tué !")
    sys.exit(0)

# Création des processus fils
for i in range(N):
    pid = os.fork()
    if pid == 0:  # Code du fils
        signal.signal(signal.SIGTERM, child_handler)  # Attache le handler
        while True:
            time.sleep(1)  # Fils "travaille", mais pas en boucle CPU
    else:
        pids.append(pid)  # Stocke le PID du fils dans le père

# Menu interactif côté père
while True:
    print("Menu : 1=endormir, 2=réveiller, 3=terminer, 4=quit")
    choix = int(input("Choix : "))
    if choix == 4:
        break
    fils = int(input(f"Numéro du fils (0-{N-1}) : "))

    if choix == 1:
        os.kill(pids[fils], signal.SIGSTOP)  # Stop le fils
    elif choix == 2:
        os.kill(pids[fils], signal.SIGCONT)  # Continue le fils
    elif choix == 3:
        os.kill(pids[fils], signal.SIGTERM)  # Termine le fils
