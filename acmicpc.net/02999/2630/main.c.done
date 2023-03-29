#include <stdio.h>
#define N_MAX 128

int MAP[N_MAX][N_MAX];
int N;
int pow_2[8] = {1, 2, 4, 8, 16, 32, 64, 128};
int blue_n, white_n;

int is_uniform(int x, int y, int n);
int do_quad_tree(int x, int y, int n);

int main() {
    scanf("%d", &N);
    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++) {
            char c;
            scanf(" %c", &c);
            MAP[x][y] = c - '0';
        }
    int pow = 0;
    for (int i = 0; i < 8; i++)
        if (pow_2[i] == N) {
            pow = i;
            break;
        }
    do_quad_tree(0, 0, pow);
    printf("%d\n%d", white_n, blue_n);
    return 0;
}

int is_uniform(int x_s, int y_s, int n) {
    int d = pow_2[n];
    for (int x = x_s; x < x_s + d; x++)
        for (int y = y_s; y < y_s + d; y++)
            if (MAP[x][y] != MAP[x_s][y_s]) return 0;
    return 1;
}

int do_quad_tree(int x_s, int y_s, int n) {
    if (is_uniform(x_s, y_s, n)) {
        if (MAP[x_s][y_s])
            blue_n++;
        else
            white_n++;
    } else {
        int d = pow_2[n - 1];
        do_quad_tree(x_s, y_s, n - 1);
        do_quad_tree(x_s + d, y_s, n - 1);
        do_quad_tree(x_s, y_s + d, n - 1);
        do_quad_tree(x_s + d, y_s + d, n - 1);
    }
    return 0;
}