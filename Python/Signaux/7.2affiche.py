import signal
import time

def handler(sig, frame):
    # Signal reçu : lire le fichier et afficher la valeur
    with open("/tmp/entier.txt", "r") as f:
        n = int(f.read().strip())
    print(f"Valeur reçue : {n}")

# Associer le signal SIGUSR1 au handler
signal.signal(signal.SIGUSR1, handler)

print(f"PID de ce programme : {os.getpid()}")
print("En attente du signal...")

# Boucle infinie pour attendre le signal
while True:
    signal.pause()  # pause jusqu'à la réception d'un signal