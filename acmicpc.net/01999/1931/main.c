#include <stdio.h>
#include <stdlib.h>
#define N_MAX 100000

typedef struct pair {
    int s, e;
} pair;

int N;
pair time[N_MAX];

int cmp_last(const void *a, const void *b);

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) scanf("%d %d", &time[i].s, &time[i].e);
    qsort(time, N, sizeof(pair), cmp_last);

    int count = 1;
    int last = time[0].e;
    for (int i = 1; i < N; i++) {
        // printf("===========Last: %d, count: %d\n", last, count);
        // printf("this: %d to %d\n", time[i].s, time[i].e);
        if (time[i].s < last) {
            // printf("Can't fit %d to %d\n", time[i].s, time[i].e);
            continue;
        }
        last = time[i].e;
        count++;

        // printf("Last to %d count to %d\n", last, count);
    }
    printf("%d\n", count);

    return 0;
}

int cmp_last(const void *a, const void *b) {
    if (((pair *)a)->e < ((pair *)b)->e) return -1;
    if (((pair *)a)->e > ((pair *)b)->e) return 1;
    if (((pair *)a)->s < ((pair *)b)->s) return -1;
    if (((pair *)a)->s > ((pair *)b)->s) return 1;
    return 0;
}