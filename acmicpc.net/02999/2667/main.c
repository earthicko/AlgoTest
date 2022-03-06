#include <stdio.h>
#include <stdlib.h>
#define N_MAX 25
#define ANS_MAX 350

int N;
int MAP[N_MAX][N_MAX];
// int VISITED[N_MAX][N_MAX];
int count, n_house[ANS_MAX];

int cmp(const void *a, const void *b);
int do_dfs(int x, int y);
// int do_dfs(int x, int y, int key);
int do_bfs(int x, int y);

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            // char c;
            // scanf(" %c", &c);
            // MAP[i][j] = c - '0';
            scanf("%1d", &MAP[i][j]);
        }

    // for (int x = 0; x < N; x++)
    //     for (int y = 0; y < N; y++)
    //         if (MAP[x][y] == 1) {
    //             count++;
    //             do_dfs(x, y, count + 1);
    //         }

    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
            if (MAP[x][y] == 1) {
                // do_dfs(x, y);
                do_bfs(x, y);
                count++;
            }

    // for (int x = 0; x < N; x++) {
    //     for (int y = 0; y < N; y++) {
    //         if (MAP[x][y] >= 2) n_house[MAP[x][y] - 2]++;
    //     }
    // }

    qsort(n_house, count, sizeof(int), cmp);
    printf("%d\n", count);
    for (int i = 0; i < count; i++) printf("%d\n", n_house[i]);
    return 0;
}

// int do_dfs(int x, int y, int key) {
//     int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
//
//     // VISITED[x][y] = 1;
//     MAP[x][y] = key;
//     for (int i = 0; i < 4; i++) {
//         int there_x = x + dir[i][0];
//         int there_y = y + dir[i][1];
//         if (there_x < 0 || there_x >= N || there_y < 0 || there_y >= N)
//             continue;
//         if (MAP[there_x][there_y] == 1) do_dfs(there_x, there_y, key);
//     }
//     return 0;
// }

// int do_dfs(int x, int y) {
//     int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
//     n_house[count]++;
//     MAP[x][y] = 0;
//     for (int i = 0; i < 4; i++) {
//         int there_x = x + dir[i][0];
//         int there_y = y + dir[i][1];
//         if (there_x < 0 || there_x >= N || there_y < 0 || there_y >= N)
//             continue;
//         if (MAP[there_x][there_y] == 0) continue;
//         do_dfs(there_x, there_y);
//     }
//     return 0;
// }

int do_bfs(int x, int y) {
    int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    int queue[1000][2];
    int front = 0, back = 1, n = 1;
    queue[1][0] = x, queue[1][1] = y;

    MAP[x][y] = 0;
    n_house[count]++;

    while (n > 0) {
        front = (front + 1) % 1000;
        n--;
        int here_x = queue[front][0], here_y = queue[front][1];
        for (int i = 0; i < 4; i++) {
            int there_x = here_x + dir[i][0];
            int there_y = here_y + dir[i][1];
            if (there_x < 0 || there_x >= N || there_y < 0 || there_y >= N)
                continue;
            if (MAP[there_x][there_y] == 0) continue;
            MAP[there_x][there_y] = 0;
            n_house[count]++;
            back = (back + 1) % 1000;
            n++;
            queue[back][0] = there_x;
            queue[back][1] = there_y;
        }
    }
    return 0;
}

int cmp(const void *a, const void *b) {
    if (*(int *)a < *(int *)b) return -1;
    if (*(int *)a > *(int *)b) return 1;
    return 0;
}