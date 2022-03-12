#include <stdio.h>
#include <stdlib.h>

typedef struct Set {
    int* container;
    int n, mod, cap;
} Set;

Set* Set__init__(int n_);
int Set__del__(Set* this);
int Set_realloc(Set* this, int n_);
int Set_add(Set* this, int i);
int Set_remove(Set* this, int i);
int Set_check(Set* this, int i);
int Set_toggle(Set* this, int i);
int Set_set_all(Set* this, int i);

Set* Set__init__(int n_) {
    Set* this = malloc(sizeof(Set));
    this->container = calloc(n_, sizeof(int));
    this->n = n_;
    this->mod = sizeof(int) * 8;
    this->cap = n_ * this->mod;
    return this;
}
int Set__del__(Set* this) {
    free(this->container);
    free(this);
    return 0;
}
int Set_realloc(Set* this, int n_) {
    this->container = realloc(this->container, n_);
    this->n = n_;
    this->cap = n_ * this->mod;
    return 0;
}
int Set_add(Set* this, int i) {
    if (this->cap <= i) Set_realloc(this, i / this->mod + 1);
    this->container[i / this->mod] |= (1 << (i % this->mod));
    return 0;
}
int Set_remove(Set* this, int i) {
    if (this->cap <= i) Set_realloc(this, i / this->mod + 1);
    this->container[i / this->mod] &= ~(1 << (i % this->mod));
    return 0;
}
int Set_check(Set* this, int i) {
    if (this->cap <= i) Set_realloc(this, i / this->mod + 1);
    if (this->container[i / this->mod] & (1 << (i % this->mod)))
        return 1;
    else
        return 0;
}
int Set_toggle(Set* this, int i) {
    if (this->cap <= i) Set_realloc(this, i / this->mod + 1);
    this->container[i / this->mod] ^= (1 << (i % this->mod));
    return 0;
}
int Set_set_all(Set* this, int i) {
    if (i == 1) i = ~0;
    for (int j = 0; j < this->n; j++) this->container[j] = i;
    return 0;
}