#include <stdio.h>

int N, M;

int combination(int n, int c, int prev);

int main() {
    scanf("%d %d", &N, &M);
    combination(0, M, 0);
    return 0;
}

int combination(int n, int c, int prev) {
    if (c == 0) {
        char c[8];
        int digits = 0;
        while (prev > 0) {
            c[digits++] = prev % 10 + '0';
            prev /= 10;
        }
        for (int i = digits - 1; i >= 0; i--) printf("%c ", c[i]);
        printf("\n");
        return 0;
    }
    for (int i = n + 1; i <= N; i++) {
        combination(i, c - 1, prev * 10 + i);
    }
    return 0;
}