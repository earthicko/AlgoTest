/* 다익스트라
필요 자료
- 맵 char[102][102]
    감옥 외곽을 자유로이 오갈 수 있기 때문에 100 x 100 감옥을 한번 빈 공간
(.)으로 감싼다.
- 문 횟수 맵 int[102][102] 3개
    해당 좌표까지 가기 위해서 열어야 하는 문의 개수
    다익스트라 알고리즘에서 코스트를 담당
- 우선순위 큐
    미방문 상태인 모든 노드 중 코스트가 가장 적은 노드를 고르기 위해 min heap
큐를 사용 정렬 기준은 문 횟수 (코스트)

논리 경로

조력자, 죄수1, 죄수2에 대해 각각 다익스트라 알고리즘을 실행하여 문 횟수 맵을
완성 조력자는 감옥 외곽에서, 죄수는 각자의 위치에서 시작

문 횟수 맵을 int 최대값으로 초기화한다
출발 좌표의 문 횟수는 0으로 설정한다

우선순위 큐를 만든다 (정렬 기준: 코스트)
큐에 출발 좌표를 푸시한다

큐가 빌 때까지 반복:
    큐에서 좌표를 뽑아 현재 좌표로 설정
    현재 좌표에 인접한 상하좌우의 노드에 대해서:
        다음 노드가 문이라면 코스트가 1 증가, 아니라면 같은 코스트
        다음 노드의 코스트를 계산한 결과가 문 횟수 맵에 저장된 코스트보다 작을
        경우:
            맵의 값을 갱신한다
            큐에 다음 노드의 좌표를 푸시한다 (즉 한번 와봤던
            좌표는 코스트가 더 작을 수 없기 때문에 큐에 다시 들어가지 않음)

3개의 문 맵을 더한다
-> 이때 도달하지 못한 부분은 int 최대값이기 때문에 오버플로 발생 체크
-> 이때 문의 좌표에서는 문을 여는 동작이 3번 일어나기 때문에 -2 한다

맵 상에서 가장 작은 수가 정답
*/

#include <limits.h>
#include <stdio.h>

#define DEBUG 0
#define INFO 1
#define JUDGE 100

#define LOG_LEVEL 100

#define MAP_SIZE 102
#define ARR_SIZE 10000

typedef struct coord {
    int x, y;
    int cost;
} coord;
typedef struct heap {
    int (*bottom_sorter)(int, struct heap*);
    int (*top_sorter)(int, struct heap*);
    int last_index;        // index where last element is (0 when empty)
    coord data[ARR_SIZE];  // 1: root / 2~3: level 1 / 4~7: level 2...
} heap;
char map[MAP_SIZE][MAP_SIZE];
int door_count[MAP_SIZE][MAP_SIZE][3];
coord dir[4] = {{0, 1, 0}, {0, -1, 0}, {-1, 0, 0}, {1, 0, 0}};

int sort_min_heap_from_bottom(int start_index, struct heap* target);
int sort_min_heap_from_top(int start_index, struct heap* target);
int put_heap(coord new_val, struct heap* target);
coord get_heap(struct heap* target);
int print_heap(struct heap* target);
int print_map(int x_size, int y_size);
int print_door_count(int idx, int x_size, int y_size);

int do_dijkstra(int idx, coord start, int size_x, int size_y);

int main() {
    int num_cases;
    scanf("%d", &num_cases);
    for (int i = 0; i < num_cases; i++) {
        int y_max, x_max;
        scanf("%d %d", &y_max, &x_max);
        x_max += 2;
        y_max += 2;

        coord dest[2];
        int num_dest = 0;
        for (int y = y_max - 2; y >= 1; y--) {
            for (int x = 1; x < x_max - 1; x++) {
                scanf(" %c", &(map[x][y]));
                if (map[x][y] == '$') {
                    dest[num_dest].x = x;
                    dest[num_dest].y = y;
                    dest[num_dest].cost = 0;
                    num_dest++;
                }
            }
        }
        for (int x = 0; x < x_max; x++) {
            map[x][0] = '.';
            map[x][y_max - 1] = '.';
        }
        for (int y = 1; y < y_max - 1; y++) {
            map[0][y] = '.';
            map[x_max - 1][y] = '.';
        }
        if (INFO >= LOG_LEVEL) {
            printf("Case %d\n", i);
            print_map(x_max, y_max);
            printf("Dest at (%d, %d), (%d, %d)\n", dest[0].x, dest[0].y,
                   dest[1].x, dest[1].y);
        }

        coord start = {0, 0, 0};

        do_dijkstra(0, start, x_max, y_max);
        if (INFO >= LOG_LEVEL) print_door_count(0, x_max, y_max);

        do_dijkstra(1, dest[0], x_max, y_max);
        if (INFO >= LOG_LEVEL) print_door_count(1, x_max, y_max);

        do_dijkstra(2, dest[1], x_max, y_max);
        if (INFO >= LOG_LEVEL) print_door_count(2, x_max, y_max);

        int min = INT_MAX;
        for (int x = 0; x < x_max; x++) {
            for (int y = 0; y < y_max; y++) {
                if (map[x][y] == '*') continue;
                int sum = 0;
                for (int j = 0; j < 3; j++) {
                    sum += door_count[x][y][j];
                }
                if (map[x][y] == '#') sum -= 2;
                if (sum < min) min = sum;
            }
        }
        printf("%d\n", min);
    }
    return 0;
}

