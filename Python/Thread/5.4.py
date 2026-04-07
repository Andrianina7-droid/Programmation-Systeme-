import threading
import random

T1 = []
T2 = []
annule = False

def generer_tableau(tab, taille):
    for _ in range(taille):
        tab.append(random.randint(0,99))

def inclusion():
    if annule:
        print("Programme annulé par l'utilisateur")
        return
    for elem in T1:
        if elem not in T2:
            print("T1 n'est pas inclus dans T2")
            return
    print("T1 est inclus dans T2")

def surveiller_annulation():
    global annule
    c = input("Appuyez sur A pour annuler : ")
    if c.upper() == 'A':
        annule = True

# Création et lancement des threads de génération
t1_gen = threading.Thread(target=generer_tableau, args=(T1,5))
t2_gen = threading.Thread(target=generer_tableau, args=(T2,10))
t1_gen.start()
t2_gen.start()
t1_gen.join()
t2_gen.join()

# Lancement des threads de vérification et d'annulation
t_incl = threading.Thread(target=inclusion)
t_ann = threading.Thread(target=surveiller_annulation)
t_incl.start()
t_ann.start()
t_incl.join()
t_ann.join()