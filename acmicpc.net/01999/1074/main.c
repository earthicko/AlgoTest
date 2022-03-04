#include <stdio.h>

int main() {
    int N, R, C;
    int pow_2[30];
    scanf("%d %d %d", &N, &R, &C);
    pow_2[0] = 1;
    for (int i = 1; i < 2 * N; i++) pow_2[i] = pow_2[i - 1] * 2;
    int sum = 0;
    for (int n = N; n > 0; n--) {
        int r, c;
        if (R < pow_2[n - 1]) {
            r = 0;
        } else {
            r = 1;
            R -= pow_2[n - 1];
        }
        if (C < pow_2[n - 1]) {
            c = 0;
        } else {
            c = 1;
            C -= pow_2[n - 1];
        }
        int multiplier;
        if (r == 0 && c == 0)
            multiplier = 0;
        else if (r == 0 && c == 1)
            multiplier = 1;
        else if (r == 1 && c == 0)
            multiplier = 2;
        else if (r == 1 && c == 1)
            multiplier = 3;
        sum += pow_2[(n - 1) * 2] * multiplier;
    }
    printf("%d\n", sum);
    return 0;
}