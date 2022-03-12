#include <stdio.h>

int main() {
    long long M = 1234567891, r = 31, L;
    long long r_pow_mod[50];
    scanf("%lld", &L);
    r_pow_mod[0] = 1;
    for (int i = 1; i < L; i++) r_pow_mod[i] = (r_pow_mod[i - 1] * r) % M;

    char str[51];
    scanf("%s", str);
    long long hash = 0;
    for (int i = 0; i < L; i++) {
        long long added = ((str[i] - 'a' + 1) * r_pow_mod[i]) % M;
        hash = (hash + added) % M;
    }
    printf("%lld\n", hash);

    return 0;
}