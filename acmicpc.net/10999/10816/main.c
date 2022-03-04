#include <stdio.h>
#define SCOPE 20000001
#define ABS_MAX 10000000
int counter[SCOPE];
int N, M;
int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int new;
        scanf("%d", &new);
        counter[new + ABS_MAX]++;
    }
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int new;
        scanf("%d", &new);
        printf("%d ", counter[new + ABS_MAX]);
    }
    return 0;
}