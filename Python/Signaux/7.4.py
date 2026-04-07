
n = int(input("Nombre d'éléments : "))
tab = [int(input(f"tab[{i}] = ")) for i in range(n)]

while True:
    i = int(input("Index à afficher : "))
    if 0 <= i < n:
        print(f"tab[{i}] = {tab[i]}")
        break
    else:
        print("Erreur : index invalide !")