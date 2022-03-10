#include <stdio.h>
#define SIZE_MAX 20
int R, C;
char MAP[SIZE_MAX][SIZE_MAX];
int VISITED[SIZE_MAX][SIZE_MAX];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int max_steps = 0;
int do_dfs(int r, int c, int steps, int visited_bits);
int main() {
    scanf("%d %d", &R, &C);
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++) scanf(" %c", &MAP[r][c]);
    do_dfs(0, 0, 0, 0);
    printf("%d", max_steps);
    return 0;
}
int do_dfs(int r, int c, int steps, int visited_bits) {
    // if (VISITED[r][c]) return -1;
    // VISITED[r][c] = 1;
    int char_idx = MAP[r][c] - 'A';
    // printf("Visited %d, %d, char is %c, visited bit %d\n", r, c, MAP[r][c], visited_bits);
    if (visited_bits & (1 << char_idx)) return -2;
    visited_bits = visited_bits | (1 << char_idx);
    steps++;
    if (max_steps < steps) max_steps = steps;
    for (int i = 0; i < 4; i++) {
        int n_r = r + dir[i][0];
        int n_c = c + dir[i][1];
        if (0 <= n_r && n_r < R && 0 <= n_c && n_c < C)
            do_dfs(n_r, n_c, steps, visited_bits);
    }
}