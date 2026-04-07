n = int(input("n = "))
k = int(input("k = "))

if k == 0 or k == n:
    print(f"C({n},{k}) = 1")
else:
    result = 1
    for i in range(1, k+1):
        result = result * (n - i + 1) // i
    print(f"C({n},{k}) = {result}")