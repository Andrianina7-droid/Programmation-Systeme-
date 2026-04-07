import shutil
import sys
import os

if len(sys.argv) != 2:
    print(f"Usage: {sys.argv[0]} chemin_cible")
    sys.exit(1)

chemin = sys.argv[1]
courant = os.getcwd()
shutil.copytree(courant, chemin, dirs_exist_ok=True)