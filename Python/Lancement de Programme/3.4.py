import shutil
import os

while True:
    dirname = input("Nom du répertoire (ou 'quit' pour sortir) : ")
    if dirname.lower() == "quit":
        break
    shutil.copytree(os.getcwd(), dirname, dirs_exist_ok=True) # shutil.copytree = cp -r 