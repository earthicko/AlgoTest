#include <stdio.h>
#define N_MAX 101

__uint128_t NCR[N_MAX][N_MAX];
int N, M;

__uint128_t combination(int n, int r);

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= N; j++) NCR[i][j] = -1;
    __uint128_t ncm = combination(N, M);
    char result[100];
    int digits = 0;
    while (ncm > 0) {
        result[digits++] = (ncm % 10) + '0';
        ncm /= 10;
    }
    for (int i = digits - 1; i >= 0; i--) printf("%c", result[i]);
    printf("\n");

    // for (int i = 0; i < N_MAX; i++)
    //     for (int j = 0; j < N_MAX; j++) NCR[i][j] = -1;

    // for (int n = 0; n < N_MAX; n++) {
    //     for (int r = 0; r <= n / 2; r++) {
    //         __uint128_t ncr = combination(n, r);
    //         printf("%dC%d = ", n, r);
    //         char result[100];
    //         int digits = 0;
    //         while (ncr > 0) {
    //             result[digits++] = (ncr % 10) + '0';
    //             ncr /= 10;
    //         }
    //         for (int i = digits - 1; i >= 0; i--) printf("%c", result[i]);
    //         printf(", ");
    //     }
    //     printf("\n");
    // }
    return 0;
}

__uint128_t combination(int n, int r) {
    if (NCR[n][r] != -1) return NCR[n][r];
    if (r == 0 || r == n) {
        NCR[n][r] = 1;
        return NCR[n][r];
    }
    NCR[n][r] = combination(n - 1, r - 1) + combination(n - 1, r);
    return NCR[n][r];
}