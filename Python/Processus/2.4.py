import os

num = 0
for i in range(5):
    pid = os.fork()
    if pid == 0:
        num = i+1
        print(f"Je suis le fils {num}")
        break 
    
