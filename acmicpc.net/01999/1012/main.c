#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE_MAX 50
typedef struct Item {
    int m, n;
} Item;
typedef struct Queue {
    int n, cap;
    int head, tail;
    Item* items;
} Queue;
int MAP[SIZE_MAX][SIZE_MAX];
Queue* Queue__init__(int cap_);
int Queue__del__(Queue* this);
int Queue_push(Queue* this, Item item);
Item Queue_pop(Queue* this);
Item Queue_peek(Queue* this);
int print_map();
int do_bfs(int m, int n);
int T, M, N, K;
Item DIR[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int main() {
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        scanf("%d %d %d", &M, &N, &K);
        for (int k = 0; k < K; k++) {
            int m, n;
            scanf("%d %d", &m, &n);
            MAP[m][n] = 1;
        }
        // print_map();
        int count = 0;
        for (int m = 0; m < M; m++) {
            for (int n = 0; n < N; n++) {
                if (MAP[m][n] == 1) {
                    do_bfs(m, n);
                    count++;
                    // print_map();
                }
            }
        }
        printf("%d\n", count);
    }
    return 0;
}
int print_map() {
    for (int n = 0; n < N; n++) {
        for (int m = 0; m < M; m++) printf("%d ", MAP[m][n]);
        printf("\n");
    }
    printf("=================================\n");
    return 0;
}
int do_bfs(int m, int n) {
    Queue* queue = Queue__init__(2500);
    Item start = {m, n};
    MAP[m][n] = 0;
    Queue_push(queue, start);
    while (queue->n > 0) {
        Item here = Queue_pop(queue);
        for (int i = 0; i < 4; i++) {
            Item there = {here.m + DIR[i].m, here.n + DIR[i].n};
            if (there.m < 0 || there.m >= M || there.n < 0 || there.n >= N)
                continue;
            if (MAP[there.m][there.n] == 0) continue;
            MAP[there.m][there.n] = 0;
            Queue_push(queue, there);
        }
    }
    return 0;
}
Queue* Queue__init__(int cap_) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->n = 0;
    queue->cap = cap_;
    queue->head = 0;
    queue->tail = 0;
    queue->items = (Item*)malloc(sizeof(Item) * cap_);
    return queue;
}
int Queue__del__(Queue* this) {
    free(this->items);
    free(this);
    return 0;
}
int Queue_push(Queue* this, Item item) {
    assert(this->n < this->cap);
    this->tail = (this->tail + 1) % this->cap;
    this->items[this->tail] = item;
    this->n++;
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
