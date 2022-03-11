#include <stdio.h>

int K, N, result;
int lengths[10001];
int max_len = 0;
long long mid, max, min;

int main() {
    scanf("%d %d", &K, &N);

    for (int i = 0; i < K; i++) {
        scanf("%d", &(lengths[i]));
        if (max_len < lengths[i]) max_len = lengths[i];
    }
    min = 1;
    max = max_len;
    result = 0;

    while (min <= max) {
        mid = (min + max) / 2;
        int counter = 0;
        for (int i = 0; i < K; i++) counter += lengths[i] / mid;

        if (counter >= N) {
            min = mid + 1;
            if (result < mid) result = mid;
        } else {
            max = mid - 1;
        }
    }

    printf("%d\n", result);
    return 0;
}