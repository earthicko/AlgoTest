#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef char Item;
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

int main() {
    while (1) {
        char line[101];
        int size = 1;
        for (int i = 0; i < 101; i++, size++) {
            scanf("%c", &line[i]);
            if (line[i] == '\n') break;
        }
        if (line[0] == '.') break;

        Stack* stack = Stack__init__(100);
        int balanced = 1;
        for (int i = 0; i < size; i++) {
            int command = 0;  // 0:skip, 1:push, 2:pop, 3:endl
            switch (line[i]) {
                case '(':
                    command = 1;
                    break;
                case '[':
                    command = 1;
                    break;
                case ')':
                    command = 2;
                    break;
                case ']':
                    command = 2;
                    break;
                case '.':
                    command = 3;
                    break;
                default:
                    break;
            }

            switch (command) {
                case 1:
                    stack->push(stack, line[i]);
                    break;
                case 2:
                    if (stack->n > 0) {
                        char c = stack->pop(stack);
                        if (c == '(' && line[i] == ')') {
                        } else if (c == '[' && line[i] == ']') {
                        } else {
                            balanced = 0;
                        }
                    } else {
                        balanced = 0;
                    }
                    break;
                default:
                    break;
            }
            if (!balanced) break;
        }
        if (stack->n > 0) balanced = 0;
        Stack__del__(stack);
        if (balanced)
            printf("yes\n");
        else
            printf("no\n");
    }
    return 0;
}

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