int do_dijkstra(int idx, coord start, int size_x, int size_y) {
    struct heap p_q;
    p_q.bottom_sorter = sort_min_heap_from_bottom;
    p_q.top_sorter = sort_min_heap_from_top;
    p_q.last_index = 0;

    for (int x = 0; x < size_x; x++)
        for (int y = 0; y < size_y; y++) door_count[x][y][idx] = INT_MAX;

    put_heap(start, &p_q);
    door_count[start.x][start.y][idx] = 0;

    while (p_q.last_index > 0) {
        coord curr = get_heap(&p_q);
        for (int i = 0; i < 4; i++) {
            coord next;
            next.x = curr.x + dir[i].x;
            next.y = curr.y + dir[i].y;
            next.cost = curr.cost;
            if (map[next.x][next.y] == '*') continue;
            if (next.x < 0 || next.x >= size_x || next.y < 0 ||
                next.y >= size_y)
                continue;
            if (map[next.x][next.y] == '#') next.cost++;
            if (next.cost < door_count[next.x][next.y][idx]) {
                door_count[next.x][next.y][idx] = next.cost;
                put_heap(next, &p_q);
            }
        }
    }
    return 0;
}

int print_map(int x_size, int y_size) {
    for (int y = y_size - 1; y >= 0; y--) {
        for (int x = 0; x < x_size; x++) printf("%c ", map[x][y]);
        printf("\n");
    }
    return 0;
}

int print_door_count(int idx, int x_size, int y_size) {
    for (int y = y_size - 1; y >= 0; y--) {
        for (int x = 0; x < x_size; x++) {
            if (door_count[x][y][idx] == INT_MAX)
                printf("X ");
            else
                printf("%d ", door_count[x][y][idx]);
        }
        printf("\n");
    }
    return 0;
}

int sort_min_heap_from_bottom(int start_index, struct heap* target) {
    if (start_index == 1) return 0;
    int parent_index = start_index / 2;
    if (target->data[parent_index].cost > target->data[start_index].cost) {
        // parent is bigger -> swap
        coord temp = target->data[parent_index];
        target->data[parent_index] = target->data[start_index];
        target->data[start_index] = temp;
        sort_min_heap_from_bottom(parent_index, target);
    }
    return 0;
}

int sort_min_heap_from_top(int start_index, struct heap* target) {
    int left_index = start_index * 2;
    int right_index = start_index * 2 + 1;

    coord parent, left, right, temp;

    char swap_with_whom = 0;
    if (left_index <= target->last_index) {
        // left child exists
        parent = target->data[start_index];
        left = target->data[left_index];

        if (right_index <= target->last_index) {
            // right child exists
            right = target->data[right_index];

            if (left.cost < parent.cost && right.cost < parent.cost) {
                // both children are smaller
                if (left.cost <= right.cost) {
                    swap_with_whom = 1;  // swap with left child
                } else {
                    swap_with_whom = 2;  // swap with right child
                }
            } else if (left.cost < parent.cost) {
                // only left child is smaller
                swap_with_whom = 1;  // swap with left child
            } else if (right.cost < parent.cost) {
                // only right child is smaller
                swap_with_whom = 2;  // swap with right child
            }
        } else {
            if (left.cost < parent.cost) {
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
            target->data[start_index] = left;
            sort_min_heap_from_top(left_index, target);
            break;
        case 2:
            // swap with right child
            target->data[right_index] = parent;
            target->data[start_index] = right;
            sort_min_heap_from_top(right_index, target);
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

int print_heap(struct heap* target) {
    int cur_level = 1;
    int level_max = 1;
    int i;
    for (i = 1; i <= target->last_index; i++) {
        printf("(%d, %d: %d) ", target->data[i].x, target->data[i].y,
               target->data[i].cost);
        if (i == level_max) {
            printf(") lv %d\n", cur_level);
            cur_level++;
            level_max = (level_max + 1) * 2 - 1;
        }
    }
    printf("\n-- total %d items\n", target->last_index);
}