#include <stdio.h>

int is_generator(int tested, int target);

int main() {
    int n;
    scanf("%d", &n);

    int i = 1;
    while (i < n) {
        if (is_generator(i, n)) {
            printf("%d\n", i);
            break;
        }
        i++;
    }
    if (n == i) printf("0\n");
    return 0;
}

int is_generator(int tested, int target) {
    int temp = tested;
    while (temp > 0) {
        tested += temp % 10;
        temp /= 10;
    }
    if (tested == target)
        return 1;
    else
        return 0;
}