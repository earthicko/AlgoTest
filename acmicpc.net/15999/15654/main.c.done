#include <stdio.h>
#include <stdlib.h>

int N, M;
int numbers[8];

int cmp(const void *a, const void *b);
int combination(int pick_n, int picked_bit, int picked_list);

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) scanf("%d", &numbers[i]);
    qsort(numbers, N, sizeof(int), cmp);
    combination(M, 0, 0);
    return 0;
}

int combination(int pick_n, int picked_bit, int picked_list) {
    if (pick_n == 0) {
        int idx[8];
        int digit = 0;
        while (picked_list > 0) {
            idx[digit++] = picked_list % 10;
            picked_list /= 10;
        }
        for (int i = digit - 1; i >= 0; i--) printf("%d ", numbers[idx[i] - 1]);
        printf("\n");

        // printf("%d\n", picked_list);

        return 0;
    }
    for (int i = 1; i <= N; i++) {
        if (picked_bit & (1 << i)) continue;
        int new_picked_bit = picked_bit | (1 << i);
        combination(pick_n - 1, new_picked_bit, picked_list * 10 + i);
    }
    return 0;
}

int cmp(const void *a, const void *b) {
    if (*(int *)a < *(int *)b) return -1;
    if (*(int *)a > *(int *)b) return 1;
    return 0;
}