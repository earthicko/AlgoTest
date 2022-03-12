#include <stdio.h>

int main() {
    while (1) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        if (!a && !b && !c) break;
        if (a > b && a > c && a * a == b * b + c * c)
            printf("right\n");
        else if (b > a && b > c && b * b == a * a + c * c)
            printf("right\n");
        else if (c > a && c > b && c * c == a * a + b * b)
            printf("right\n");
        else
            printf("wrong\n");
    }
    return 0;
}