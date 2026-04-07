import threading  # Pour créer des threads

# Fonction exécutée par le thread
def afficher_tableau(tab):
    print("Contenu du tableau :", tab)

# Programme principal
tableau = [1, 2, 3, 4, 5]

# Création du thread
thread = threading.Thread(target=afficher_tableau, args=(tableau,))

# Démarrage du thread
thread.start()

# Attente de la fin du thread
thread.join()

print("Thread terminé .")   