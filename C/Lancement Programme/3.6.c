#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, k;
    printf("n = "); scanf("%d", &n);
    printf("k = "); scanf("%d", &k);

    if(k == 0 || k == n) {
        printf("C(%d,%d) = 1\n", n, k);
        return 0;
    }

    int result = 1;
    for(int i = 1; i <= k; i++) {  // pas de récursion
        result = result * (n - i + 1) / i;
    }

    printf("C(%d,%d) = %d\n", n, k, result);
    return 0;
}