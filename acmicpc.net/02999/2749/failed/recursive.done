/*
input: n (1<=n<=1,000,000,000,000,000,000) 1000000000000000000
output: Fn % 1,000,000

4B = 2^32
n < 2^60 < 2^64 = 8B = unsigned long long int

F(n) = F(a + 1) * F(n - a) + F(a) * F(n - a - 1)

n % 2 == 0:
    F(n) = F(n / 2) * F(n / 2 + 1) + F(n / 2) * F(n / 2 - 1)
n % 2 == 1:
    f(n) = F((n + 1) / 2) ^ 2 + F((n - 1) / 2) ^ 2
*/
#include <stdio.h>
#define P 1000000
#define DEBUG 1

typedef unsigned long long int ull;
typedef unsigned int uint;

ull mod_fibo(ull n);

int main() {
    ull n;
    scanf("%lld", &n);
    printf("%llu", mod_fibo(n));
    return 0;
}

ull mod_fibo(ull n) {
    if (DEBUG) printf("F(%llu) = ?\n", n);
    if (n <= 1) {
        if (n == 0) {
            if (DEBUG) printf("F(%llu) = 0\n", n);
            return 0;
        }
        if (n == 1) {
            if (DEBUG) printf("F(%llu) = 1\n", n);
            return 1;
        }
    }
    if (n % 2) {
        // f(n) = F((n + 1) / 2) ^ 2 + F((n - 1) / 2) ^ 2
        //               a                    b
        if (DEBUG)
            printf("F(%llu) = F(%llu)^2 + F(%llu)^2\n", n, (n + 1) / 2,
                   (n - 1) / 2);
        ull a, b;
        a = mod_fibo((n + 1) / 2);
        b = mod_fibo((n - 1) / 2);
        ull output = ((a * a) % P + (b * b) % P) % P;
        if (DEBUG) printf("F(%llu) = %llu\n", n, output);
        return output;
    } else {
        // F(n) = F(n / 2) * F(n / 2 + 1) + F(n / 2) * F(n / 2 - 1)
        //            a            c            a            b
        // c = a + b => a (a + 2b) = a^2 + 2ab
        if (DEBUG)
            printf("F(%llu) = F(%llu)^2 + 2 * F(%llu) * F(%llu)\n", n, n / 2,
                   n / 2, n / 2 - 1);
        ull a, b;
        a = mod_fibo(n / 2);
        b = mod_fibo(n / 2 - 1);
        ull output = ((a * a) % P + (2 * a * b) % P) % P;
        if (DEBUG) printf("F(%llu) = %llu\n", n, output);
        return output;
    }
}