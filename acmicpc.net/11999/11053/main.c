#include <stdio.h>
#define N_MAX 1001
#define INF __INT32_MAX__

int N;
int A[N_MAX];
int D[N_MAX];
int L[N_MAX];

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
    for (int i = 1; i <= N; i++) L[i] = INF;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (L[j - 1] < A[i] && A[i] < L[j]) {
                L[j] = A[i];
                D[i] = j;
                break;
            }
        }
    }
    int max = 0;
    for (int i = 1; i <= N; i++)
        if (max < D[i]) max = D[i];
    printf("%d\n", max);

    return 0;
}