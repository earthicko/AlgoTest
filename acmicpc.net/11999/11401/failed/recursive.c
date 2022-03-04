/*
문제
자연수 N과 정수 K가 주어졌을 때 이항 계수 ({N}{K})를 1,000,000,007로 나눈
나머지를 구하는 프로그램을 작성하시오.

입력
첫째 줄에 N과 K가 주어진다. (1 ≤ N ≤ 4,000,000, 0 ≤ K ≤ N)

출력
({N}{K})를 1,000,000,007로 나눈 나머지를 출력한다.

1. f(n, k) = f(n, n - k)
2. f(n, 0) = 1, f(0, k) = 1
3. f(n, k) = f(n - 1, k - 1) + f(n - 1, k)
*/

#include <stdio.h>

#define DENOM 1000000007

int get_mod_binom_coef(int n, int k);

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    printf("%d", get_mod_binom_coef(n, k));

    return 0;
}

int get_mod_binom_coef(int n, int k) {
    if (n == 0 || k == 0) {
        printf("f(%d, %d) = 1\n", n, k);
        return 1;
    }
    if (k > n / 2) return get_mod_binom_coef(n, n - k);
    int sum = get_mod_binom_coef(n - 1, k - 1) + get_mod_binom_coef(n - 1, k);
    if (sum >= DENOM) sum = sum % DENOM;
    printf("f(%d, %d) = %d\n", n, k, sum);
    return sum;
}