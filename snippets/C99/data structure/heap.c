#include <stdlib.h>

typedef int Node;

typedef struct Heap {
    int (*cmp)(struct Heap*, int, int);
    int (*push)(struct Heap*, Node);
    Node (*pop)(struct Heap*);
    int n;  // index where last element is (0 when empty)
    int cap;
    Node* data;  // 1: root / 2~3: level 1 / 4~7: level 2...
} Heap;

Heap* Heap__init__(int cap_, int (*cmp_)(struct Heap*, int, int));
int Heap__del__(Heap* this);
int Heap_min_compare_node(Heap* this, int idx_a, int idx_b);
int Heap_max_compare_node(Heap* this, int idx_a, int idx_b);
int Heap_sort_from_bottom(Heap* this, int start_index);
int Heap_sort_from_top(Heap* this, int start_index);
int Heap_push(Heap* this, Node new_val);
Node Heap_pop(Heap* this);
int Heap_realloc(Heap* this, int new_cap);

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
    // a > b => 1, a == b => 0, a < b => -1
    if (this->data[a] > this->data[b]) return 1;
    if (this->data[a] == this->data[b]) return 0;
    return -1;
}
int Heap_max_compare_node(Heap* this, int a, int b) {
    // a < b => 1, a == b => 0, a > b => -1
    if (this->data[a] < this->data[b]) return 1;
    if (this->data[a] == this->data[b]) return 0;
    return -1;
}
int Heap_sort_from_bottom(Heap* this, int s_idx) {
    if (s_idx == 1) return 0;
    int parent_idx = s_idx / 2;
    if (this->cmp(this, parent_idx, s_idx) == 1) {
        // parent is bigger -> swap
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
        // left child exists
        parent = this->data[s_idx];
        l = this->data[l_idx];
        if (r_idx <= this->n) {  // right child exists
            r = this->data[r_idx];
            if (this->cmp(this, s_idx, l_idx) == 1 &&
                this->cmp(this, s_idx, r_idx) == 1) {
                // both children are smaller
                if (this->cmp(this, r_idx, l_idx) >= 0)
                    swap = 1;  // swap with left child
                else
                    swap = 2;  // swap with right child
            } else if (this->cmp(this, s_idx, l_idx) == 1) {
                // only left child is smaller
                swap = 1;  // swap with left child
            } else if (this->cmp(this, s_idx, r_idx) == 1) {
                // only right child is smaller
                swap = 2;  // swap with right child
            }
        } else {
            if (this->cmp(this, s_idx, l_idx) == 1)
                swap = 1;  // swap with left child
        }
    }
    switch (swap) {
        case 0:  // do nothing
            break;
        case 1:  // swap with left child
            this->data[l_idx] = parent;
            this->data[s_idx] = l;
            Heap_sort_from_top(this, l_idx);
            break;
        case 2:  // swap with right child
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
    Node* temp = this->data;
    this->data = (Node*)malloc(sizeof(Node) * new_cap);
    for (int i = 0; i < this->n; i++) this->data[i] = temp[i];
    free(temp);
    return 0;
}