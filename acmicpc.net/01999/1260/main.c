#include <stdio.h>
#define N_MAX 1000

int N, M, V;
int E[N_MAX][N_MAX];
int VISITED[N_MAX];

int do_dfs(int s);
int do_bfs(int s);

int main() {
    scanf("%d %d %d", &N, &M, &V);
    for (int i = 0; i < M; i++) {
        int s, e;
        scanf("%d %d", &s, &e);
        E[s - 1][e - 1] = 1;
        E[e - 1][s - 1] = 1;
    }
    do_dfs(V - 1);
    printf("\n");
    for (int i = 0; i < N; i++) VISITED[i] = 0;
    do_bfs(V - 1);
    return 0;
}

int do_dfs(int s) {
    printf("%d ", s + 1);
    VISITED[s] = 1;
    for (int i = 0; i < N; i++)
        if (E[s][i] && !VISITED[i]) do_dfs(i);
    return 0;
}
int do_bfs(int s) {
    int queue[N_MAX], front = 0, back = 1, n = 1;
    queue[1] = s;
    VISITED[s] = 1;
    while (n > 0) {
        front = (front + 1) % N_MAX;
        n--;
        int here = queue[front];
        printf("%d ", here + 1);
        for (int i = 0; i < N; i++)
            if (E[here][i] && !VISITED[i]) {
                VISITED[i] = 1;
                back = (back + 1) % N_MAX;
                n++;
                queue[back] = i;
            }
    }
    return 0;
}