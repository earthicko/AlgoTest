#include <stdio.h>
#define N_MAX 100

int N, M;
int E[N_MAX][N_MAX];
int VISITED[N_MAX];

int do_bfs(int s);

int main() {
    scanf("%d\n%d\n", &N, &M);
    for (int m = 0; m < M; m++) {
        int s, e;
        scanf("%d %d", &s, &e);
        E[s - 1][e - 1] = 1;
        E[e - 1][s - 1] = 1;
    }
    do_bfs(0);
    int count = 0;
    for (int n = 0; n < N; n++)
        if (VISITED[n]) count++;
    printf("%d", count - 1);
    return 0;
}

int do_bfs(int s) {
    int queue[10000];
    int front = 0, back = 1, n = 1;
    queue[1] = s;
    VISITED[s] = 1;
    while (n > 0) {
        front = (front + 1) % 10000;
        n--;
        int here = queue[front];
        for (int e = 0; e < N; e++) {
            if (E[here][e] == 0) continue;
            if (VISITED[e]) continue;
            VISITED[e] = 1;
            back = (back + 1) % 10000;
            n++;
            queue[back] = e;
        }
    }
    return 0;
}