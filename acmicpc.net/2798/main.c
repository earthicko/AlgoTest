#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int cards[100];
    for (int i = 0; i < n; i++) scanf("%d", cards + i);
    int max_sum = 0;
    for (int a = 0; a < n; a++) {
        for (int b = a + 1; b < n; b++) {
            for (int c = b + 1; c < n; c++) {
                int sum = cards[a] + cards[b] + cards[c];
                if (sum <= m && sum > max_sum) max_sum = sum;
            }
        }
    }
    printf("%d\n", max_sum);
    return 0;
}