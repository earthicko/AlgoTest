#include <stdio.h>
#define N_MAX 1000
#define min(a, b)               \
    ({                          \
        __typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        _a < _b ? _a : _b;      \
    })

int MIN_COST[N_MAX][3];
int N;

int main() {
    scanf("%d", &N);
    scanf("%d %d %d", &MIN_COST[0][0], &MIN_COST[0][1], &MIN_COST[0][2]);
    for (int i = 1; i < N; i++) {
        int r, g, b;
        scanf("%d %d %d", &r, &g, &b);
        MIN_COST[i][0] = min(MIN_COST[i - 1][1], MIN_COST[i - 1][2]) + r;
        MIN_COST[i][1] = min(MIN_COST[i - 1][0], MIN_COST[i - 1][2]) + g;
        MIN_COST[i][2] = min(MIN_COST[i - 1][0], MIN_COST[i - 1][1]) + b;
    }
    int min = min(MIN_COST[N - 1][0], MIN_COST[N - 1][1]);
    min = min(min, MIN_COST[N - 1][2]);
    printf("%d", min);
    return 0;
}