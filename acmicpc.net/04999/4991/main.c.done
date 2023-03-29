/*
더러운 칸이 n_dest(0 <= n_dest <= 10)개일 시 BFS n_dest + 1번 수행

논리 경로
마스터 맵 입력
    이때 시작점 1개와 도착점 n_dest개를 별도로 저장
최소 이동 횟수 맵 n_dest+1개 생성
BFS n_dest+1개 생성:
    입력: 마스터 맵, 시작점, 도착점
    출력: 최소 이동 횟수 맵
    각 좌표별 의미: 해당 좌표로 더러운 칸을 피하면서 이동할 때 최소이동횟수
조합 실시:
    (n_dest)!번 조합
    (시작점) -> a번 더러운곳 -> b번 더러운곳 -> ... -> 마지막 더러운 곳
    맵[시작점][a의 좌표] + 맵[a][b의 좌표] + 맵[b][ + ... + ][마지막 좌표]

필요 자료형
최소이동횟수 맵 구조체: int** 횟수, int x크기, int y크기
좌표 구조체: int x, int y, int cost
우선순위 큐: 최소 힙
*/
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef ONLINE_JUDGE
#define NDEBUG
#endif

typedef struct coord {
    int x, y, cost;
} coord;
typedef struct list {
    int n, cap;
    coord* items;
    int (*append)(struct list*, coord);
    int (*insert)(struct list*, coord, int);
    int (*resize)(struct list*, int);
} list;
typedef struct heap {
    int (*bottom_sorter)(int, struct heap*);
    int (*top_sorter)(int, struct heap*);
    int last_index;   // index where last element is (0 when empty)
    coord data[400];  // 1: root / 2~3: level 1 / 4~7: level 2...
} heap;
typedef struct min_map {
    int** cost;
    int x, y;
} min_map;

int X_SIZE, Y_SIZE, N_POINTS;
int MIN_DISTANCE;
int** DISTANCES;
coord dir[4] = {{0, 1, 0}, {0, -1, 0}, {-1, 0, 0}, {1, 0, 0}};

int sort_min_heap_from_bottom(int start_index, struct heap* target);
int sort_min_heap_from_top(int start_index, struct heap* target);
int put_heap(coord new_val, struct heap* target);
coord get_heap(struct heap* target);
list* list_(int cap_);
int list__(list* del);
int resize_list(list* this, int cap_);
int append_to_list(list* this, coord new);
int insert_to_list(list* this, coord new, int idx);
min_map* min_map_(int x, int y);
int min_map__(min_map* del);

int do_bfs(char** map, coord s, coord e);
int permutate(int* indices, int s, int e);

int main() {
    while (1) {
        scanf("%d %d", &X_SIZE, &Y_SIZE);
        if (X_SIZE == 0 && Y_SIZE == 0) break;

        coord start = {0, 0, 0};
        list* points = list_(20);

        char** master_map = (char**)malloc(sizeof(char*) * X_SIZE);
        for (int i = 0; i < X_SIZE; i++)
            master_map[i] = (char*)malloc(sizeof(char) * Y_SIZE);

        for (int y = Y_SIZE - 1; y >= 0; y--) {
            for (int x = 0; x < X_SIZE; x++) {
                scanf(" %c", &(master_map[x][y]));
                if (master_map[x][y] == 'o') {
                    start.x = x;
                    start.y = y;
                }
                if (master_map[x][y] == '*') {
                    coord dest = {x, y, 0};
                    points->append(points, dest);
                }
            }
        }
        points->insert(points, start, 0);
        N_POINTS = points->n;

#ifndef NDEBUG
        printf("Waypoints: \n");
        for (int i = 0; i < N_POINTS; i++)
            printf("(%d, %d), ", points->items[i].x, points->items[i].y);
        printf("\n");
#endif

        DISTANCES = (int**)malloc(sizeof(int*) * N_POINTS);
        for (int i = 0; i < N_POINTS; i++) {
            DISTANCES[i] = (int*)malloc(sizeof(int) * N_POINTS);
        }
        char impossible_flag = 0;
        for (int i = 0; i < N_POINTS; i++) {
            for (int j = i + 1; j < N_POINTS; j++) {
                DISTANCES[i][j] =
                    do_bfs(master_map, points->items[i], points->items[j]);
                if (DISTANCES[i][j] == -1) {
                    impossible_flag = 1;
                    break;
                }
                DISTANCES[j][i] = DISTANCES[i][j];
            }
            if (impossible_flag) break;
        }
        if (impossible_flag) {
            printf("-1\n");
        } else {
#ifndef NDEBUG
            for (int i = 0; i < N_POINTS; i++) {
                for (int j = i + 1; j < N_POINTS; j++)
                    printf("Distance from (%d, %d) to (%d, %d) is %d\n",
                           points->items[i].x, points->items[i].y,
                           points->items[j].x, points->items[j].y,
                           DISTANCES[i][j]);
            }
#endif
            int* index_permutation = (int*)malloc(sizeof(int) * N_POINTS);
            for (int i = 0; i < N_POINTS; i++) index_permutation[i] = i;
            MIN_DISTANCE = INT_MAX;
            permutate(index_permutation, 1, N_POINTS);
            printf("%d\n", MIN_DISTANCE);
            free(index_permutation);
        }
        for (int i = 0; i < N_POINTS; i++) free(DISTANCES[i]);
        free(DISTANCES);
        for (int i = 0; i < X_SIZE; i++) free(master_map[i]);
        free(master_map);
        list__(points);
    }
    return 0;
}

