#include <stdio.h>
#include <stdlib.h>
#define P_MAX 40320  // 40320

typedef struct list {
    int arr[8];
    // int n;
} list;

int N, M;
int numbers[8];
list permutations[P_MAX];
int n_permutations;

int cmp(const void *a, const void *b);
int cmp_list(const void *a, const void *b);
int combination(int pick_n, int picked_bit, list picked_list);

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) scanf("%d", &numbers[i]);
    qsort(numbers, N, sizeof(int), cmp);
    list empty;
    combination(M, 0, empty);
    qsort(permutations, n_permutations, sizeof(list), cmp_list);
    list prev;
    for (int i = 0; i < n_permutations; i++) {
        int dup = 1;
        for (int j = 0; j < M; j++) {
            if (prev.arr[j] != permutations[i].arr[j]) {
                dup = 0;
                break;
            }
        }
        if (dup) continue;
        for (int j = 0; j < M; j++) {
            prev.arr[j] = permutations[i].arr[j];
            printf("%d ", permutations[i].arr[j]);
        }
        printf("\n");
    }

    return 0;
}

int combination(int pick_n, int picked_bit, list picked_list) {
    if (pick_n == 0) {
        permutations[n_permutations++] = picked_list;
        return 0;
    }
    for (int i = 0; i < N; i++) {
        if (picked_bit & (1 << i)) continue;
        int new_picked_bit = picked_bit | (1 << i);
        picked_list.arr[M - pick_n] = numbers[i];
        combination(pick_n - 1, new_picked_bit, picked_list);
    }
    return 0;
}

int cmp(const void *a, const void *b) {
    if (*(int *)a > *(int *)b) return 1;
    if (*(int *)a < *(int *)b) return -1;
    return 0;
}

int cmp_list(const void *a, const void *b) {
    for (int i = 0; i < M; i++) {
        if (((list *)a)->arr[i] > ((list *)b)->arr[i]) return 1;
        if (((list *)a)->arr[i] < ((list *)b)->arr[i]) return -1;
    }
    return 0;
}