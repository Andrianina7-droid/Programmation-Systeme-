import threading, time, random

N = 100
tableau = [random.randint(0,100) for _ in range(N)]
tableau[0] = tableau[-1] = 0

mutex = threading.Lock()

def calcul_moyenne():
    for i in range(1, N-1):
        with mutex:  # section critique
            tableau[i] = (tableau[i-1] + tableau[i] + tableau[i+1])/3
        time.sleep(random.randint(1,3))

def affichage():
    while True:
        with mutex:
            print(["%.2f"%x for x in tableau])
        time.sleep(4)

t1 = threading.Thread(target=calcul_moyenne)
t2 = threading.Thread(target=affichage)

t1.start()
t2.start()

t1.join()
t2.do_run = False  # On peut créer un flag pour stopper le thread si besoin
# t2.join() # Optionnel si on a un flag