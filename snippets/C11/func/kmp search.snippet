#include <stdio.h>
#include <stdlib.h>
#define L_MAX 1000001

typedef int Item;
typedef struct List {
    int n, cap;
    Item* items;
} List;
List* List__init__(int cap_);
int List__del__(List* del);
int List_resize(List* this, int cap_);
int List_append(List* this, Item new);

int L_T, L_P;
char T[L_MAX], P[L_MAX];

List* search_string(char* str, char* pattern, int l_str, int l_pattern);

int main() {
    for (L_T = 0; L_T < L_MAX; L_T++) {
        scanf("%c", &T[L_T]);
        if (T[L_T] == '\n') break;
    }
    for (L_P = 0; L_P < L_MAX; L_P++) {
        scanf("%c", &P[L_P]);
        if (P[L_P] == '\n') break;
    }

    List* match = search_string(T, P, L_T, L_P);
    printf("%d\n", match->n);
    for (int i = 0; i < match->n; i++) printf("%d\n", match->items[i]);

    return 0;
}

int* build_transition_table(char* pattern, int l_pattern) {
    int* table = (int*)malloc(sizeof(int) * (l_pattern + 1));
    for (int i = 0; i < l_pattern + 1; i++) table[i] = 0;
    int i = -1, j = 0;
    table[j] = i;
    while (j < l_pattern) {
        if (i == -1 || pattern[i] == pattern[j]) {
            i++, j++;
            table[j] = i;
        } else {
            i = table[i];
        }
    }
    return table;
}

List* search_string(char* str, char* pattern, int l_str, int l_pattern) {
    List* match = List__init__(L_MAX);
    int* table = build_transition_table(pattern, l_pattern);
    int i = 0, j = 0;
    while (i < l_str) {
        if (j == -1 || str[i] == pattern[j]) {
            i++, j++;
        } else {
            j = table[j];
        }
        if (j == l_pattern) {
            List_append(match, i - l_pattern + 1);
            j = table[j];
        }
    }
    free(table);
    return match;
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