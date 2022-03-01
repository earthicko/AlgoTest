#include <stdio.h>
#include <stdlib.h>
#define N_MAX 100000

int N;
int A[N_MAX];
int M;

int static compare(const void* first, const void* second);

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) scanf("%d", A + i);
    qsort(A, N, sizeof(int), compare);

    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int m;
        scanf("%d", &m);

        int start = 0, end = N - 1;
        while (end - start >= 0) {
            int mid = (start + end) / 2;
            if (m == A[mid]) {
                printf("1\n");
                break;
            } else if (A[mid] < m) {
                start = mid + 1;
            } else if (m < A[mid]) {
                end = mid - 1;
            }
        }
        if (end - start < 0) printf("0\n");
    }

    return 0;
}

int static compare(const void* first, const void* second) {
    if (*(int*)first > *(int*)second)
        return 1;
    else if (*(int*)first < *(int*)second)
        return -1;
    else
        return 0;
}
