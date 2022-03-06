#include <stdio.h>
#define N_MAX 100002

int T, N;
int deque[N_MAX];
int front, back, size, dir;

int main() {
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        char commands[N_MAX];
        scanf("%s", commands);
        scanf("%d", &N);
        scanf("%*c%*c");
        for (int i = 0; i < N; i++) {
            scanf("%d", &deque[i + 1]);
            if (i < N - 1) scanf("%*c");
        }
        scanf("%*c%*c");
        front = 0, back = N, size = N, dir = 1;

        int i = 0;
        char com = commands[i];
        int error_flag = 0;
        while (com != '\0') {
            if (com == 'R') {
                if (dir == 1) {
                    int temp = back;
                    // back = (front + 1) % N_MAX;
                    // front = (temp + 1) % N_MAX;
                    back = front + 1;
                    front = temp + 1;
                    dir = -1;
                } else {
                    int temp = back;
                    // back = (front - 1) % N_MAX;
                    // front = (temp - 1) % N_MAX;
                    back = front - 1;
                    front = temp - 1;
                    dir = 1;
                }
            } else {
                if (front == back) {
                    // if (size == 0) {
                    error_flag = 1;
                    break;
                }
                // size--;
                if (dir == 1) {
                    // front = (front + 1) % N_MAX;
                    front++;
                } else {
                    // front = (front - 1) % N_MAX;
                    front--;
                }
            }
            com = commands[++i];
        }
        if (error_flag) {
            printf("error\n");
        } else {
            if (dir == 1) {
                printf("[");
                for (int i = front + 1; i <= back; i++) {
                    printf("%d", deque[i]);
                    if (i != back) printf(",");
                }
                printf("]\n");
            } else {
                printf("[");
                for (int i = front - 1; i >= back; i--) {
                    printf("%d", deque[i]);
                    if (i != back) printf(",");
                }
                printf("]\n");
            }
        }
    }
    return 0;
}