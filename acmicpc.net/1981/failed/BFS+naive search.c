#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define N_MAX 100

typedef struct Node {
    int x, y;
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

int N;
int MAP[N_MAX][N_MAX];  // 40KB
Node DIR[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

Queue* Queue__init__();
int Queue__del__(Queue* this);
int Queue_push(Queue* this, Node new_val);
Node Queue_pop(Queue* this);

int solve();
int get_map_continuity(int max, int min);

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) scanf("%d", &(MAP[i][j]));
    }
    solve();

    return 0;
}

int solve() {
    int max = (MAP[0][0] > MAP[N - 1][N - 1]) ? MAP[0][0] : MAP[N - 1][N - 1];
    int min = (MAP[0][0] < MAP[N - 1][N - 1]) ? MAP[0][0] : MAP[N - 1][N - 1];
    int shifter = 0;
    while (1) {
#ifndef ONLINE_JUDGE
        printf("%d to %d\n", max, min);
#endif
        if (get_map_continuity(max, min)) {
            printf("%d\n", max - min);
            break;
        }
        shifter = shifter ^ 1;
        if (shifter)
            min--;
        else
            max++;
        if (min < 0) min++;
        if (max > 200) max--;
    }
    return 0;
}

// int get_map_continuity(int max, int min) {
//     Queue* queue = Queue__init__();
//     int visited[N_MAX][N_MAX];
//     for (int x = 0; x < N; x++) {
//         for (int y = 0; y < N; y++) {
//             if (MAP[x][y] > max || MAP[x][y] < min)
//                 visited[x][y] = 1;
//             else
//                 visited[x][y] = 0;
//         }
//     }
//     Node start = {0, 0};
//     queue->push(queue, start);
//     while (queue->size > 0) {
//         Node here = queue->pop(queue);
//
//         if (visited[here.x][here.y]) continue;
//         visited[here.x][here.y] = 1;
//
//         if (here.x == N - 1 && here.y == N - 1) {
//             Queue__del__(queue);
//             return 1;
//         }
//
//         for (int dir = 0; dir < 4; dir++) {
//             Node there = {here.x + DIR[dir].x, here.y + DIR[dir].y};
//             if (0 <= there.x && there.x < N && 0 <= there.y && there.y < N)
//                 queue->push(queue, there);
//         }
//     }
//     Queue__del__(queue);
//     return 0;
// }

int get_map_continuity(int max, int min) {
    int visited[N_MAX][N_MAX];
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            visited[x][y] = 0;
        }
    }
    Queue* queue = Queue__init__();
    Node start = {0, 0};
    queue->push(queue, start);
    visited[0][0] = 1;
    while (queue->size > 0) {
        Node here = queue->pop(queue);
        if (here.x == N - 1 && here.y == N - 1) {
            Queue__del__(queue);
            return 1;
        }
        for (int i = 0; i < 4; i++) {
            Node there;
            there.x = here.x + DIR[i].x;
            there.y = here.y + DIR[i].y;
            if (there.x < 0 || there.x > N - 1 || there.y < 0 ||
                there.y > N - 1 || visited[there.x][there.y])
                continue;
            if (MAP[there.x][there.y] < min || MAP[there.x][there.y] > max)
                continue;
            visited[there.x][there.y] = 1;
            queue->push(queue, there);
        }
    }
    Queue__del__(queue);
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