int permutate(int* indices, int s, int e) {
    if (s + 1 == e) {
        int total_distance = 0;
        for (int i = 0; i < N_POINTS - 1; i++) {
            int start = indices[i];
            int end = indices[i + 1];
            int seg_distance = DISTANCES[indices[i]][indices[i + 1]];
            // if (DEBUG) printf("%d -%d-> %d, ", start, seg_distance, end);
            total_distance += seg_distance;
            if (total_distance >= MIN_DISTANCE) {
                // if (DEBUG) printf("Route too long\n");
                return -1;
            }
        }
        MIN_DISTANCE = total_distance;
#ifndef NDEBUG
        printf("New route found: ");
        for (int i = 0; i < N_POINTS; i++) printf("%d ", indices[i]);
        printf("\n");
        printf("MIN_DISTANCE update to %d\n", MIN_DISTANCE);
#endif
        return 0;
    }
    for (int i = s; i < e; i++) {
        int temp = indices[i];
        indices[i] = indices[s];
        indices[s] = temp;
        permutate(indices, s + 1, e);
        temp = indices[i];
        indices[i] = indices[s];
        indices[s] = temp;
    }
}

int do_bfs(char** map, coord s, coord e) {
    min_map* result = min_map_(X_SIZE, Y_SIZE);
    // make queue
    heap* queue = (heap*)malloc(sizeof(heap));
    queue->bottom_sorter = sort_min_heap_from_bottom;
    queue->top_sorter = sort_min_heap_from_top;
    queue->last_index = 0;

    result->cost[s.x][s.y] = 0;
    // push start to queue
    put_heap(s, queue);

    while (queue->last_index > 0) {  // queue is not empty
        // pop from queue
        coord here = get_heap(queue);
        for (int i = 0; i < 4; i++) {  // iterate directions
            coord there = {here.x + dir[i].x, here.y + dir[i].y, here.cost + 1};

            if (there.x < 0 || there.x >= X_SIZE || there.y < 0 ||
                there.y >= Y_SIZE) {  // if out of bound
                continue;
            }
            if (there.x == e.x && there.y == e.y) {  // if endpoint
                min_map__(result);
                return there.cost;
            }
            if (map[there.x][there.y] == 'x') {  // if wall
                continue;
            }
            // if already searched
            if (result->cost[there.x][there.y] <= there.cost) {
                continue;
            }
            // save cost
            result->cost[there.x][there.y] = there.cost;
            // push to queue
            put_heap(there, queue);
        }
    }
    min_map__(result);
    return -1;
}

