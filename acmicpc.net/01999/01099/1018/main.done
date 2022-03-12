/*
8 <= N, M <= 50 -> 9, 43 * 43개 경우의 수
*/

#include <stdio.h>

int N, M;
char MAP[50][50];

int get_repainted_blocks(int x, int y, char start);

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) scanf(" %c", &(MAP[i][j]));
    }
    // N = 8 -> n: [0 1) N = 10 -> n: [0 2)
    int min = 250;
    for (int i = 0; i < N - 7; i++) {
        for (int j = 0; j < M - 7; j++) {
            int min_w = get_repainted_blocks(i, j, 'W');
            int min_b = get_repainted_blocks(i, j, 'B');
            if (min > min_w) min = min_w;
            if (min > min_b) min = min_b;
        }
    }
    printf("%d", min);
}

int get_repainted_blocks(int x, int y, char start) {
    char wb[2] = {start};
    if (start == 'W') wb[1] = 'B';
    if (start == 'B') wb[1] = 'W';
    int result = 0;
    int shifter = 0;
    for (int i = x; i < x + 8; i++) {
        for (int j = y; j < y + 8; j++) {
            if (MAP[i][j] != wb[shifter]) result++;
            shifter ^= 1;
        }
        shifter ^= 1;
    }
    return result;
}