#include <stdio.h>
#include <stdlib.h>

typedef struct Item {
    int data;
} Item;

typedef struct List {
    int n, cap;
    Item* items;
    int (*append)(struct List*, Item);
    int (*insert)(struct List*, Item, int);
    Item (*pop)(struct List*, int);
    Item (*peek)(struct List*, int);
    int (*resize)(struct List*, int);
} List;

List* List__init__(int cap_);
int List__del__(List* del);
int List_resize(List* this, int cap_);
int List_append(List* this, Item new);
int List_insert(List* this, Item new, int idx);
Item List_pop(List* this, int idx);
Item List_peek(List* this, int idx);

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