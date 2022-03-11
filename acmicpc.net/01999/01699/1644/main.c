#include <stdio.h>
#define N_MAX 4000001  // 16MB
int N;
int IS_PRIME[N_MAX];
int main() {
    scanf("%d", &N);
    for (int i = 0; i <= N; i++) IS_PRIME[i] = 1;
    IS_PRIME[0] = 0;
    IS_PRIME[1] = 0;
    for (int i = 4; i <= N; i += 2) IS_PRIME[i] = 0;
    for (int i = 3; i <= N; i += 2)
        if (IS_PRIME[i])
            for (int j = i * 2; j <= N; j += i) IS_PRIME[j] = 0;

    int num = 0;
    for (int i = N; i >= 2; i--) {
        if (IS_PRIME[i]) {
            int sum = 0;
            for (int j = i; j >= 2; j--) {
                if (IS_PRIME[j]) sum += j;
                if (sum == N) num++;
                if (sum >= N) break;
            }
        }
    }
    printf("%d", num);

    return 0;
}