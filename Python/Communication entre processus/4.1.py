import os

# Création des deux pipes
p1_r, p1_w = os.pipe()   # Fils -> Père
p2_r, p2_w = os.pipe()   # Père -> Fils

pid = os.fork()

if pid == 0:
    word = input("Entrez un mot : ")

    # Envoi du mot au père
    os.write(p1_w, word.encode())

    # Lecture du résultat du père
    result = os.read(p2_r, 10).decode()

    print("Résultat :", result)

    os._exit(0)

else:

    # Lecture du mot envoyé par le fils
    word = os.read(p1_r, 100).decode()

    found = 0

    try:
        with open("file.txt", "r") as f:
            for line in f.read().split():
                if line == word:
                    found = 1
                    break
    except:
        print("Erreur ouverture fichier")
        os._exit(1)

    # Envoi du résultat au fils
    os.write(p2_w, str(found).encode())

    os.wait()