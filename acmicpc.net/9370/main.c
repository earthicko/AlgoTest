#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define n_MAX 2001
#define t_MAX 100
#define QUEUE_SIZE 1000000

typedef struct node {
    int n, d;
} node;

typedef struct heap {
    int (*bottom_sorter)(int, struct heap*);
    int (*top_sorter)(int, struct heap*);
    int last_index;         // index where last element is (0 when empty)
    node data[QUEUE_SIZE];  // 1: root / 2~3: level 1 / 4~7: level 2...
} heap;

int N_CASES, N_DEST, N_VISITED_DEST, N_POSSIBLE_DEST;
int START, DEST[t_MAX], POSSIBLE_DEST[t_MAX], G, H;
int N_NODES, N_TOTAL_ROADS, N_ROADS[n_MAX];
int ROADS[n_MAX][n_MAX], D[n_MAX][n_MAX];
int VISITED[n_MAX];
int MIN_D_FROM_S[n_MAX], MIN_D_FROM_G[n_MAX], MIN_D_FROM_H[n_MAX];
int PREV[n_MAX];

int cmpfunc(const void* a, const void* b);
int sort_min_heap_from_bottom(int start_index, heap* target);
int sort_min_heap_from_top(int start_index, heap* target);
int put_heap(node new_val, heap* target);
node get_heap(struct heap* target);

int is_dest(int test_target);
int do_dijkstra(int start, int min_d[n_MAX]);

int main() {
    scanf("%d", &N_CASES);
    for (int n_case = 0; n_case < N_CASES; n_case++) {
        scanf("%d %d %d", &N_NODES, &N_TOTAL_ROADS, &N_DEST);
        scanf("%d %d %d", &START, &G, &H);
        for (int i = 1; i <= N_NODES; i++) N_ROADS[i] = 0;
        for (int i = 0; i < N_TOTAL_ROADS; i++) {
            int a, b, d;
            scanf("%d %d %d", &a, &b, &d);
            D[a][b] = d;
            D[b][a] = d;
            ROADS[a][N_ROADS[a]] = b;
            ROADS[b][N_ROADS[b]] = a;
            N_ROADS[a]++;
            N_ROADS[b]++;
        }
        for (int i = 0; i < N_DEST; i++) scanf("%d", &(DEST[i]));

        N_VISITED_DEST = 0;
        for (int i = 1; i <= N_NODES; i++) {
            MIN_D_FROM_S[i] = INT_MAX;
            MIN_D_FROM_G[i] = INT_MAX;
            MIN_D_FROM_H[i] = INT_MAX;
        }
        // get min distance to g, h, all destinations
        do_dijkstra(START, MIN_D_FROM_S);
        do_dijkstra(G, MIN_D_FROM_G);
        do_dijkstra(H, MIN_D_FROM_H);

        N_POSSIBLE_DEST = 0;
        int min_d_from_s_to_g = MIN_D_FROM_S[G];
        int min_d_from_s_to_h = MIN_D_FROM_S[H];
        int g_to_h = D[G][H];
        for (int i = 0; i < N_DEST; i++) {
            int min_d_from_s_to_d = MIN_D_FROM_S[DEST[i]];

            int min_d_from_g_to_d = MIN_D_FROM_G[DEST[i]];
            int min_d_from_h_to_d = MIN_D_FROM_H[DEST[i]];
            int min_d_s_g_h_d = min_d_from_s_to_g + D[G][H] + min_d_from_h_to_d;
            int min_d_s_h_g_d = min_d_from_s_to_h + D[H][G] + min_d_from_g_to_d;
            if (min_d_s_g_h_d == min_d_from_s_to_d ||
                min_d_s_h_g_d == min_d_from_s_to_d) {
                POSSIBLE_DEST[N_POSSIBLE_DEST++] = DEST[i];
            }
        }

        qsort(POSSIBLE_DEST, N_POSSIBLE_DEST, sizeof(int), cmpfunc);
        for (int i = 0; i < N_POSSIBLE_DEST; i++)
            printf("%d ", POSSIBLE_DEST[i]);
        printf("\n");
    }
}

