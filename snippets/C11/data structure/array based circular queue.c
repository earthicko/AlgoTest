#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
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