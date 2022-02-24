#include <stdio.h>
#include <stdlib.h>

typedef struct item {
    int data;
} item;

typedef struct list {
    int n, cap;
    item* items;
    int (*append)(struct list*, item);
    int (*insert)(struct list*, item, int);
    item (*pop)(struct list*, int);
    item (*peek)(struct list*, int);
    int (*resize)(struct list*, int);
} list;

list* list_(int cap_);
int list__(list* del);
int resize_list(list* this, int cap_);
int append_to_list(list* this, item new);
int insert_to_list(list* this, item new, int idx);
item pop_from_list(list* this, int idx);
item peek_from_list(list* this, int idx);

list* list_(int cap_) {
    list* new = (list*)malloc(sizeof(list));
    new->n = 0;
    new->cap = cap_;
    new->items = (item*)malloc(sizeof(item) * cap_);
    new->append = append_to_list;
    new->insert = insert_to_list;
    new->pop = pop_from_list;
    new->peek = peek_from_list;
    new->resize = resize_list;
    return new;
}
int list__(list* del) {
    free(del->items);
    free(del);
    return 0;
}
int resize_list(list* this, int cap_) {
    item* temp = this->items;
    this->items = (item*)malloc(sizeof(item) * cap_);
    int copy_max = (this->n < cap_) ? this->n : cap_;
    for (int i = 0; i < copy_max; i++) this->items[i] = temp[i];
    free(temp);
    return 0;
}
int append_to_list(list* this, item new) {
    if (this->n == this->cap) this->resize(this, this->cap * 2);
    this->items[this->n] = new;
    this->n++;
    return 0;
}
int insert_to_list(list* this, item new, int idx) {
    if (this->n == this->cap) this->resize(this, this->cap * 2);
    idx = idx % this->n;
    for (int i = this->n - 1; i >= idx; i--)
        this->items[i + 1] = this->items[i];
    this->items[idx] = new;
    this->n++;
    return 0;
}
item pop_from_list(list* this, int idx) {
    idx = idx % this->n;
    item output = this->items[idx];
    this->n--;
    for (int i = idx; i < this->n; i++) this->items[i] = this->items[i + 1];
    return output;
}
item peek_from_list(list* this, int idx) {
    idx = idx % this->n;
    return this->items[idx];
}