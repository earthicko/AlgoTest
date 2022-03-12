#include <stdio.h>
#include <string.h>
#define N_MAX 10001
int main() {
    int N, queue[N_MAX], front = 0, back = 0;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        char command[11];
        scanf("%s", command);
        if (strcmp(command, "push_front") == 0) {
            int input;
            scanf("%d", &input);
            queue[front] = input;
            front = (front - 1 + N_MAX) % N_MAX;
        } else if (strcmp(command, "push_back") == 0) {
            int input;
            scanf("%d", &input);
            back = (back + 1) % N_MAX;
            queue[back] = input;
        } else if (strcmp(command, "pop_front") == 0) {
            if (back != front) {
                front = (front + 1) % N_MAX;
                printf("%d\n", queue[front]);
            } else {
                printf("-1\n");
            }
        } else if (strcmp(command, "pop_back") == 0) {
            if (back != front) {
                int output = queue[back];
                back = (back - 1 + N_MAX) % N_MAX;
                printf("%d\n", output);
            } else {
                printf("-1\n");
            }
        } else if (strcmp(command, "size") == 0) {
            printf("%d\n", (back - front + N_MAX) % N_MAX);
        } else if (strcmp(command, "empty") == 0) {
            if (back != front)
                printf("0\n");
            else
                printf("1\n");
        } else if (strcmp(command, "front") == 0) {
            if (back != front)
                printf("%d\n", queue[(front + 1) % N_MAX]);
            else
                printf("-1\n");
        } else if (strcmp(command, "back") == 0) {
            if (back != front)
                printf("%d\n", queue[back]);
            else
                printf("-1\n");
        }
    }
    return 0;
}