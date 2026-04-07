import os

while True:
    filename = input("Nom du fichier (ou 'quit' pour sortir) : ")
    if filename.lower() == "quit":
        break
    os.system(f"/usr/bin/emacs {filename}")