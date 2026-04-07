import threading
import time
import random

sem1 = threading.Semaphore(0)
sem2 = threading.Semaphore(0)

def T1():
    for i in range(10):
        print(f"T1 : traitement iteration {i+1}")
        time.sleep(2)
        sem1.release()  # signal T1 fini
        sem2.acquire()  # attend T2

def T2():
    for i in range(10):
        sem1.acquire()  # attend T1
        t = random.randint(4,9)
        print(f"T2 : traitement iteration {i+1} pendant {t} sec")
        time.sleep(t)
        sem2.release()  # signal T2 fini

t1 = threading.Thread(target=T1)
t2 = threading.Thread(target=T2)

t1.start()
t2.start()

t1.join()
t2.join()