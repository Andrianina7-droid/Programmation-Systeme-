import os   # pour parcourir les dossiers et fichiers
import sys  # pour récupérer les arguments

# Vérifier que l'utilisateur fournit un répertoire
if len(sys.argv) != 2:
    print(f"Usage : {sys.argv[0]} <répertoire>")
    sys.exit(1)

dossier = sys.argv[1]

# Parcourir tous les fichiers du répertoire
for nom_fichier in os.listdir(dossier):
    chemin_complet = os.path.join(dossier, nom_fichier)  # chemin complet
    
    # Vérifier que c'est bien un fichier (ignorer les dossiers)
    if os.path.isfile(chemin_complet):
        taille = os.path.getsize(chemin_complet)  # taille en octets
        uid = os.stat(chemin_complet).st_uid     # propriétaire (UID)
        
        # Afficher uniquement les fichiers > 1 Mo
        if taille > 1024*1024:
            print(f"Fichier : {nom_fichier}, UID={uid}, taille={taille} octets")