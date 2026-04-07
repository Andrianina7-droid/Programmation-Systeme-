import threading
import time
import random

octet = None
ready = False
mutex = threading.Lock()
cond = threading.Condition(mutex)

def emetteur():
    global octet, ready
    for _ in range(10):
        time.sleep(random.randint(1,3))
        with cond:
            while ready:
                cond.wait()
            octet = random.randint(0,255)
            ready = True
            print(f"Émetteur : octet {octet} envoyé")
            cond.notify()

def recepteur():
    global octet, ready
    for _ in range(10):
        with cond:
            while not ready:
                cond.wait()
            print(f"Récepteur : octet {octet} reçu")
            ready = False
            cond.notify()

t1 = threading.Thread(target=emetteur)
t2 = threading.Thread(target=recepteur)

t1.start()
t2.start()
t1.join()
t2.join()