import struct
import os

tab = []

with open("tab.bin", "rb") as f:
    while True:
        bytes_read = f.read(4)  # lire 4 octets (int)
        if not bytes_read:
            break
        x = struct.unpack('i', bytes_read)[0]
        tab.append(x)

print(f"Tableau chargé ({len(tab)} entiers) : {tab}")