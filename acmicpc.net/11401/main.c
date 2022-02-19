/*
문제
자연수 N과 정수 K가 주어졌을 때 이항 계수 ({N}{K})를 1,000,000,007로 나눈
나머지를 구하는 프로그램을 작성하시오.

입력
첫째 줄에 N과 K가 주어진다. (1 ≤ N ≤ 4,000,000, 0 ≤ K ≤ N)

출력
({N}{K})를 1,000,000,007로 나눈 나머지를 출력한다.
==========================================================================
P = 1,000,000,007
({N}{K}) % P = ( N! / K! (N - K)! ) % P
= ( N! * (K! (N - K)!)^-1 ) % P

페르마의 소정리
a^p === a (mod p) where p is prime number
=> a^p-1 === 1

=> a^1 * a^p-2 === 1
a에다 곱하면 1이되는 수 (역수)를 역원이라 하고 a^p-2는 a의 역원이다

(K! (N - K)!)^-1 는 K! (N - K)!의 역원이고, mod p 세상에서 또다른 역원은
(K! (N - K)!) ^ P-2

(엄) 준 식 = ( N! * (K! (N - K)!)^P-2 ) % P
(K! (N - K)!)^P-2 = Y 라 하면
준 식 = ( N!%P * Y%P ) % P
Y = ( K!%P * (N - K)!%P )^P-2

할 일
1. 동적 계획법으로 mod 조여 가면서 팩토리얼 계산
2. 분할 정복으로 mod 조여 가면서 거듭제곱 계산
*/

#include <stdio.h>
#include <stdlib.h>

#define N_MAX 4000000
#define PRIME 1000000007

typedef unsigned long long int ull;

ull generate_mod_factorial_dict(ull limit, ull* dict);
int calculate_mod_factorial(ull limit, int num_targets, ull* targets,
                            ull* output);
ull get_mod_exponential(ull base, ull power);

int main() {
    ull n, k;
    scanf("%lld %lld", &n, &k);

    // ull* f_dict = (ull*)malloc(sizeof(ull) * (n + 1));
    // generate_mod_factorial_dict(n, f_dict);
    // ull n_f = f_dict[n];
    // ull k_f = f_dict[k];
    // ull n_k_f = f_dict[n - k];

    ull f_output[3];
    ull f_calculate_target[3] = {n, k, n - k};
    calculate_mod_factorial(n, 3, f_calculate_target, f_output);
    ull n_f = f_output[0];
    ull k_f = f_output[1];
    ull n_k_f = f_output[2];

    // printf("n! = %lld k! = %lld n-k! = %lld\n", n_f, k_f, n_k_f);
    ull y = get_mod_exponential((k_f * n_k_f) % PRIME, PRIME - 2);
    // printf("y = %lld\n", y);
    ull final = (n_f * y) % PRIME;

    printf("%lld", final);

    return 0;
}

ull generate_mod_factorial_dict(ull limit, ull* dict) {
    dict[0] = 1;
    dict[1] = 1;
    ull i;
    for (i = 2; i <= limit; i++) {
        dict[i] = (dict[i - 1] * i) % PRIME;
        // printf("%lld! = %lld\n", i, dict[i]);
    }
    return 0;
}

int calculate_mod_factorial(ull limit, int num_targets, ull* targets,
                            ull* output) {
    char* done = (char*)malloc(sizeof(char) * num_targets);
    ull i;
    for (i = 0; i < num_targets; i++) {
        if (targets[i] == 0 || targets[i] == 1) {
            output[i] = 1;
            done[i] = 1;
        }
    }

    ull prev = 1;

    for (i = 2; i <= limit; i++) {
        ull curr = (prev * i) % PRIME;
        int j;
        for (j = 0; j < num_targets; j++) {
            if (done[j]) continue;
            if (targets[j] == i) {
                // printf("Found target %lld, output %lld! %lld\n", targets[j], i,
                //        curr);
                output[j] = curr;
                done[j] = 1;
            }
        }
        prev = curr;
    }

    return 0;
}

ull get_mod_exponential(ull base, ull power) {
    // printf("power: %lld base: %lld\n", power, base);
    if (power == 1) return base % PRIME;
    ull half_result = get_mod_exponential(base, power / 2);
    // printf("%lld ^ %lld = %lld\n", base, power / 2, half_result);

    ull result = (half_result * half_result) % PRIME;
    // printf("%lld ^ %lld = %lld\n", base, (power / 2) * 2, half_result);

    if (power % 2 == 1) result = (result * base) % PRIME;

    // printf("%lld ^ %lld = %lld\n", base, power, result);
    return result;
}