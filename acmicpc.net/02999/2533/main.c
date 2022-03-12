#include <stdio.h>
#include <stdlib.h>
#define min(a, b)               \
    ({                          \
        __typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        _a < _b ? _a : _b;      \
    })
#define N_MAX 1000000
typedef int Item;
typedef struct List {
    int s;
    int n, cap;
    Item* items;
} List;
List* List__init__(int cap_);
int List__del__(List* del);
int List_resize(List* this, int cap_);
int List_append(List* this, Item new);
int List_insert(List* this, Item new, int idx);
Item List_pop(List* this, int idx);
Item List_peek(List* this, int idx);

int N;
List* CONN[N_MAX];
// [i][0]: i가 EA일 경우 [i][1]: 아닐 경우
int MIN_EA[N_MAX][2];

int cmp(const void* a, const void* b);
int do_dp(int s, int state, int prev);

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        CONN[i] = List__init__(2);
        CONN[i]->s = i;
    }
    for (int i = 0; i < N - 1; i++) {
        int s, e;
        scanf("%d %d", &s, &e);
        List_append(CONN[s - 1], e - 1);
        List_append(CONN[e - 1], s - 1);
    }
    for (int i = 0; i < N; i++) {
        MIN_EA[i][0] = -1;
        MIN_EA[i][1] = -1;
    }
    do_dp(0, 0, -1);
    do_dp(0, 1, -1);
    printf("%d", min(MIN_EA[0][0], MIN_EA[0][1]));

    return 0;
}

int do_dp(int s, int state, int prev) {
    if (MIN_EA[s][state] != -1) return MIN_EA[s][state];
    int sum;
    if (state) {
        sum = 0;
        for (int i = 0; i < CONN[s]->n; i++) {
            if (CONN[s]->items[i] == prev) continue;
            sum += do_dp(CONN[s]->items[i], 0, s);
        }
    } else {
        sum = 1;
        for (int i = 0; i < CONN[s]->n; i++) {
            if (CONN[s]->items[i] == prev) continue;
            int min_val = min(do_dp(CONN[s]->items[i], 0, s),
                              do_dp(CONN[s]->items[i], 1, s));
            sum += min_val;
        }
    }
    MIN_EA[s][state] = sum;
    return MIN_EA[s][state];
}

int cmp(const void* a, const void* b) {
    if ((*(List**)a)->n < (*(List**)b)->n) return 1;
    if ((*(List**)a)->n > (*(List**)b)->n) return -1;
    return 0;
}

List* List__init__(int cap_) {
    List* new = (List*)malloc(sizeof(List));
    new->n = 0;
    new->cap = cap_;
    new->items = (Item*)malloc(sizeof(Item) * cap_);
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
    if (this->n == this->cap) List_resize(this, this->cap * 2);
    this->items[this->n] = new;
    this->n++;
    return 0;
}