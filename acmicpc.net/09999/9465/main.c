#include <stdio.h>
#define max(a, b)               \
    ({                          \
        __typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        _a > _b ? _a : _b;      \
    })
#define N_MAX 100000
int SCORE[N_MAX][2];
int MAX_SCORE[N_MAX][2];
int main() {
    int T;
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        int N;
        scanf("%d", &N);
        for (int i = 0; i < N; i++) scanf("%d", &SCORE[i][0]);
        for (int i = 0; i < N; i++) scanf("%d", &SCORE[i][1]);
        MAX_SCORE[0][0] = SCORE[0][0];
        MAX_SCORE[0][1] = SCORE[0][1];
        MAX_SCORE[1][0] = SCORE[0][1] + SCORE[1][0];
        MAX_SCORE[1][1] = SCORE[0][0] + SCORE[1][1];
        for (int i = 2; i < N; i++) {
            int max_2 = max(MAX_SCORE[i - 2][0], MAX_SCORE[i - 2][1]);
            MAX_SCORE[i][0] = max(max_2, MAX_SCORE[i - 1][1]) + SCORE[i][0];
            MAX_SCORE[i][1] = max(max_2, MAX_SCORE[i - 1][0]) + SCORE[i][1];
        }
        printf("%d\n", max(MAX_SCORE[N - 1][0], MAX_SCORE[N - 1][1]));
    }
    return 0;
}