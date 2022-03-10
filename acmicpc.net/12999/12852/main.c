#include <stdio.h>
#define N_MAX 1000001
int PREV[N_MAX];
int HISTORY[N_MAX];
int history_n;
int MIN_MOVE[N_MAX];
int N, min;
int do_dfs(int now, int prev, int n);
int main() {
    scanf("%d", &N);
    min = __INT32_MAX__;
    for (int i = 1; i <= N; i++) MIN_MOVE[i] = __INT32_MAX__;
    do_dfs(N, 0, 0);
    // printf("Min count is %d\n", min);
    int cursor = 1;
    while (1) {
        HISTORY[history_n++] = cursor;
        cursor = PREV[cursor];
        if (cursor == 0) break;
    }
    printf("%d\n", min);
    for (int i = history_n - 1; i >= 0; i--) printf("%d ", HISTORY[i]);
    return 0;
}
int do_dfs(int now, int prev, int n) {
    // printf("from %d, now %d\n", prev, now);
    if (MIN_MOVE[now] > n) {
        MIN_MOVE[now] = n;
        PREV[now] = prev;
    } else {
        return 0;
    }
    if (now == 1) {
        // printf("Found 1, finish\n");
        if (min > n) min = n;
        return 0;
    }
    if (now % 3 == 0) do_dfs(now / 3, now, n + 1);
    if (now % 2 == 0) do_dfs(now / 2, now, n + 1);
    if (now >= 2) do_dfs(now - 1, now, n + 1);
    return 0;
}