int is_dest(int test_target) {
    for (int i = 0; i < N_DEST; i++) {
        if (DEST[i] == test_target) return 1;
    }
    return 0;
}

int trace_route(int start) {
    int curr = start;
    int prev = PREV[curr];
    int found = 0;
    while (prev != START) {
        if ((prev == G && curr == H) || (prev == H && curr == G)) {
            found = 1;
            break;
        }
        curr = PREV[curr];
        prev = PREV[prev];
    }
    return found;
}

int do_dijkstra(int start, int min_d[n_MAX]) {
    for (int i = 1; i <= N_NODES; i++) {
        min_d[i] = INT_MAX;
        VISITED[i] = 0;
    }

    heap* queue = (heap*)malloc(sizeof(heap));
    queue->bottom_sorter = sort_min_heap_from_bottom;
    queue->top_sorter = sort_min_heap_from_top;
    queue->last_index = 0;

    node start_node = {start, 0};
    put_heap(start_node, queue);
    min_d[start] = 0;
    while (queue->last_index > 0 ||
           (!VISITED[G] && !VISITED[H] && N_VISITED_DEST < N_DEST)) {
        node here = get_heap(queue);
        for (int i = 0; i < N_ROADS[here.n]; i++) {
            node there = {ROADS[here.n][i], 0};
            if (VISITED[there.n]) continue;
            if (min_d[here.n] + D[here.n][there.n] < min_d[there.n]) {
                min_d[there.n] = min_d[here.n] + D[here.n][there.n];
                there.d = min_d[there.n];
                put_heap(there, queue);
                PREV[there.n] = here.n;
            }
        }
        VISITED[here.n] = 1;
        if (is_dest(here.n)) {
            N_VISITED_DEST++;
        }
    }
    free(queue);
}

int cmpfunc(const void* a, const void* b) { return (*(int*)a - *(int*)b); }
int sort_min_heap_from_bottom(int start_index, heap* target) {
    if (start_index == 1) return 0;

    int parent_index = start_index / 2;
    if (target->data[parent_index].d > target->data[start_index].d) {
        // parent is bigger -> swap
        node temp = target->data[parent_index];
        target->data[parent_index] = target->data[start_index];
        target->data[start_index] = temp;
        sort_min_heap_from_bottom(parent_index, target);
    }
    return 0;
}
int sort_min_heap_from_top(int s_idx, heap* target) {
    int l_idx = s_idx * 2;
    int r_idx = s_idx * 2 + 1;

    node parent, l, r, temp;

    char swap = 0;
    if (l_idx <= target->last_index) {
        // left child exists
        parent = target->data[s_idx];
        l = target->data[l_idx];
        if (r_idx <= target->last_index) {  // right child exists
            r = target->data[r_idx];
            if (l.d < parent.d &&
                r.d < parent.d) {  // both children are smaller
                if (l.d <= r.d)
                    swap = 1;  // swap with left child
                else
                    swap = 2;             // swap with right child
            } else if (l.d < parent.d) {  // only left child is smaller
                swap = 1;                 // swap with left child
            } else if (r.d < parent.d) {  // only right child is smaller
                swap = 2;                 // swap with right child
            }
        } else {
            if (l.d < parent.d) swap = 1;  // swap with left child
        }
    }
    switch (swap) {
        case 0:  // do nothing
            break;
        case 1:  // swap with left child
            target->data[l_idx] = parent;
            target->data[s_idx] = l;
            sort_min_heap_from_top(l_idx, target);
            break;
        case 2:  // swap with right child
            target->data[r_idx] = parent;
            target->data[s_idx] = r;
            sort_min_heap_from_top(r_idx, target);
            break;
        default:
            break;
    }

    return 0;
}
int put_heap(node new_val, heap* target) {
    target->last_index++;
    target->data[target->last_index] = new_val;

    if (target->last_index == 1) return 0;

    target->bottom_sorter(target->last_index, target);

    return 0;
}
node get_heap(heap* target) {
    node top_val = target->data[1];
    target->data[1] = target->data[target->last_index];
    target->last_index--;
    if (target->last_index == 0) return top_val;

    target->top_sorter(1, target);

    return top_val;
}