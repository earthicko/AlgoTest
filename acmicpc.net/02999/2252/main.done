#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define N_MAX 32000
#define M_MAX 100000
typedef int Item;
typedef struct List {
    int n, cap;
    Item* items;
    int (*append)(struct List*, Item);
    int (*resize)(struct List*, int);
} List;
List* List__init__(int cap_);
int List__del__(List* del);
int List_resize(List* this, int cap_);
int List_append(List* this, Item new);

int N, M;
List* EDGE[N_MAX];
int VISITED[N_MAX];
List* result;

int do_dfs(int s);

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) EDGE[i] = List__init__(4);
    for (int m = 0; m < M; m++) {
        int s, e;
        scanf("%d %d", &s, &e);
        EDGE[s - 1]->append(EDGE[s - 1], e - 1);
    }
    result = List__init__(N);
    for (int i = 0; i < N; i++)
        if (!VISITED[i]) do_dfs(i);
    for (int i = result->n - 1; i >= 0; i--)
        printf("%d ", result->items[i] + 1);
    return 0;
}

int do_dfs(int s) {
    VISITED[s] = 1;
    for (int i = 0; i < EDGE[s]->n; i++)
        if (!VISITED[EDGE[s]->items[i]]) do_dfs(EDGE[s]->items[i]);
    result->append(result, s);
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