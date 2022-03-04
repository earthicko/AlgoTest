#include <stdio.h>

int IS_COMPOSITE[1000001];

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    IS_COMPOSITE[1] = 1;
    for (int cursor = 4; cursor <= n; cursor += 2) IS_COMPOSITE[cursor] = 1;

    for (int cursor = 3; cursor <= n; cursor += 2) {
        if (!IS_COMPOSITE[cursor]) {
            for (int div = cursor * 2; div <= n; div += cursor) {
                IS_COMPOSITE[div] = 1;
            }
        }
    }
    for (int i = m; i <= n; i++)
        if (!IS_COMPOSITE[i]) printf("%d\n", i);
    return 0;
}