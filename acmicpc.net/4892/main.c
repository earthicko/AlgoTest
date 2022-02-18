#include <stdio.h>

int main() {
    int n0, n1, n2, n3, n4;
    int counter = 0;

    while (1) {
        scanf("%d", &n0);
        if (n0 == 0) break;

        counter++;

        printf("%d. ", counter);

        n1 = 3 * n0;
        if (n1 % 2 == 0) {
            n2 = n1 / 2;
            printf("even ");
        } else {
            n2 = (n1 + 1) / 2;
            printf("odd ");
        }
        n3 = 3 * n2;
        n4 = n3 / 9;
        printf("%d\n", n4);
    }
    return 0;
}