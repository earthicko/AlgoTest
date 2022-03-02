#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
typedef int Item;

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
    int n;
    scanf("%d", &n);
    int target[100000];
    Stack* stack = Stack__init__(100000);
    Stack* commands = Stack__init__(200000);
    for (int i = 0; i < n; i++) {
        scanf("%d", target + i);
    }
    int source = 1;
    int target_i = 0;
    while (target_i < n) {
        // if empty -> push until (+)
        // if peek = target -> pop (-)
        // if target >= source -> push until
        char command = 0;
        if (stack->n == 0)
            command = '+';
        else if (stack->peek(stack) == target[target_i])
            command = '-';
        else if (target[target_i] >= source)
            command = '+';
        else {
            printf("NO\n");
            return 0;
        }
        switch (command) {
            case '+':
                while (target[target_i] >= source) {
                    stack->push(stack, source++);
                    commands->push(commands, '+');
                }
                break;
            case '-':
                stack->pop(stack);
                target_i++;
                commands->push(commands, '-');
                break;
            default:
                break;
        }
    }
    for (int i = 0; i < commands->n; i++) printf("%c\n", commands->items[i]);
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