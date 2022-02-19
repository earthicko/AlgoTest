#include <stdio.h>
#include <stdlib.h>

struct queue_node {
    int data;
    struct queue_node* prev;
};

struct queue {
    struct queue_node* head;
    struct queue_node* tail;
    int size;
};

struct queue* construct_queue(int first_val) {
    struct queue* new_queue = (struct queue*)malloc(sizeof(struct queue));
    struct queue_node* first_node =
        (struct queue_node*)malloc(sizeof(struct queue_node));
    first_node->data = first_val;
    first_node->prev = NULL;

    new_queue->head = first_node;
    new_queue->tail = first_node;
    new_queue->size = 1;
    return new_queue;
}

int push_queue(int new_val, struct queue* target) {
    struct queue_node* new_node =
        (struct queue_node*)malloc(sizeof(struct queue_node));

    if (target->size == 0) {
        target->head = new_node;
    } else {
        target->tail->prev = new_node;
    }
    target->tail = new_node;
    target->size++;

    new_node->data = new_val;
    new_node->prev = NULL;

    return 0;
}

int pop_queue(struct queue* target) {
    if (target->size == 0) return -69420;
    int return_val = target->head->data;
    struct queue_node* deleted = target->head;
    target->head = target->head->prev;
    free(deleted);
    target->size--;
    return return_val;
}

int print_queue(struct queue* target) {
    printf("Queue size: %d\n", target->size);
    struct queue_node* cursor = target->head;
    while (cursor) {
        printf("%d ", cursor->data);
        cursor = cursor->prev;
    }
    printf("\n");
    return 0;
}

int main() {
    struct queue* kueue = construct_queue(777);

    while (1) {
        printf("1: push | 2: pop <<<");
        char choice = getchar();

        int popped_val;
        switch (choice) {
            case '1':
                printf("Input new value: ");
                int new_val;
                scanf("%d", &new_val);
                push_queue(new_val, kueue);
                break;
            case '2':
                popped_val = pop_queue(kueue);
                printf("Popped: %d\n", popped_val);
                break;

            default:
                printf("Invalid input\n");
                break;
        }
        print_queue(kueue);
    }
}