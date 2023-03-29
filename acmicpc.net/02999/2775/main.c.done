#include <stdio.h>

int people[15][15];
int main() {
    int T, K, N;
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        scanf("%d%d", &K, &N);
        for (int n = 1; n <= N; n++) people[0][n] = n;
        for (int k = 1; k <= K; k++) {
            for (int n = 1; n <= N; n++) {
                people[k][n] = 0;
                for (int i = 1; i <= n; i++) people[k][n] += people[k - 1][i];
            }
        }
        printf("%d\n", people[K][N]);
    }
    return 0;
}