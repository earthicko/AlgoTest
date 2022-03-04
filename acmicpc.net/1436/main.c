#include <stdio.h>

int has_666(int input);

int main() {
    int N;
    scanf("%d", &N);
    int tested = 666;
    for (int i = 0; i < N; i++) {
        while (!has_666(tested)) tested++;
        // printf("%dth 666: %d\n", i, tested);
        tested++;
    }
    printf("%d\n", --tested);
    return 0;
}

int has_666(int input) {
    while (input > 0) {
        if (input % 1000 == 666) return 1;
        input /= 10;
    }
    return 0;
}