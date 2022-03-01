#include <limits.h>
#include <stdio.h>

#define N_MAX 500
#define M_MAX 6000

int N, M;
long MIN_COST[N_MAX];
int EDGE[M_MAX][3];

int do_bellman_ford_cycle();
int do_bellman_ford_pathfinding();

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) MIN_COST[i] = LONG_MAX;
    for (int m = 0; m < M; m++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        EDGE[m][0] = a - 1;
        EDGE[m][1] = b - 1;
        EDGE[m][2] = c;
    }
    int negative_cycle = do_bellman_ford_pathfinding();
    if (negative_cycle) {
        printf("-1\n");
    } else {
        for (int i = 1; i < N; i++) {
            if (MIN_COST[i] == LONG_MAX)
                printf("-1\n");
            else
                printf("%ld\n", MIN_COST[i]);
        }
    }

    return 0;
}

int do_bellman_ford_pathfinding() {
    MIN_COST[0] = 0;
    for (int i = 1; i <= N - 1; i++) do_bellman_ford_cycle();
    int negative_cycle = do_bellman_ford_cycle();
    return negative_cycle;
}

int do_bellman_ford_cycle() {
    int renewal_happened = 0;
    for (int e_i = 0; e_i < M; e_i++) {
        int from = EDGE[e_i][0];
        int to = EDGE[e_i][1];
        int cost = EDGE[e_i][2];
        if (MIN_COST[from] == LONG_MAX) continue;
        if (MIN_COST[from] + cost < MIN_COST[to]) {
            MIN_COST[to] = MIN_COST[from] + cost;
            renewal_happened = 1;
        }
    }
    return renewal_happened;
}