#include <stdio.h>
#define N_MAX 1025

int TABLE[N_MAX][N_MAX];
int SUM_TABLE[N_MAX][N_MAX];
int SUM_ROW[N_MAX][N_MAX];
int N, M;
int main() {
    scanf("%d %d", &N, &M);
    for (int r = 1; r <= N; r++)
        for (int c = 1; c <= N; c++) {
            scanf("%d", &TABLE[r][c]);
            SUM_ROW[r][c] = SUM_ROW[r][c - 1] + TABLE[r][c];
        }
    for (int r = 1; r <= N; r++)
        for (int c = 1; c <= N; c++)
            SUM_TABLE[r][c] = SUM_TABLE[r - 1][c] + SUM_ROW[r][c];
    for (int m = 0; m < M; m++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        x1--;
        y1--;
        int x2y2 = SUM_TABLE[x2][y2];
        int x1y2 = SUM_TABLE[x1][y2];
        int x2y1 = SUM_TABLE[x2][y1];
        int x1y1 = SUM_TABLE[x1][y1];
        printf("%d\n", x2y2 - x1y2 - x2y1 + x1y1);
    }
    return 0;
}