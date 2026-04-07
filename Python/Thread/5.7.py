import threading, time, random

u = 1
compteur = 0
mutex = threading.Lock()

def f1():
    global u, compteur
    while compteur < 10:
        with mutex:
            compteur += 1
            u = (u-1)**2/4
            print(f"T1 -> u={u:.2f}, compteur={compteur}")
        time.sleep(random.randint(1,5))

def f2():
    global u, compteur
    while compteur < 10:
        with mutex:
            compteur += 1
            u = (u-2)**2/6
            print(f"T2 -> u={u:.2f}, compteur={compteur}")
        time.sleep(random.randint(1,5))

t1 = threading.Thread(target=f1)
t2 = threading.Thread(target=f2)

t1.start()
t2.start()

t1.join()
t2.join()