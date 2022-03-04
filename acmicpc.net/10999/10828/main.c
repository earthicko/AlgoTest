#include <stdio.h>
#include <string.h>
#define N_MAX 10000
int main() {
    int N, stack[N_MAX], cur = 0;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        char command[6];
        scanf("%s", command);
        if (strcmp(command, "push") == 0) {
            // printf("push %d\n", input);
            int input;
            scanf("%d", &input);
            stack[cur++] = input;
        } else if (strcmp(command, "pop") == 0) {
            // printf("pop\n");
            if (cur > 0)
                printf("%d\n", stack[--cur]);
            else
                printf("-1\n");
        } else if (strcmp(command, "size") == 0) {
            // printf("size\n");
            printf("%d\n", cur);
        } else if (strcmp(command, "empty") == 0) {
            // printf("empty\n");
            if (cur > 0)
                printf("0\n");
            else
                printf("1\n");
        } else if (strcmp(command, "top") == 0) {
            // printf("top\n");
            if (cur > 0)
                printf("%d\n", stack[cur - 1]);
            else
                printf("-1\n");
        }
    }
    return 0;
}