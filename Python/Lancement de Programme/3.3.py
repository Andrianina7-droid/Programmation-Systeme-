import os

filename = input("Entrer le nom du fichier à ouvrir : ")
os.system(f"/usr/bin/emacs {filename}")