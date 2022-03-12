#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Item {
    int data;
} Item;

typedef struct Stack {
    int n, cap;
    Item* items;
    int (*push)(struct Stack*, Item);
    Item (*pop)(struct Stack*);
    Item (*peek)(struct Stack*);
} Stack;

Stack* Stack__init__(int cap_);
int Stack__del__(Stack* del);
int Stack_resize(Stack* this, int cap_);
int Stack_push(Stack* this, Item new);
Item Stack_pop(Stack* this);
Item Stack_peek(Stack* this);

Stack* Stack__init__(int cap_) {
    Stack* new = (Stack*)malloc(sizeof(Stack));
    new->n = 0;
    new->cap = cap_;
    new->items = (Item*)malloc(sizeof(Item) * cap_);
    new->push = Stack_push;
    new->pop = Stack_pop;
    new->peek = Stack_peek;
    return new;
}
int Stack__del__(Stack* del) {
    free(del->items);
    free(del);
    return 0;
}
int Stack_resize(Stack* this, int cap_) {
    Item* temp = this->items;
    this->items = (Item*)malloc(sizeof(Item) * cap_);
    int copy_max = (this->n < cap_) ? this->n : cap_;
    for (int i = 0; i < copy_max; i++) this->items[i] = temp[i];
    free(temp);
    return 0;
}
int Stack_push(Stack* this, Item new) {
    if (this->n == this->cap) Stack_resize(this, this->cap * 2);
    this->items[this->n++] = new;
    return 0;
}
Item Stack_pop(Stack* this) {
    assert(this->n > 0);
    Item output = this->items[this->n-- - 1];
    return output;
}
Item Stack_peek(Stack* this) {
    assert(this->n > 0);
    return this->items[this->n - 1];
}