#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef int Node;
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

#define N_MAX 500
#define M_MAX 6000

int N, M;
long MIN_COST[N_MAX];
int N_EDGE[N_MAX];
int EDGE[N_MAX][M_MAX][2];  // 24MB
int IN_QUEUE[N_MAX], N_CYCLE[N_MAX];

Queue* Queue__init__();
int Queue__del__(Queue* this);
int Queue_push(Queue* this, Node new_val);
Node Queue_pop(Queue* this);

int do_spfa();

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) MIN_COST[i] = LONG_MAX;
    for (int m = 0; m < M; m++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        EDGE[a - 1][N_EDGE[a - 1]][0] = b - 1;
        EDGE[a - 1][N_EDGE[a - 1]][1] = c;
        N_EDGE[a - 1]++;
    }

    int negative_cycle = do_spfa();
    if (negative_cycle) {
        printf("-1\n");
    } else {
        for (int i = 1; i < N; i++) {
            if (MIN_COST[i] == LONG_MAX)
                printf("-1\n");
            else
                printf("%ld\n", MIN_COST[i]);
        }
    }

    return 0;
}

int do_spfa() {
    Queue* queue = Queue__init__();

    MIN_COST[0] = 0;
    queue->push(queue, 0);
    IN_QUEUE[0] = 1;
    N_CYCLE[0]++;

    while (queue->size > 0) {
        Node here = queue->pop(queue);
        IN_QUEUE[here] = 0;

        for (int e_i = 0; e_i < N_EDGE[here]; e_i++) {
            Node there = EDGE[here][e_i][0];
            int cost = EDGE[here][e_i][1];
            if (MIN_COST[there] > MIN_COST[here] + cost) {
                MIN_COST[there] = MIN_COST[here] + cost;
                if (!IN_QUEUE[there]) {
                    N_CYCLE[there]++;
                    if (N_CYCLE[there] >= N) {
                        Queue__del__(queue);
                        return 1;
                    }
                    queue->push(queue, there);
                    IN_QUEUE[there] = 1;
                }
            }
        }
    }
    return 0;
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
