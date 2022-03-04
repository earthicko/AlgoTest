/*
다익스트라 (코스트: 꺾임)

맵을 INF로 초기화
C 두개 중 한 칸에서 시작
우선순위 큐 (정렬 기준: 코스트)에 시작점을 푸시

큐가 빌 때까지:
    큐에서 노드 하나 pop
    노드에 저장된 방향의 CCW 90도, 0도, CW 90도 방향 좌표에 대해:
        out of bound시 패스
        벽일 시 패스
        0도: 코스트 그대로, CCW / CW: 코스트++
        좌표에 저장된 코스트 <-> 새 코스트 비교:
            새 코스트가 더 적을 시 갱신 수 큐에 push

다른 C 좌표의 값을 확인

필요 자료형
맵 char[100][100]
맵 크기 int
노드 {x방향, y방향, x좌표, y좌표 int}
우선순위 큐 (최소 힙)
*/
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAP_SIZE 100
#define QUEUE_SIZE 10000

typedef struct node {
    short dir_idx, x, y;
    int cost;
} node;

typedef struct heap {
    int (*bottom_sorter)(int, struct heap*);
    int (*top_sorter)(int, struct heap*);
    int last_index;         // index where last element is (0 when empty)
    node data[QUEUE_SIZE];  // 1: root / 2~3: level 1 / 4~7: level 2...
} heap;

int x_size, y_size;
char map[MAP_SIZE][MAP_SIZE];
int cost[MAP_SIZE][MAP_SIZE][4];
int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int sort_min_heap_from_bottom(int start_index, struct heap* target);
int sort_min_heap_from_top(int start_index, struct heap* target);
int put_heap(node new_val, struct heap* target);
node get_heap(struct heap* target);
int do_dijkstra(int x, int y);

int main() {
    scanf("%d %d", &x_size, &y_size);

    int x_target[2];
    int y_target[2];
    int i = 0;
    for (int y = y_size - 1; y >= 0; y--) {
        for (int x = 0; x < x_size; x++) {
            scanf(" %c", &(map[x][y]));
            if (map[x][y] == 'C') {
                x_target[i] = x;
                y_target[i] = y;
                i++;
            }
            for (int i = 0; i < 4; i++) cost[x][y][i] = INT_MAX;
        }
    }
    do_dijkstra(x_target[0], y_target[0]);

    // for (int y = y_size - 1; y >= 0; y--) {
    //     for (int x = 0; x < x_size; x++) {
    //         int min = INT_MAX;
    //         for (int i = 0; i < 4; i++)
    //             min = (cost[x][y][i] < min) ? cost[x][y][i] : min;
    //         if (min == INT_MAX)
    //             printf(" X ");
    //         else
    //             printf("%2d ", min);
    //     }
    //     printf("\n");
    // }
    int min = INT_MAX;
    for (int i = 0; i < 4; i++)
        min = (cost[x_target[1]][y_target[1]][i] < min)
                  ? cost[x_target[1]][y_target[1]][i]
                  : min;
    printf("%d\n", min);
}

int do_dijkstra(int x, int y) {
    heap* queue = (heap*)malloc(sizeof(heap));
    queue->bottom_sorter = sort_min_heap_from_bottom;
    queue->top_sorter = sort_min_heap_from_top;
    queue->last_index = 0;

    for (int i = 0; i < 4; i++) cost[x][y][i] = 0;
    node start[4];
    for (int i = 0; i < 4; i++) {
        start[i].x = x + dir[i][0];
        start[i].y = y + dir[i][1];
        if (start[i].x < 0 || start[i].x >= x_size || start[i].y < 0 ||
            start[i].y >= y_size)
            continue;
        if (map[start[i].x][start[i].y] == '*') continue;
        start[i].cost = 0;
        start[i].dir_idx = i;
        cost[start[i].x][start[i].y][i] = 0;
        put_heap(start[i], queue);
    }

    while (queue->last_index > 0) {
        node curr = get_heap(queue);
        for (short new_dir = 0; new_dir < 4; new_dir++) {
            int cost_d = 0;
            // 3 - 1 or 1 - 3 or 2 - 0 or 4 - 2 ...
            if ((curr.dir_idx - new_dir) % 4 == 2) continue;
            // 2 - 3 or 2 - 1 ...
            if ((curr.dir_idx - new_dir) % 4 != 0) cost_d = 1;
            node new;
            new.x = curr.x + dir[new_dir][0];
            new.y = curr.y + dir[new_dir][1];
            if (new.x < 0 || new.x >= x_size || new.y < 0 || new.y >= y_size)
                continue;
            if (map[new.x][new.y] == '*') continue;
            new.cost = curr.cost + cost_d;
            if (new.cost < cost[new.x][new.y][new_dir]) {
                cost[new.x][new.y][new_dir] = new.cost;
                new.dir_idx = new_dir;
                put_heap(new, queue);
            }
        }
    }
}

int sort_min_heap_from_bottom(int start_index, struct heap* target) {
    if (start_index == 1) return 0;

    int parent_index = start_index / 2;
    if (target->data[parent_index].cost > target->data[start_index].cost) {
        // parent is bigger -> swap
        node temp = target->data[parent_index];
        target->data[parent_index] = target->data[start_index];
        target->data[start_index] = temp;
        sort_min_heap_from_bottom(parent_index, target);
    }
    return 0;
}

int sort_min_heap_from_top(int start_index, struct heap* target) {
    int left_index = start_index * 2;
    int right_index = start_index * 2 + 1;

    node parent, left_child, right_child, temp;

    char swap_with_whom = 0;
    if (left_index <= target->last_index) {
        // left child exists
        parent = target->data[start_index];
        left_child = target->data[left_index];

        if (right_index <= target->last_index) {
            // right child exists
            right_child = target->data[right_index];

            if (left_child.cost < parent.cost &&
                right_child.cost < parent.cost) {
                // both children are smaller
                if (left_child.cost <= right_child.cost) {
                    swap_with_whom = 1;  // swap with left child
                } else {
                    swap_with_whom = 2;  // swap with right child
                }
            } else if (left_child.cost < parent.cost) {
                // only left child is smaller
                swap_with_whom = 1;  // swap with left child
            } else if (right_child.cost < parent.cost) {
                // only right child is smaller
                swap_with_whom = 2;  // swap with right child
            }
        } else {
            if (left_child.cost < parent.cost) {
                swap_with_whom = 1;  // swap with left child
            }
        }
    }

    switch (swap_with_whom) {
        case 0:
            // do nothing
            break;
        case 1:
            // swap with left child
            target->data[left_index] = parent;
            target->data[start_index] = left_child;
            sort_min_heap_from_top(left_index, target);
            break;
        case 2:
            // swap with right child
            target->data[right_index] = parent;
            target->data[start_index] = right_child;
            sort_min_heap_from_top(right_index, target);
            break;
        default:
            break;
    }

    return 0;
}

int put_heap(node new_val, struct heap* target) {
    target->last_index++;
    target->data[target->last_index] = new_val;

    if (target->last_index == 1) return 0;

    target->bottom_sorter(target->last_index, target);

    return 0;
}

node get_heap(struct heap* target) {
    node top_val = target->data[1];
    target->data[1] = target->data[target->last_index];
    target->last_index--;
    if (target->last_index == 0) return top_val;

    target->top_sorter(1, target);

    return top_val;
}
