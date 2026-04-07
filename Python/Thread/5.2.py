import threading
import random

TAILLE = 5

def generer_tableau(result):
    tab = [random.randint(0, 99) for _ in range(TAILLE)]
    result.append(tab)  # On retourne le tableau via une liste partagée

# Liste partagée pour récupérer le résultat
result = []

thread = threading.Thread(target=generer_tableau, args=(result,))
thread.start()
thread.join()  # On attend que le thread finisse

print("Tableau généré par le thread :", result[0])