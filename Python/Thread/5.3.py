import threading
import random

class TypeTableau:
    def __init__(self, taille, x):
        self.tab = []
        self.taille = taille
        self.x = x

def generer_tableau(t):
    t.tab = [random.randint(0, 99) for _ in range(t.taille)]

def chercher_x(t):
    if t.x in t.tab:
        print(f"Résultat : x est dans le tableau")
    else:
        print(f"Résultat : x n'est pas dans le tableau")

# Lecture utilisateur
taille = int(input("Saisir la taille du tableau : "))
x = int(input("Saisir la valeur à chercher x : "))

t = TypeTableau(taille, x)

# Création et lancement du thread de génération
thread_gen = threading.Thread(target=generer_tableau, args=(t,))
thread_gen.start()
thread_gen.join()  # attendre que le tableau soit généré

# Création et lancement du thread de recherche
thread_cherche = threading.Thread(target=chercher_x, args=(t,))
thread_cherche.start()
thread_cherche.join()