#include <stdio.h>

typedef struct call {
    int zero, one;
} call;

call calls[41];

call fib(int n);

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        int N;
        scanf("%d", &N);
        for (int i = 0; i <= N; i++) {
            calls[i].zero = -1;
            calls[i].one = -1;
        }
        fib(N);
        printf("%d %d\n", calls[N].zero, calls[N].one);
    }
    return 0;
}

call fib(int n) {
    if (calls[n].zero != -1) return calls[n];
    call output;
    if (n == 0) {
        output.zero = 1;
        output.one = 0;
    } else if (n == 1) {
        output.zero = 0;
        output.one = 1;
    } else {
        call n_1 = fib(n - 1);
        call n_2 = fib(n - 2);
        output.zero = n_1.zero + n_2.zero;
        output.one = n_1.one + n_2.one;
    }
    calls[n] = output;
    return output;
}