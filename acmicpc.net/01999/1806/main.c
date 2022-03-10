#include <stdio.h>
#define N_MAX 100000
int N, S;
int numbers[N_MAX];

int main() {
    scanf("%d %d", &N, &S);
    for (int i = 0; i < N; i++) scanf("%d", &numbers[i]);

    int s = 0, e = 0, fit_l = N_MAX + 1, sum = numbers[0];
    while (e < N && s <= e) {
        if (S <= sum && e - s + 1 < fit_l) {
            fit_l = e - s + 1;
            if (fit_l == 1) break;
        }
        if (sum < S) {
            sum += numbers[++e];
        } else {
            sum -= numbers[s++];
        }
    }
    if (fit_l == N_MAX + 1) fit_l = 0;
    printf("%d", fit_l);
    return 0;
}