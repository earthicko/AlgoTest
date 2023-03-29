#include <stdio.h>
#define N_MAX 2187

int N;
int pow_3[8] = {1, 3, 9, 27, 81, 243, 729, 2187};

int MAP[N_MAX][N_MAX];
int count[3];

int count_map(int x_s, int y_s, int n);

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) scanf("%d", &MAP[i][j]);
    int pow;
    for (int i = 0; i < 8; i++)
        if (pow_3[i] == N) {
            pow = i;
            break;
        }
    count_map(0, 0, pow);
    for (int i = 0; i < 3; i++) printf("%d\n", count[i]);
    return 0;
}

int count_map(int x_s, int y_s, int n) {
    int do_count = 1;
    int base = MAP[x_s][y_s];
    for (int x = x_s; x < x_s + pow_3[n]; x++) {
        for (int y = y_s; y < y_s + pow_3[n]; y++) {
            if (MAP[x][y] != base) {
                do_count = 0;
                break;
            }
        }
    }
    if (do_count) {
        int base = MAP[x_s][y_s];
        if (base == -1)
            count[0]++;
        else if (base == 0)
            count[1]++;
        else if (base == 1)
            count[2]++;
    } else {
        int s[3] = {0, pow_3[n - 1], 2 * pow_3[n - 1]};
        int d = pow_3[n - 1];

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                count_map(x_s + s[i], y_s + s[j], n - 1);
            }
        }
    }

    return 0;
}