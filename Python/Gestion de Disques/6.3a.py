import struct
import os

# Saisie du tableau
n = int(input("Nombre d'entiers : "))
tab = []
for i in range(n):
    x = int(input(f"Entier {i} : "))
    tab.append(x)

# Sauvegarde binaire
with open("tab.bin", "wb") as f:
    for x in tab:
        f.write(struct.pack('i', x))  # 'i' = entier 4 octets

# Modifier permissions : propriétaire par défaut, groupe écriture, autres lecture
os.chmod("tab.bin", 0o624)

print("Tableau sauvegardé dans tab.bin")