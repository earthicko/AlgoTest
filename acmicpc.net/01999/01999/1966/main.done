#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define N_MAX 100

typedef struct Node {
    int i, priority;
} Node;
typedef struct Queue_Node {
    Node data;
    struct Queue_Node* prev;
} Queue_Node;
typedef struct Queue {
    int (*push)(struct Queue*, Node);
    Node (*pop)(struct Queue*);
    Queue_Node* head;
    Queue_Node* tail;
    int size;
} Queue;

int static compare(const void* first, const void* second);
Queue* Queue__init__();
int Queue__del__(Queue* this);
int Queue_push(Queue* this, Node new_val);
Node Queue_pop(Queue* this);

int main() {
    int n_cases;
    scanf("%d", &n_cases);
    for (int i = 0; i < n_cases; i++) {
        int n, m;
        scanf("%d %d", &n, &m);
        Queue* queue = Queue__init__(N_MAX);
        int priorities[N_MAX];
        for (int j = 0; j < n; j++) {
            // assert(j < N_MAX);
            Node doc;
            scanf("%d", &doc.priority);
            doc.i = j;
            Queue_push(queue, doc);
            priorities[j] = doc.priority;
        }
        qsort(priorities, n, sizeof(int), compare);

        int counter = 1;
        int i_max_p = 0;

        while (queue->size > 0) {
            Node doc = Queue_pop(queue);
            assert(i_max_p < N_MAX);

            // int is_max_priority = 1;
            // for (int k = queue->head;;) {
            //     k++;
            //     if (k == queue->cap) k = 0;
            //     // printf("Compare %d <-> %d\n", queue->items[k].priority,
            //     //        doc.priority);
            //     if (queue->items[k].priority > doc.priority) {
            //         is_max_priority = 0;
            //         break;
            //     }
            //     if (k == queue->tail) break;
            // }
            // if (is_max_priority) {
            if (doc.priority == priorities[i_max_p]) {
                // printf("Print->%dth doc is max\n", doc.priority);
                if (doc.i == m) break;
                counter++;
                i_max_p++;
            } else {
                // printf("Push->%dth doc is not max\n", doc.priority);
                Queue_push(queue, doc);
            }
        }
        Queue__del__(queue);

        printf("%d\n", counter);
    }
}

Queue* Queue__init__() {
    Queue* new_queue = (Queue*)malloc(sizeof(Queue));
    new_queue->push = Queue_push;
    new_queue->pop = Queue_pop;
    new_queue->head = NULL;
    new_queue->tail = NULL;
    new_queue->size = 0;
    return new_queue;
}
int Queue__del__(Queue* this) {
    Queue_Node* cursor = this->head;
    while (cursor != NULL) {
        Queue_Node* temp = cursor;
        cursor = cursor->prev;
        free(temp);
    }
    free(this);
}
int Queue_push(Queue* this, Node new_val) {
    Queue_Node* new_node = (Queue_Node*)malloc(sizeof(Queue_Node));
    if (this->size == 0)
        this->head = new_node;
    else
        this->tail->prev = new_node;
    this->tail = new_node;
    this->size++;
    new_node->data = new_val;
    new_node->prev = NULL;
    return 0;
}
Node Queue_pop(Queue* this) {
    assert(this->size > 0);
    Node return_val = this->head->data;
    Queue_Node* deleted = this->head;
    this->head = this->head->prev;
    free(deleted);
    this->size--;
    return return_val;
}
int static compare(const void* first, const void* second) {
    if (*(int*)first < *(int*)second)
        return 1;
    else if (*(int*)first > *(int*)second)
        return -1;
    else
        return 0;
}
