#include <stdio.h>
#define N_MAX 1000001
#define INF __INT32_MAX__
int MIN_CAL[N_MAX];
int N;
int get_min_cal(int n);
int main() {
    scanf("%d", &N);
    for (int i = 0; i <= N; i++) MIN_CAL[i] = -1;
    MIN_CAL[0] = INF;
    MIN_CAL[1] = 0;
    MIN_CAL[2] = 1;
    MIN_CAL[3] = 1;
    printf("%d", get_min_cal(N));
    return 0;
}
int get_min_cal(int n) {
    if (MIN_CAL[n] > -1) return MIN_CAL[n];
    int mod_3 = INF, mod_2 = INF, minus_1 = INF;
    if (n % 3 == 0) mod_3 = get_min_cal(n / 3) + 1;
    if (n % 2 == 0) mod_2 = get_min_cal(n / 2) + 1;
    minus_1 = get_min_cal(n - 1) + 1;

    int min = INF;
    if (min > mod_3) min = mod_3;
    if (min > mod_2) min = mod_2;
    if (min > minus_1) min = minus_1;
    MIN_CAL[n] = min;
    return min;
}