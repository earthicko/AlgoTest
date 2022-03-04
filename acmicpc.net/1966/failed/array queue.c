#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define N_MAX 100

typedef struct Item {
    int i, priority;
} Item;
typedef struct Queue {
    int n, cap;
    int head, tail;
    Item* items;
} Queue;

int static compare(const void* first, const void* second);
Queue* Queue__init__(int cap_);
int Queue__del__(Queue* this);
int Queue_push(Queue* this, Item item);
Item Queue_pop(Queue* this);

int main() {
    int n_cases;
    scanf("%d", &n_cases);
    for (int i = 0; i < n_cases; i++) {
        int n, m;
        scanf("%d %d", &n, &m);
        Queue* queue = Queue__init__(N_MAX);
        int priorities[N_MAX];
        for (int j = 0; j < n; j++) {
            Item doc;
            scanf("%d", &doc.priority);
            doc.i = j;
            Queue_push(queue, doc);
            priorities[j] = doc.priority;
        }
        qsort(priorities, n, sizeof(int), compare);

        int counter = 1;
        int i_max_p = 0;

        while (queue->n > 0) {
            Item doc = Queue_pop(queue);
            if (doc.priority == priorities[i_max_p]) {
                if (doc.i == m) break;
                counter++;
                i_max_p++;
            } else {
                Queue_push(queue, doc);
            }
        }
        Queue__del__(queue);

        printf("%d\n", counter);
    }
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
    this->tail++;
    if (this->tail == this->cap) this->tail = 0;
    this->items[this->tail] = item;
    this->n++;
    return 0;
}
Item Queue_pop(Queue* this) {
    assert(this->n > 0);
    this->head++;
    if (this->head == this->cap) this->head = 0;
    this->n--;
    return this->items[this->head];
}

int static compare(const void* first, const void* second) {
    if (*(int*)first < *(int*)second)
        return 1;
    else if (*(int*)first > *(int*)second)
        return -1;
    else
        return 0;
}
