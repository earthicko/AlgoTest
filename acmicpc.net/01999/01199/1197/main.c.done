#include <stdio.h>
#include <stdlib.h>
#define V_MAX 10000
#define E_MAX 100000

typedef struct edge {
    int s, e, w;
} edge;

int V, E;
edge edges[E_MAX];
int parent[V_MAX];
int level[V_MAX];

int cmp(const void* a, const void* b);

int find(int node);
int merge(int u, int v);

int main() {
    scanf("%d %d", &V, &E);
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i].s, &edges[i].e, &edges[i].w);
    }
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        level[i] = 1;
    }
    qsort(edges, E, sizeof(edge), cmp);
    int sum_w = 0;
    for (int i = 0; i < E; i++) {
        int success = merge(edges[i].s - 1, edges[i].e - 1);
        if (success == 0) sum_w += edges[i].w;
    }
    printf("%d\n", sum_w);
    return 0;
}

int find(int node) {
    if (parent[node] == node) return node;
    parent[node] = find(parent[node]);
    return parent[node];
}

int merge(int u, int v) {
    int p_u = find(u);
    int p_v = find(v);
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

int cmp(const void* a, const void* b) {
    if (((edge*)a)->w > ((edge*)b)->w) return 1;
    if (((edge*)a)->w < ((edge*)b)->w) return -1;
    return 0;
}