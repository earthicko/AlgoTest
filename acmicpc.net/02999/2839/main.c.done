#include <stdio.h>
int main() {
    int n, a, b;
    scanf("%d", &n);
    a = n / 5;
    while (a >= 0) {
        if ((n - 5 * a) % 3 == 0) {
            b = (n - 5 * a) / 3;
            break;
        }
        a--;
    }
    if (a < 0)
        printf("-1\n");
    else
        printf("%d\n", a + b);
    return 0;
}