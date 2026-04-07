import os
import signal

# PID du programme affiche.py
pid_affiche = int(input("Entrez le PID du programme affiche.py : "))

# Saisie de l'entier
n = int(input("Entrez un entier : "))

# Écriture dans un fichier temporaire
with open("/tmp/entier.txt", "w") as f:
    f.write(str(n))

# Envoi du signal SIGUSR1 au programme affiche.py
os.kill(pid_affiche, signal.SIGUSR1)
print(f"Signal envoyé au processus {pid_affiche}")