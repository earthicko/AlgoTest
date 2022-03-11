#include <stdio.h>
#include <stdlib.h>
#define N_MAX 100001
#define INF __INT32_MAX__

int N, K;
int MIN_T[N_MAX];
int VISITED[N_MAX];

int do_bfs(int s, int e);

int main() {
    scanf("%d %d", &N, &K);
    do_bfs(N, K);
    printf("%d", MIN_T[K]);
    return 0;
}
int do_bfs(int s, int e) {
    for (int i = 0; i < N_MAX; i++) MIN_T[i] = INF;

    int queue[N_MAX];
    int front = 0, back = 1, n = 1;
    queue[1] = s;
    MIN_T[s] = 0;
    VISITED[s] = 1;

    while (n > 0) {
        front = (front + 1) % N_MAX;
        n--;
        int here = queue[front];

        int there[3] = {here - 1, here + 1, here * 2};
        for (int i = 0; i < 3; i++) {
            if (there[i] < 0 || there[i] >= N_MAX) continue;
            if (VISITED[there[i]]) continue;
            VISITED[there[i]] = 1;

            MIN_T[there[i]] = MIN_T[here] + 1;
            if (there[i] == e) return 0;

            back = (back + 1) % N_MAX;
            n++;
            queue[back] = there[i];
        }
    }
    return 0;
}
