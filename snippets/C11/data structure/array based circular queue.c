#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef int Item;

typedef struct Queue {
    int n, cap;
    int head, tail;
    Item* items;
} Queue;

Queue* Queue__init__(int cap_);
int Queue__del__(Queue* this);
int Queue_push(Queue* this, Item item);
Item Queue_pop(Queue* this);
Item Queue_peek(Queue* this);

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
