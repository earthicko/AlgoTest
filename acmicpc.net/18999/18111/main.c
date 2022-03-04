#include <stdio.h>

int main() {
    int h[500][500];
    int N, M, B;
    int n_blocks = 0;
    scanf("%d %d %d", &N, &M, &B);
    for (int n = 0; n < N; n++) {
        for (int m = 0; m < M; m++) {
            scanf("%d", &(h[n][m]));
            n_blocks += h[n][m];
        }
    }

    int min_time = __INT32_MAX__, max_h = 0;

    for (int target_h = 256; target_h >= 0; target_h--) {
        int put = 0, get = 0;
        for (int n = 0; n < N; n++) {
            for (int m = 0; m < M; m++) {
                if (h[n][m] < target_h)
                    put += (target_h - h[n][m]);
                else if (h[n][m] > target_h)
                    get += (h[n][m] - target_h);
            }
        }
        if (put - get > B) continue;

        int time = put + 2 * get;
        if (time < min_time) {
            min_time = time;
            max_h = target_h;
        }
    }

    printf("%d %d\n", min_time, max_h);
    return 0;
}