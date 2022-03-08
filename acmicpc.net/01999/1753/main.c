#include <stdio.h>
#include <stdlib.h>
#define V_MAX 20000

typedef struct Item {
    int v, w;
} Item;
typedef struct Node {
    int v, d;
} Node;
typedef struct List {
    int n, cap;
    Item* items;
    int (*append)(struct List*, Item);
    int (*resize)(struct List*, int);
} List;
typedef struct Heap {
    int (*cmp)(struct Heap*, int, int);
    int (*push)(struct Heap*, Node);
    Node (*pop)(struct Heap*);
    int n;  // index where last element is (0 when empty)
    int cap;
    Node* data;  // 1: root / 2~3: level 1 / 4~7: level 2...
} Heap;

int V, E, K;
List* EDGE[V_MAX];
int MIN_D[V_MAX];
int VISITED[V_MAX];

List* List__init__(int cap_);
int List__del__(List* del);
int List_resize(List* this, int cap_);
int List_append(List* this, Item new);
Heap* Heap__init__(int cap_, int (*cmp_)(struct Heap*, int, int));
int Heap__del__(Heap* this);
int Heap_min_compare_node(Heap* this, int idx_a, int idx_b);
int Heap_sort_from_bottom(Heap* this, int start_index);
int Heap_sort_from_top(Heap* this, int start_index);
int Heap_push(Heap* this, Node new_val);
Node Heap_pop(Heap* this);
int Heap_realloc(Heap* this, int new_cap);

int do_dijkstra(int s);

int main() {
    scanf("%d %d", &V, &E);
    scanf("%d", &K);

    for (int i = 0; i < V; i++) EDGE[i] = List__init__(10);
    for (int i = 0; i < E; i++) {
        int s, e, w;
        scanf("%d %d %d", &s, &e, &w);
        Item edge = {e - 1, w};
        EDGE[s - 1]->append(EDGE[s - 1], edge);
    }

    do_dijkstra(K - 1);

    for (int i = 0; i < V; i++) {
        if (MIN_D[i] == 3000001)
            printf("INF\n");
        else
            printf("%d\n", MIN_D[i]);
    }
    return 0;
}

int do_dijkstra(int s) {
    for (int i = 0; i < V; i++) MIN_D[i] = 3000001;
    MIN_D[s] = 0;

    Heap* queue = Heap__init__(V_MAX, Heap_min_compare_node);
    Node start = {s, 0};
    queue->push(queue, start);

    while (queue->n > 0) {
        Node here = queue->pop(queue);

        for (int i = 0; i < EDGE[here.v]->n; i++) {
            Node there;
            there.v = EDGE[here.v]->items[i].v;
            there.d = MIN_D[here.v] + EDGE[here.v]->items[i].w;

            if (MIN_D[there.v] <= there.d) continue;
            if (VISITED[there.v]) continue;

            MIN_D[there.v] = there.d;
            queue->push(queue, there);
        }
        VISITED[here.v] = 1;
    }
    return 0;
}

List* List__init__(int cap_) {
    List* new = (List*)malloc(sizeof(List));
    new->n = 0;
    new->cap = cap_;
    new->items = (Item*)malloc(sizeof(Item) * cap_);
    new->append = List_append;
    new->resize = List_resize;
    return new;
}
int List__del__(List* del) {
    free(del->items);
    free(del);
    return 0;
}
int List_resize(List* this, int cap_) {
    Item* temp = this->items;
    this->items = (Item*)malloc(sizeof(Item) * cap_);
    for (int i = 0; i < this->n; i++) this->items[i] = temp[i];
    free(temp);
    this->cap = cap_;
    return 0;
}
int List_append(List* this, Item new) {
    if (this->n == this->cap) this->resize(this, this->cap * 2);
    this->items[this->n] = new;
    this->n++;
    return 0;
}
Heap* Heap__init__(int cap_, int (*cmp_)(struct Heap*, int, int)) {
    Heap* new = (Heap*)malloc(sizeof(Heap));
    new->cmp = cmp_;
    new->push = Heap_push;
    new->pop = Heap_pop;
    new->n = 0;
    new->cap = cap_;
    new->data = (Node*)malloc(sizeof(Node) * cap_);
    return new;
}
int Heap__del__(Heap* this) {
    free(this->data);
    free(this);
    return 0;
}
int Heap_min_compare_node(Heap* this, int a, int b) {
    if (this->data[a].d > this->data[b].d) return 1;
    if (this->data[a].d == this->data[b].d) return 0;
    return -1;
}
int Heap_sort_from_bottom(Heap* this, int s_idx) {
    if (s_idx == 1) return 0;
    int parent_idx = s_idx / 2;
    if (this->cmp(this, parent_idx, s_idx) == 1) {
        Node temp = this->data[parent_idx];
        this->data[parent_idx] = this->data[s_idx];
        this->data[s_idx] = temp;
        Heap_sort_from_bottom(this, parent_idx);
    }
    return 0;
}
int Heap_sort_from_top(Heap* this, int s_idx) {
    int l_idx = s_idx * 2;
    int r_idx = s_idx * 2 + 1;
    Node parent, l, r;
    char swap = 0;
    if (l_idx <= this->n) {
        parent = this->data[s_idx];
        l = this->data[l_idx];
        if (r_idx <= this->n) {
            r = this->data[r_idx];
            if (this->cmp(this, s_idx, l_idx) == 1 &&
                this->cmp(this, s_idx, r_idx) == 1) {
                if (this->cmp(this, r_idx, l_idx) >= 0)
                    swap = 1;
                else
                    swap = 2;
            } else if (this->cmp(this, s_idx, l_idx) == 1) {
                swap = 1;
            } else if (this->cmp(this, s_idx, r_idx) == 1) {
                swap = 2;
            }
        } else {
            if (this->cmp(this, s_idx, l_idx) == 1) swap = 1;
        }
    }
    switch (swap) {
        case 0:
            break;
        case 1:
            this->data[l_idx] = parent;
            this->data[s_idx] = l;
            Heap_sort_from_top(this, l_idx);
            break;
        case 2:
            this->data[r_idx] = parent;
            this->data[s_idx] = r;
            Heap_sort_from_top(this, r_idx);
            break;
        default:
            break;
    }
    return 0;
}
int Heap_push(Heap* this, Node new_val) {
    if (this->n + 1 == this->cap) Heap_realloc(this, this->cap * 2);
    this->n++;
    this->data[this->n] = new_val;
    if (this->n == 1) return 0;
    Heap_sort_from_bottom(this, this->n);
    return 0;
}
Node Heap_pop(Heap* this) {
    Node top_val = this->data[1];
    this->data[1] = this->data[this->n];
    this->n--;
    if (this->n == 0) return top_val;
    Heap_sort_from_top(this, 1);
    return top_val;
}
int Heap_realloc(Heap* this, int new_cap) {
    if (new_cap <= this->cap) return 0;
    this->cap = new_cap;
    Node* temp = this->data;
    this->data = (Node*)malloc(sizeof(Node) * new_cap);
    for (int i = 0; i < this->n; i++) this->data[i] = temp[i];
    return 0;
}