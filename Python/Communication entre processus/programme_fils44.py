import os

# récupérer le fd depuis l'environnement
fd = int(os.environ["FD"])

# lire le message
msg = os.read(fd, 100).decode()

print("Message reçu :", msg)