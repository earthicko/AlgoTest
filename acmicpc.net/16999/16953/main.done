#include <stdio.h>
#define MAX 1000000000
int A, B;
int min = __INT32_MAX__;
int do_dfs(int s, int count);
int main() {
    scanf("%d %d", &A, &B);
    do_dfs(A, 0);
    if (min == __INT32_MAX__)
        printf("-1\n");
    else
        printf("%d", min + 1);
    return 0;
}
int do_dfs(int s, int count) {
    if (s == B) {
        if (min > count) min = count;
        return 0;
    }
    int e0, e1;
    if (s <= MAX / 2) do_dfs(s * 2, count + 1);
    if (s <= (MAX - 1) / 10) do_dfs(s * 10 + 1, count + 1);
    return 0;
}