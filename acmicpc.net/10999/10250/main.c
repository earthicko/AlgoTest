#include <stdio.h>

// / 층수 = 호수, % 층수 = 층수

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        int h, w, n;  // 충수, 방수, 순번
        scanf("%d %d %d", &h, &w, &n);
        int floor = n % h, num = (n - 1) / h + 1;
        if (floor == 0) floor = h;
        printf("%d\n", floor * 100 + num);
    }
    return 0;
}