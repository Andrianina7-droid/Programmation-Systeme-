import os
import sys

# Création d'un pipe
r, w = os.pipe()

pid = os.fork()  # Création du fils

if pid == 0:
    os.close(w)  # on ferme l'écriture dans le fils
    os.dup2(r, 0)  # redirection stdin du fils vers lecture du pipe
    os.close(r)  # plus nécessaire après dup2

    # Lecture depuis stdin (qui vient du père)
    mot = input("Fils lit depuis stdin : ")
    print(f"Fils : mot reçu = {mot}")
else:
    os.close(r)  # on ferme la lecture dans le père

    mot = input("Père : entrez un mot à envoyer au fils : ")
    os.write(w, mot.encode())  # envoi du mot au fils
    os.close(w)  # fermeture après écriture

    os.wait()  # attendre la fin du fils