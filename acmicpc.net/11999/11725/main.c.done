#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define N_MAX 100000
#define ARRAY_SIZE 10

typedef int Item;
typedef struct List {
    int n, cap;
    Item* items;
    int (*append)(struct List*, Item);
    int (*insert)(struct List*, Item, int);
    Item (*pop)(struct List*, int);
    Item (*peek)(struct List*, int);
    int (*resize)(struct List*, int);
} List;

int N;
List* TREE[N_MAX];
int PARENT[N_MAX];
int VISITED[N_MAX];

List* List__init__(int cap_);
int List__del__(List* del);
int List_resize(List* this, int cap_);
int List_append(List* this, Item new);
int List_insert(List* this, Item new, int idx);
Item List_pop(List* this, int idx);
Item List_peek(List* this, int idx);

int do_dfs(int n);

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) TREE[i] = List__init__(ARRAY_SIZE);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        TREE[a - 1]->append(TREE[a - 1], b - 1);
        TREE[b - 1]->append(TREE[b - 1], a - 1);
    }
    do_dfs(0);
    for (int i = 1; i < N; i++) printf("%d\n", PARENT[i] + 1);
    return 0;
}

int do_dfs(int n) {
    VISITED[n] = 1;
    for (int i = 0; i < TREE[n]->n; i++) {
        int there = TREE[n]->items[i];
        if (VISITED[there]) continue;
        VISITED[there] = 1;
        PARENT[there] = n;
        do_dfs(there);
    }
    return 0;
}

List* List__init__(int cap_) {
    List* new = (List*)malloc(sizeof(List));
    new->n = 0;
    new->cap = cap_;
    new->items = (Item*)malloc(sizeof(Item) * cap_);
    new->append = List_append;
    new->insert = List_insert;
    new->pop = List_pop;
    new->peek = List_peek;
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
    int copy_max = (this->n < cap_) ? this->n : cap_;
    for (int i = 0; i < copy_max; i++) this->items[i] = temp[i];
    free(temp);
    return 0;
}
int List_append(List* this, Item new) {
    if (this->n == this->cap) this->resize(this, this->cap * 2);
    this->items[this->n] = new;
    this->n++;
    return 0;
}
int List_insert(List* this, Item new, int idx) {
    if (this->n == this->cap) this->resize(this, this->cap * 2);
    idx = idx % this->n;
    for (int i = this->n - 1; i >= idx; i--)
        this->items[i + 1] = this->items[i];
    this->items[idx] = new;
    this->n++;
    return 0;
}
Item List_pop(List* this, int idx) {
    idx = idx % this->n;
    Item output = this->items[idx];
    this->n--;
    for (int i = idx; i < this->n; i++) this->items[i] = this->items[i + 1];
    return output;
}
Item List_peek(List* this, int idx) {
    idx = idx % this->n;
    return this->items[idx];
}