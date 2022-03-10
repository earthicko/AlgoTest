#include <stdio.h>
#define N_MAX 100000

int numbers[N_MAX];
int N;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &numbers[i]);
    }
    int s = 0, e = N - 1;
    int min_div = numbers[s] + numbers[e];
    min_div = (min_div > 0) ? min_div : -min_div;
    int fit_s = s, fit_e = e;
    while (s <= N - 1 && e >= 0 && s < e) {
        int div = numbers[s] + numbers[e];
        int abs_div = (div > 0) ? div : -div;
        if (abs_div < min_div) {
            min_div = abs_div;
            fit_s = s;
            fit_e = e;
        }
        if (div > 0)
            e--;
        else if (div < 0)
            s++;
        else
            break;
    }
    printf("%d %d", numbers[fit_s], numbers[fit_e]);

    return 0;
}