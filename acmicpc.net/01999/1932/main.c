#include <stdio.h>
#define N_MAX 500
#define max(a, b)               \
    ({                          \
        __typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        _a > _b ? _a : _b;      \
    })
int MAX_SCORE[N_MAX][N_MAX];
int N;
int main() {
    scanf("%d", &N);
    scanf("%d", &MAX_SCORE[0][0]);
    for (int i = 1; i < N; i++)
        for (int j = 0; j <= i; j++) {
            if (j == 0)
                MAX_SCORE[i][j] = MAX_SCORE[i - 1][j];
            else if (j == i)
                MAX_SCORE[i][j] = MAX_SCORE[i - 1][j - 1];
            else
                MAX_SCORE[i][j] =
                    max(MAX_SCORE[i - 1][j - 1], MAX_SCORE[i - 1][j]);
            int a;
            scanf("%d", &a);
            MAX_SCORE[i][j] += a;
        }

    int max = 0;
    for (int i = 0; i < N; i++) max = max(MAX_SCORE[N - 1][i], max);
    printf("%d", max);
    return 0;
}