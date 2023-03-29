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
typedef int Item;
typedef struct Queue {
    int n, cap, head;
    Item* items;
    int (*push)(struct Queue*, Item);
    Item (*pop)(struct Queue*);
    Item (*peek)(struct Queue*);
} Queue;
Queue* Queue__init__(int cap_);
int Queue__del__(Queue* this);
int Queue_push(Queue* this, Item item);
Item Queue_pop(Queue* this);
Item Queue_peek(Queue* this);
int Queue_resize(Queue* this, int cap_);

int N, M;
List* EDGE[N_MAX];
int IN_DEGREE[N_MAX], VISITED[N_MAX];
List* result;

int do_bfs();

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) EDGE[i] = List__init__(4);
    for (int m = 0; m < M; m++) {
        int s, e;
        scanf("%d %d", &s, &e);
        EDGE[s - 1]->append(EDGE[s - 1], e - 1);
        IN_DEGREE[e - 1]++;
    }
    result = List__init__(N);
    do_bfs();
    for (int i = 0; i < result->n; i++) printf("%d ", result->items[i] + 1);
    return 0;
}

int do_bfs() {
    Queue* q = Queue__init__(M_MAX);
    for (int i = 0; i < N; i++)
        if (IN_DEGREE[i] == 0) {
            // printf("Begin BFS from %d\n", i + 1);
            q->push(q, i);
            VISITED[i] = 1;
        }
    while (q->n > 0) {
        int here = q->pop(q);
        result->append(result, here);
        // printf("Reached %d, appended\n", here + 1);
        for (int i = 0; i < EDGE[here]->n; i++) {
            int there = EDGE[here]->items[i];
            if (VISITED[there]) continue;
            // printf("Can go to %d\n", there + 1);
            if (IN_DEGREE[there] > 0) IN_DEGREE[there]--;
            if (IN_DEGREE[there] == 0) {
                // printf("Pushed %d\n", there + 1);
                q->push(q, there);
                VISITED[there] = 1;
            }
        }
    }
    Queue__del__(q);
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
Queue* Queue__init__(int cap_) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->n = 0;
    queue->cap = cap_;
    queue->head = 0;
    queue->items = (Item*)malloc(sizeof(Item) * cap_);
    queue->push = Queue_push;
    queue->pop = Queue_pop;
    queue->peek = Queue_peek;
    return queue;
}
int Queue__del__(Queue* this) {
    free(this->items);
    free(this);
    return 0;
}
int Queue_push(Queue* this, Item item) {
    // assert(this->n < this->cap);
    if (this->n == this->cap) Queue_resize(this, this->cap * 2);
    this->n++;
    this->items[(this->head + this->n) % this->cap] = item;
    return 0;
}
Item Queue_pop(Queue* this) {
    assert(this->n > 0);
    this->head = (this->head + 1) % this->cap;
    this->n--;
    return this->items[this->head];
}
Item Queue_peek(Queue* this) {
    return this->items[(this->head + 1) % this->cap];
}
int Queue_resize(Queue* this, int cap_) {
    Item* linear = (Item*)malloc(sizeof(Item) * this->n);
    for (int i = 0; i < this->n; i++)
        linear[i] = this->items[(this->head + i + 1) % this->cap];
    free(this->items);
    this->items = (Item*)malloc(sizeof(Item) * cap_);
    for (int i = 0; i < this->n; i++) this->items[i] = linear[i];
    free(linear);
    this->head = cap_ - 1;
    this->cap = cap_;
    return 0;
}