min_map* min_map_(int x_, int y_) {
    min_map* output = (min_map*)malloc(sizeof(min_map));
    output->cost = (int**)malloc(sizeof(int*) * x_);
    for (int i = 0; i < x_; i++) {
        output->cost[i] = (int*)malloc(sizeof(int) * y_);
        for (int j = 0; j < y_; j++) output->cost[i][j] = INT_MAX;
    }
    output->x = x_;
    output->y = y_;
    return output;
}

int min_map__(min_map* del) {
    for (int i = 0; i < del->x; i++) free(del->cost[i]);
    free(del->cost);
    free(del);
    return 0;
}

int sort_min_heap_from_bottom(int s_idx, struct heap* target) {
    if (s_idx == 1) return 0;

    int p_idx = s_idx / 2;
    if (target->data[p_idx].cost > target->data[s_idx].cost) {
        // parent is bigger -> swap
        coord temp = target->data[p_idx];
        target->data[p_idx] = target->data[s_idx];
        target->data[s_idx] = temp;
        sort_min_heap_from_bottom(p_idx, target);
    }
    return 0;
}

int sort_min_heap_from_top(int s_idx, struct heap* target) {
    int l_idx = s_idx * 2;
    int r_idx = s_idx * 2 + 1;

    coord parent, l, r;

    char swap = 0;
    if (l_idx <= target->last_index) {
        // left child exists
        parent = target->data[s_idx];
        l = target->data[l_idx];
        if (r_idx <= target->last_index) {  // right child exists
            r = target->data[r_idx];
            if (l.cost < parent.cost &&
                r.cost < parent.cost) {  // both children are smaller
                if (l.cost <= r.cost)
                    swap = 1;  // swap with left child
                else
                    swap = 2;                   // swap with right child
            } else if (l.cost < parent.cost) {  // only left child is smaller
                swap = 1;                       // swap with left child
            } else if (r.cost < parent.cost) {  // only right child is smaller
                swap = 2;                       // swap with right child
            }
        } else {
            if (l.cost < parent.cost) swap = 1;  // swap with left child
        }
    }
    switch (swap) {
        case 0:  // do nothing
            break;
        case 1:  // swap with left child
            target->data[l_idx] = parent;
            target->data[s_idx] = l;
            sort_min_heap_from_top(l_idx, target);
            break;
        case 2:  // swap with right child
            target->data[r_idx] = parent;
            target->data[s_idx] = r;
            sort_min_heap_from_top(r_idx, target);
            break;
        default:
            break;
    }

    return 0;
}

int put_heap(coord new_val, struct heap* target) {
    target->last_index++;
    target->data[target->last_index] = new_val;

    if (target->last_index == 1) return 0;

    target->bottom_sorter(target->last_index, target);

    return 0;
}

coord get_heap(struct heap* target) {
    coord top_val = target->data[1];
    target->data[1] = target->data[target->last_index];
    target->last_index--;
    if (target->last_index == 0) return top_val;

    target->top_sorter(1, target);

    return top_val;
}

list* list_(int cap_) {
    list* new = (list*)malloc(sizeof(list));
    new->n = 0;
    new->cap = cap_;
    new->items = (coord*)malloc(sizeof(coord) * cap_);
    new->append = append_to_list;
    new->insert = insert_to_list;
    new->resize = resize_list;
    return new;
}

int list__(list* del) {
    free(del->items);
    free(del);
    return 0;
}

int resize_list(list* this, int cap_) {
    coord* temp = this->items;
    this->items = (coord*)malloc(sizeof(coord) * cap_);
    int copy_max = (this->n < cap_) ? this->n : cap_;
    for (int i = 0; i < copy_max; i++) this->items[i] = temp[i];
    free(temp);
    return 0;
}

int append_to_list(list* this, coord new) {
    if (this->n == this->cap) this->resize(this, this->cap * 2);
    this->items[this->n] = new;
    this->n++;
    return 0;
}

int insert_to_list(list* this, coord new, int idx) {
    if (this->n == this->cap) this->resize(this, this->cap * 2);
    idx = idx % this->n;
    for (int i = this->n - 1; i >= idx; i--)
        this->items[i + 1] = this->items[i];
    this->items[idx] = new;
    this->n++;
    return 0;
}
