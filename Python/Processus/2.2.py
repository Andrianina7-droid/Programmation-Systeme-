import os

pid1 = os.fork() # creation d'un processus 

if pid1 == 0: 
    print("Je suis le fils 1")
else: 
    pid2 = os.fork()
    if pid2 == 0:
        print("Je suis le fils 2")
    else : 
        print("Je suis le père")


       
    