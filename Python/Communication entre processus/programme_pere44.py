import os

r, w = os.pipe()

pid = os.fork()

if pid == 0:
    # mettre le fd dans variable d'environnement
    os.environ["FD"] = str(r)

    # lancer le programme fils
    os.execv("/usr/bin/python3", ["python3", "programme_fils44.py"])

else:
    msg = "Hello depuis le père"
    os.write(w, msg.encode())