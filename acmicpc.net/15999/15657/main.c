#include <stdio.h>
#include <stdlib.h>

int N, M;
int numbers[8];

int cmp(const void *a, const void *b);
int combination(int n, int c, int prev);

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) scanf("%d", &numbers[i]);
    qsort(numbers, N, sizeof(int), cmp);
    combination(1, M, 0);
    return 0;
}

int combination(int n, int c, int prev) {
    if (c == 0) {
        int idx[8];
        int digits = 0;
        while (prev > 0) {
            idx[digits++] = (prev % 10) - 1;
            prev /= 10;
        }
        for (int i = digits - 1; i >= 0; i--) printf("%d ", numbers[idx[i]]);
        printf("\n");
        return 0;
    }
    for (int i = n; i <= N; i++) {
        combination(i, c - 1, prev * 10 + i);
    }
    return 0;
}
int cmp(const void *a, const void *b) {
    if (*(int *)a < *(int *)b) return -1;
    if (*(int *)a > *(int *)b) return 1;
    return 0;
}