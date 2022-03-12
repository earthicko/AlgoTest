#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define N_MAX 100
#define E_MAX 4950

typedef struct edge {
    int s, e;
    double w;
} edge;

int parent[N_MAX], level[N_MAX];
int N;
edge edges[E_MAX];
double X[N_MAX], Y[N_MAX];

int find(int v) {
    if (parent[v] == v) return v;
    parent[v] = find(parent[v]);
    return parent[v];
}

int merge(int u, int v) {
    int pu = find(u);
    int pv = find(v);
    if (pu == pv) return -1;
    if (level[pu] > level[pv]) {
        int temp = pu;
        pu = pv;
        pv = temp;
    }
    parent[pu] = pv;
    if (level[pu] == level[pv]) level[pv]++;
    return 0;
}

int cmp(const void* a, const void* b) {
    if (((edge*)a)->w > ((edge*)b)->w) return 1;
    if (((edge*)a)->w < ((edge*)b)->w) return -1;
    return 0;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%lf %lf", &X[i], &Y[i]);
        parent[i] = i;
        level[i] = 1;
    }
    int n_edges = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            edges[n_edges].s = i;
            edges[n_edges].e = j;
            double dx = X[i] - X[j];
            double dy = Y[i] - Y[j];
            edges[n_edges].w = sqrt(dx * dx + dy * dy);
            n_edges++;
        }
    }
    qsort(edges, n_edges, sizeof(edge), cmp);
    double sum_w = 0;
    for (int i = 0; i < n_edges; i++) {
        int success = merge(edges[i].s, edges[i].e);
        if (success == 0) sum_w += edges[i].w;
    }
    sum_w *= 100;
    ceil(sum_w);
    sum_w /= 100;
    printf("%0.2lf", sum_w);
    return 0;
}