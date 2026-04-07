import os

pid = os.fork() # creation d'un processus 

if pid == -1: 
    print("Erreur de creation de processus")
elif pid == 0:
    print("Je suis le fils")
else:
    print("Je suis le père")