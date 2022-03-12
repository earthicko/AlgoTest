#include <stdio.h>

int fac(int n) {
    int output = 1;
    for (int i = 2; i <= n; i++) output *= i;
    return output;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    printf("%d\n", fac(n) / (fac(k) * fac(n - k)));
    return 0;
}