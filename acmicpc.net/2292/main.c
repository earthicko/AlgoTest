#include <stdio.h>
int main() {
    int n;
    scanf("%d", &n);
    int i = 1, sum = 1;
    for (i = 1; sum < n; i++) sum += 6 * i;
    printf("%d\n", i);
    return 0;
}