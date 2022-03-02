#include <stdio.h>

int main() {
    int K, N;
    int l[10000];
    int min = 1, max = 0;
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; i++) {
        scanf("%d", l + i);
        if (l[i] > max) max = l[i];
    }
    int mid, count = 0;
    mid = (min + max) / 2;
    while (min + 1 < max) {
        count = 0;
        for (int i = 0; i < N; i++) count += l[i] / mid;
        if (count < K)
            max = mid - 1;
        else
            min = mid;
        mid = (min + max) / 2;
    }
    printf("%d\n", mid);
    return 0;
}