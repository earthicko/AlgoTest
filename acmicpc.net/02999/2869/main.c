#include <stdio.h>

int main() {
    int a, b, v, d;
    scanf("%d %d %d", &a, &b, &v);
    d = a - b;
    if (v <= a) {
        printf("1");
        return 0;
    }
    if ((v - a) % d == 0) {
        printf("%d", (v - a) / d + 1);
    } else {
        double ans = (double)(v - a) / (double)d + 1;
        int ans_int = ans + 1;
        printf("%d", ans_int);
    }
    return 0;
}