#include <stdio.h>
#define N_MAX 500000
#define V_MAX 1000000
int N, M;
int parent[N_MAX];
int level[N_MAX];

int get_parent(int u);
int merge(int u, int v);

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        parent[i] = i;
        level[i] = 1;
    }
    for (int m = 1; m <= M; m++) {
        int s, e;
        scanf("%d %d", &s, &e);
        int success = merge(s, e);
        if (success == -1) {
            printf("%d", m);
            return 0;
        }
    }
    printf("0");
    return 0;
}

int get_parent(int u) {
    if (parent[u] == u) return u;
    parent[u] = get_parent(parent[u]);
    return parent[u];
}
int merge(int u, int v) {
    int p_u = get_parent(u);
    int p_v = get_parent(v);
    if (p_u == p_v) return -1;
    if (level[p_u] > level[p_v]) {
        int temp = p_v;
        p_v = p_u;
        p_u = temp;
    }
    parent[p_u] = p_v;
    if (level[p_u] == level[p_v]) level[p_v]++;
    return 0;
}