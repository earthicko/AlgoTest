#include <stdio.h>

int main() {
    int n, m;
    int h[1000000];
    scanf("%d %d", &n, &m);
    int min = 0, max = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", h + i);
        if (h[i] > max) max = h[i];
    }
    int result = 0;
    while (min <= max) {
        int mid = (min + max) / 2;
        long long h_sum = 0;
        for (int i = 0; i < n; i++)
            if (h[i] - mid > 0) h_sum += h[i] - mid;
        if (h_sum < m) {
            max = mid - 1;
        } else {
            min = mid + 1;
            if (result < mid) result = mid;
        }
    }
    printf("%d\n", result);
    return 0;
}