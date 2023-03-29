#include <stdio.h>
#define N_MAX 1000
#define min(a, b)               \
    ({                          \
        __typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        _a < _b ? _a : _b;      \
    })

int COST[N_MAX][3];  // a번째 집을 b색으로 칠하는 비용
int N;
// 첫 집을 a색으로 칠했을때 b번째 집을 c색으로 칠하는 비용
int MIN_C[3][N_MAX][3];
int except[3][2] = {{1, 2}, {0, 2}, {0, 1}};

int main() {
    scanf("%d", &N);
    for (int n = 0; n < N; n++)
        scanf("%d %d %d", &COST[n][0], &COST[n][1], &COST[n][2]);
    for (int c = 0; c < 3; c++)
        for (int i = 0; i < 3; i++)
            MIN_C[c][0][i] = (c == i) ? COST[0][c] : __INT32_MAX__;
    for (int n = 1; n < N; n++) {
        for (int c = 0; c < 3; c++) {
            for (int n_c = 0; n_c < 3; n_c++) {
                MIN_C[c][n][n_c] = min(MIN_C[c][n - 1][except[n_c][0]],
                                       MIN_C[c][n - 1][except[n_c][1]]);
                if (MIN_C[c][n][n_c] != __INT32_MAX__)
                    MIN_C[c][n][n_c] += COST[n][n_c];
            }
        }
    }
    int min_cost = __INT32_MAX__;
    for (int s_c = 0; s_c < 3; s_c++) {
        min_cost = min(min_cost, MIN_C[s_c][N - 1][except[s_c][0]]);
        min_cost = min(min_cost, MIN_C[s_c][N - 1][except[s_c][1]]);
    }
    printf("%d", min_cost);
    return 0;
}