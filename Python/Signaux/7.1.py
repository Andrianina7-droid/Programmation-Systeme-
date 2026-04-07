import os
import signal
import time

pid = os.fork()

if pid == 0:
    # Fils : calcul infini
    x = 0
    while True:
        x += 1
else:
    # Père : menu
    while True:
        choix = input("Menu : s=stop, r=resume, q=quit\n")
        if choix == 's':
            os.kill(pid, signal.SIGSTOP)
        elif choix == 'r':
            os.kill(pid, signal.SIGCONT)
        elif choix == 'q':
            os.kill(pid, signal.SIGKILL)
            break