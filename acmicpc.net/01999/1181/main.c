#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b);

int main(void) {
    char strs[20000][51];
    char strs_unique[20002][51];
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%s", strs[i]);

    qsort((void *)strs, n, sizeof(strs[0]), cmp);

    int unique_i = 1;
    for (int i = 0; i < n; i++) {
        if (strcmp(strs_unique[unique_i - 1], strs[i]) != 0) {
            strcpy(strs_unique[unique_i], strs[i]);
            unique_i++;
        }
    }
    for (int i = 1; i < unique_i; i++) printf("%s\n", strs_unique[i]);

    return 0;
}

int cmp(const void *a, const void *b) {
    if (strlen((char *)a) < strlen((char *)b)) return -1;
    if (strlen((char *)a) > strlen((char *)b)) return 1;
    return (strcmp((char *)a, (char *)b));
}