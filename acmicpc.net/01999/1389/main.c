#include <stdio.h>
#define N_MAX 100
int N, M;
int D_MIN[N_MAX][N_MAX];
int KEVIN[N_MAX];

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) D_MIN[i][j] = __INT32_MAX__;
    for (int i = 0; i < N; i++) D_MIN[i][i] = 0;
    for (int m = 0; m < M; m++) {
        int s, e;
        scanf("%d %d", &s, &e);
        D_MIN[s - 1][e - 1] = 1;
        D_MIN[e - 1][s - 1] = 1;
    }

    for (int m = 0; m < N; m++)
        for (int s = 0; s < N; s++)
            for (int e = 0; e < N; e++) {
                if (D_MIN[s][m] == __INT32_MAX__ ||
                    D_MIN[m][e] == __INT32_MAX__)
                    continue;
                if (D_MIN[s][e] > D_MIN[s][m] + D_MIN[m][e])
                    D_MIN[s][e] = D_MIN[s][m] + D_MIN[m][e];
            }
    for (int n = 0; n < N; n++) {
        for (int m = 0; m < N; m++) {
            if (n == m) continue;
            KEVIN[n] += D_MIN[n][m];
        }
    }
    int min_i = 0;
    int min_kevin = __INT32_MAX__;
    for (int i = 0; i < N; i++)
        if (min_kevin > KEVIN[i]) {
            min_kevin = KEVIN[i];
            min_i = i;
        }
    printf("%d\n", min_i + 1);
    return 0;
}