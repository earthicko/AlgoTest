#include <stdio.h>
#include <stdlib.h>

typedef struct queue_node {
    int data;
    struct queue_node* prev;
} queue_node;

typedef struct queue {
    queue_node* head;
    queue_node* tail;
    int size;
} queue;

queue* queue_(int first_val) {
    queue* new_queue = (queue*)malloc(sizeof(queue));
    queue_node* first_node = (queue_node*)malloc(sizeof(queue_node));
    first_node->data = first_val;
    first_node->prev = NULL;

    new_queue->head = first_node;
    new_queue->tail = first_node;
    new_queue->size = 1;
    return new_queue;
}

int push_queue(int new_val, queue* target) {
    queue_node* new_node = (queue_node*)malloc(sizeof(queue_node));

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

int pop_queue(queue* target) {
    if (target->size == 0) return -69420;
    int return_val = target->head->data;
    queue_node* deleted = target->head;
    target->head = target->head->prev;
    free(deleted);
    target->size--;
    return return_val;
}

int print_queue(queue* target) {
    printf("Queue size: %d\n", target->size);
    queue_node* cursor = target->head;
    while (cursor) {
        printf("%d ", cursor->data);
        cursor = cursor->prev;
    }
    printf("\n");
    return 0;
}

int main() {
    queue* kueue = queue_(777);

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