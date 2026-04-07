import sys 

if len(sys.argv) == 3:
    a = int(sys.argv[1])
    b = int(sys.argv[2])

    s = a + b 
    print(f"{a} + {b} = {s}")

else :
    print(f"Usage : {sys.argv[0]} nombre1 nombre2")