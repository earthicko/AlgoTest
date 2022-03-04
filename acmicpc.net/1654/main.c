#include <stdio.h>

int main() {
    int K, N;
    int l[10001];
    long long min = 1, max = 0;
    scanf("%d %d", &K, &N);
    for (int i = 0; i < K; i++) {
        scanf("%d", l + i);
        if (l[i] > max) max = (long long)l[i];
    }
    int result = 0;
    while (min <= max) {
        long long mid = (min + max) / 2;
        int count = 0;
        for (int i = 0; i < K; i++) count += l[i] / mid;
        if (count < N) {
            max = mid - 1;
        } else {
            min = mid + 1;
            if (result < mid) result = mid;
        }
    }
    printf("%d\n", result);
    return 0;
}
