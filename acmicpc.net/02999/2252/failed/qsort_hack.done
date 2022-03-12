#include <stdio.h>
#include <stdlib.h>
#define N_MAX 32001
#define M_MAX 100000
typedef struct order {
    int a, b;
} order;
int N, M;
int NUM[N_MAX];
order CMP[M_MAX];
int cmp_int(const void* a, const void* b);
int cmp_order(const void* a, const void* b);
int main() {
    scanf("%d %d", &N, &M);
    for (int m = 0; m < M; m++) scanf("%d %d", &(CMP[m].a), &(CMP[m].b));
    qsort(CMP, M, sizeof(order), cmp_order);
    for (int n = 0; n < N; n++) NUM[n] = n + 1;
    qsort(NUM, N, sizeof(int), cmp_int);
    for (int i = 0; i < N; i++) printf("%d ", NUM[i]);
    return 0;
}
int cmp_int(const void* a, const void* b) {
    order t;
    int* res;
    t.a = *(int*)a;
    t.b = *(int*)b;
    res = bsearch(&t, CMP, M, sizeof(order), cmp_order);
    if (res) return -1;
    t.a = *(int*)b;
    t.b = *(int*)a;
    res = bsearch(&t, CMP, M, sizeof(order), cmp_order);
    if (res) return 1;
    return 0;
}
int cmp_order(const void* a, const void* b) {
    if (((order*)a)->a > ((order*)b)->a) return 1;
    if (((order*)a)->a < ((order*)b)->a) return -1;
    if (((order*)a)->b > ((order*)b)->b) return 1;
    if (((order*)a)->b < ((order*)b)->b) return -1;
    return 0;
}