#include <stdio.h>
#define N_MAX 301

int N, SCORE[N_MAX];
int MAX_SCORE[2][N_MAX];

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%d", &SCORE[i]);
    MAX_SCORE[0][1] = SCORE[1];
    MAX_SCORE[0][2] = MAX_SCORE[0][1] + SCORE[2];
    MAX_SCORE[1][2] = SCORE[2];
    for (int i = 3; i <= N; i++) {
        if (i - 2 >= 0) {
            MAX_SCORE[1][i] = (MAX_SCORE[0][i - 2] < MAX_SCORE[1][i - 2])
                                  ? MAX_SCORE[1][i - 2]
                                  : MAX_SCORE[0][i - 2];
            MAX_SCORE[1][i] += SCORE[i];
        }
        if (i - 1 >= 0) {
            MAX_SCORE[0][i] = MAX_SCORE[1][i - 1] + SCORE[i];
        }
    }
    printf("%d", (MAX_SCORE[0][N] > MAX_SCORE[1][N]) ? MAX_SCORE[0][N]
                                                     : MAX_SCORE[1][N]);
    return 0;
}