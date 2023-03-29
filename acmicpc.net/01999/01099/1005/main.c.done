#include <stdio.h>
#define N_MAX 1000
#define max(a, b)               \
    ({                          \
        __typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        _a > _b ? _a : _b;      \
    })

int T, N, K, W;
int D[N_MAX];
int E[N_MAX][N_MAX];
int MAX_T[N_MAX];

int get_max_time(int u);

int main() {
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        scanf("%d %d", &N, &K);
        for (int n = 0; n < N; n++) {
            scanf("%d", &D[n]);
            MAX_T[n] = -1;
            for (int j = 0; j < N; j++) E[n][j] = 0;
        }

        for (int k = 0; k < K; k++) {
            int s, e;
            scanf("%d %d", &s, &e);
            E[s - 1][e - 1] = 1;
        }
        scanf("%d", &W);
        printf("%d\n", get_max_time(W - 1));
    }
}

int get_max_time(int u) {
    if (MAX_T[u] != -1) return MAX_T[u];
    MAX_T[u] = 0;
    for (int s = 0; s < N; s++) {
        if (E[s][u]) MAX_T[u] = max(MAX_T[u], get_max_time(s));
    }
    MAX_T[u] += D[u];
    return MAX_T[u];
}