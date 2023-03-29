/*
문제
창영과 상근은 한 동굴을 놓고 소유권을 주장하고 있다. 두 사람은 막대기를 서로에게
던지는 방법을 이용해 누구의 소유인지를 결정하기로 했다. 싸움은 동굴에서
벌어진다. 동굴에는 미네랄이 저장되어 있으며, 던진 막대기가 미네랄을 파괴할 수도
있다. 동굴은 R행 C열로 나타낼 수 있으며, R×C칸으로 이루어져 있다. 각 칸은
비어있거나 미네랄을 포함하고 있으며, 네 방향 중 하나로 인접한 미네랄이 포함된 두
칸은 같은 클러스터이다. 창영은 동굴의 왼쪽에 서있고, 상근은 오른쪽에 서있다. 두
사람은 턴을 번갈아가며 막대기를 던진다. 막대를 던지기 전에 던질 높이를 정해야
한다. 막대는 땅과 수평을 이루며 날아간다. 막대가 날아가다가 미네랄을 만나면, 그
칸에 있는 미네랄은 모두 파괴되고 막대는 그 자리에서 이동을 멈춘다. 미네랄이
파괴된 이후에 남은 클러스터가 분리될 수도 있다. 새롭게 생성된 클러스터가 떠 있는
경우에는 중력에 의해서 바닥으로 떨어지게 된다. 떨어지는 동안 클러스터의 모양은
변하지 않는다. 클러스터는 다른 클러스터나 땅을 만나기 전까지 게속해서 떨어진다.
클러스터는 다른 클러스터 위에 떨어질 수 있고, 그 이후에는 합쳐지게 된다. 동굴에
있는 미네랄의 모양과 두 사람이 던진 막대의 높이가 주어진다. 모든 막대를 던지고
난 이후에 미네랄 모양을 구하는 프로그램을 작성하시오.

입력
첫째 줄에 동굴의 크기 R과 C가 주어진다. (1 ≤ R,C ≤ 100)
다음 R개 줄에는 C개의 문자가 주어지며, '.'는 빈 칸, 'x'는 미네랄을 나타낸다.
다음 줄에는 막대를 던진 횟수 N이 주어진다. (1 ≤ N ≤ 100)
마지막 줄에는 막대를 던진 높이가 주어지며, 공백으로 구분되어져 있다. 모든 높이는
1과 R사이이며, 높이 1은 행렬의 가장 바닥, R은 가장 위를 의미한다. 첫 번째 막대는
왼쪽에서 오른쪽으로 던졌으며, 두 번째는 오른쪽에서 왼쪽으로, 이와 같은 식으로
번갈아가며 던진다. 공중에 떠 있는 미네랄 클러스터는 없으며, 두 개 또는 그 이상의
클러스터가 동시에 떨어지는 경우도 없다. 클러스터가 떨어질 때, 그 클러스터 각
열의 맨 아래 부분 중 하나가 바닥 또는 미네랄 위로 떨어지는 입력만 주어진다.

출력
입력 형식과 같은 형식으로 미네랄 모양을 출력한다.
================================================================================
필요 자료
1. 맵 (char 배열)
1-1. 탐색 완료 표시 맵 (char 배열)
2. 좌표 자료형 (struct)
3. 방문 큐 (좌표)
4. 클러스터 정보 배열 (칸 수, 가로 바운드, 세로 바운드...)
5. 클러스터 번호 카운터

필요 함수
0. 너비 우선 탐색기
    임의의 칸에서 시작하여 .이 아닌 칸을 너비 우선 탐색
    클러스터의 정보를 배열에 기록
    => 탐색해낸 칸 개수를 반환

1. 맵 해석기 (맵을 분석해 클러스터 표시)
    맵의 아래부터 탐색해 미네랄 x를 발견 시 그 지점 중심으로 너비 우선 탐색기
    실행, 클러스터 번호 매김
    => 반환 없음

    가설: 초기 상태에는 모든 클러스터가 지면에 닿아 있음

2. 막대 판정기 (막대가 닿았는지, 닿은 미네랄이 어디인지 판정)
    막대가 닿은 미네랄 좌표를 반환

3. 분열 판정기
    지면부터 위로 가로축 방향으로 스캔하여 클러스터 맵을 재구축
    만들어진 클러스터의 세로 바운드를 토대로 낙하할 클러스터 선정
    => 클러스터의 분열 여부, 낙하 할 클러스터 번호들을 반환

4. 낙하 판정기
    낙하하는 클러스터 중 하부가 노출된 칸 탐색
    노출된 칸 기준으로 하단으로 맵을 탐색하여 가장 가까운 타 클러스터 혹은
    지면까지의 거리 추산, 낙하 거리만큼 맵을 수정
    => 타 클러스터와 접촉 여부, 접촉할 클러스터 번호 반환

논리 경로
맵을 입력받는다
맵 해석기를 실행한다
막대의 수 만큼
    막대 판정기 실행->막대가 닿을 시
        분열 판정기 실행
        분열된 클러스터에 대해
            낙하 판정기 실행
맵 출력
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

#define MAP_SIZE 100

typedef struct coord {
    int x, y;
} coord;
struct queue_node {
    coord data;
    struct queue_node* prev;
};
typedef struct queue {
    struct queue_node* head;
    struct queue_node* tail;
    int size;
} queue;
typedef struct cluster_info {
    int num_blocks;
    int x_bound[2];
    int y_bound[2];
} cluster_info;

char map[MAP_SIZE][MAP_SIZE];
int x_max, y_max;
queue visiting_queue;
cluster_info clusters[MAP_SIZE];
int num_clusters = 0;

int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

struct queue* construct_queue(coord first_val);
int push_queue(coord new_val, struct queue* target);
coord pop_queue(struct queue* target);
int print_queue(struct queue* target);

int print_map();
int reset_map();
int print_num_blocks();
int paint_map(coord start, int to);
int build_cluster_info();
coord throw_stick(int height, int dir);
int get_floating_cluster_idx();
int apply_gravity(int cluster_idx);

int main() {
    scanf("%d %d", &y_max, &x_max);

    int i, j;
    for (i = y_max - 1; i >= 0; i--) {
        for (j = 0; j < x_max; j++) {
            char input;
            scanf("%c", &input);
            if (input == '\n') scanf("%c", &input);
            if (input == 'x') input = '+';
            map[j][i] = input;
        }
    }
    int num_throw;
    int h_throw[100];
    scanf("%d", &num_throw);
    for (i = 0; i < num_throw; i++) {
        scanf("%d", h_throw + i);
        h_throw[i]--;
    }

    if (DEBUG) {
        print_map();
        printf("%d Throws: ", num_throw);
        for (i = 0; i < num_throw; i++) printf("%d ", h_throw[i]);
        printf("\n");
    }

    if (DEBUG) printf("Building cluster info...\n");
    build_cluster_info();
    if (DEBUG) print_map();
    if (DEBUG) printf("Throwing sticks\n");
    for (i = 0; i < num_throw; i++) {
        if (DEBUG) printf("Throwing stick %d height %d ", i, h_throw[i]);
        coord impact;
        if (i % 2) {
            if (DEBUG) printf("from right\n");
            impact = throw_stick(h_throw[i], -1);
        } else {
            if (DEBUG) printf("from left\n");
            impact = throw_stick(h_throw[i], 1);
        }
        if (impact.x == -1) continue;
        map[impact.x][impact.y] = '.';

        int idx_floating_cls = get_floating_cluster_idx(&idx_floating_cls);

        if (DEBUG) printf("After throw\n");
        if (DEBUG) print_map();

        if (idx_floating_cls >= 0) {
            apply_gravity(idx_floating_cls);
            if (DEBUG) printf("After gravity\n");
            if (DEBUG) print_map();
        }
    }

    for (int y = y_max - 1; y >= 0; y--) {
        for (int x = 0; x < x_max; x++) {
            if (map[x][y] == '.')
                printf(".");
            else
                printf("x");
        }

        printf("\n");
    }

    return 0;
}

int print_map() {
    int i, j;
    printf("Map size (%d, %d)\n", x_max, y_max);
    for (i = y_max - 1; i >= 0; i--) {
        printf("%d | ", i);
        for (j = 0; j < x_max; j++) printf("%c ", map[j][i]);
        printf("\n");
    }
    printf("----");
    for (i = 0; i < x_max; i++) printf("--");
    printf("\n");
    printf("    ");
    for (i = 0; i < x_max; i++) printf("%d ", i);
    printf("\n");
    print_num_blocks();
    printf("Given map end\n");
}

int reset_map() {
    num_clusters = 0;
    for (int i = 0; i < y_max; i++) {
        for (int j = 0; j < x_max; j++) {
            if (map[j][i] >= 'A') map[j][i] = '+';
        }
    }
    return 0;
}

int print_num_blocks() {
    for (int i = 0; i < num_clusters; i++) {
        printf("%c: %d blocks, [%d - %d][%d - %d]\n", i + 'A',
               clusters[i].num_blocks, clusters[i].x_bound[0],
               clusters[i].x_bound[1], clusters[i].y_bound[0],
               clusters[i].y_bound[1]);
    }
    return 0;
}

int paint_map(coord from, int new_char) {
    char visited[MAP_SIZE][MAP_SIZE];
    memset(visited, 0, sizeof(char) * MAP_SIZE * MAP_SIZE);
    queue* to_visit = construct_queue(from);
    visited[from.x][from.y] = 1;

    int old_char = map[from.x][from.y];
    cluster_info* cls = clusters + (new_char - 'A');
    cls->num_blocks = 0;
    cls->x_bound[0] = x_max;
    cls->x_bound[1] = -1;
    cls->y_bound[0] = y_max;
    cls->y_bound[1] = -1;

    if (DEBUG)
        printf("Painting start (%d, %d) from %c to %c\n", from.x, from.y,
               old_char, new_char);

    while (to_visit->size != 0) {
        coord base = pop_queue(to_visit);
        map[base.x][base.y] = new_char;

        cls->num_blocks++;
        if (base.x < cls->x_bound[0]) cls->x_bound[0] = base.x;
        if (base.x > cls->x_bound[1]) cls->x_bound[1] = base.x;
        if (base.y < cls->y_bound[0]) cls->y_bound[0] = base.y;
        if (base.y > cls->y_bound[1]) cls->y_bound[1] = base.y;

        for (int i = 0; i < 4; i++) {
            int dx = directions[i][0];
            int dy = directions[i][1];
            coord target = {base.x + dx, base.y + dy};
            if (target.x < 0 || target.x >= x_max || target.y < 0 ||
                target.y >= y_max)
                continue;
            if (visited[target.x][target.y]) continue;
            if (map[target.x][target.y] == old_char)
                push_queue(target, to_visit);

            visited[target.x][target.y] = 1;
        }
    }
    if (DEBUG) printf("Painted %d blocks\n", cls->num_blocks);
    return cls->num_blocks;
}

int build_cluster_info() {
    int i;
    for (i = 0; i < x_max; i++) {
        if (map[i][0] == '+') {
            // BFS from [i][y_max]
            if (DEBUG) printf("Found mineral at (%d, %d)\n", i, 0);
            coord from = {i, 0};
            paint_map(from, num_clusters + 'A');
            num_clusters++;
        }
    }
}

coord throw_stick(int height, int dir) {
    // dir == 1  : left to right
    // dir == -1 : right to left
    int x;
    if (dir > 0)
        x = 0;
    else
        x = x_max - 1;
    for (int i = 0; i < x_max; i++) {
        if (map[x][height] != '.') {
            if (DEBUG)
                printf("Stick hit at %c (%d, %d)\n", map[x][height], x, height);
            coord output = {x, height};
            return output;
        }
        x += dir;
    }
    coord output = {-1, -1};
    return output;
}

int get_floating_cluster_idx() {
    reset_map();
    for (int i = 0; i < y_max; i++) {
        for (int j = 0; j < x_max; j++) {
            if (map[j][i] != '+') continue;
            coord from = {j, i};
            paint_map(from, num_clusters + 'A');
            num_clusters++;
        }
    }
    for (int i = 0; i < num_clusters; i++) {
        if (clusters[i].y_bound[0] > 0) {
            if (DEBUG) printf("Cluster %c is floating\n", i + 'A');
            return i;
        }
    }
    return -1;
}

int apply_gravity(int idx) {
    int cls_x_min = clusters[idx].x_bound[0];
    int cls_x_max = clusters[idx].x_bound[1];
    int distances[MAP_SIZE];

    if (DEBUG) printf("Seeking bottom of cluster %c\n", idx + 'A');
    for (int x = cls_x_min; x <= cls_x_max; x++) {
        for (int y = 0; y < y_max; y++) {
            if (map[x][y] == idx + 'A') {
                if (DEBUG) printf("bottom at (%d, %d)\n", x, y);
                distances[x] = y;
                break;
            }
        }
    }

    if (DEBUG) printf("Seeking closest surface from bottom\n");
    int closest = MAP_SIZE;
    for (int x = cls_x_min; x <= cls_x_max; x++) {
        int distance = distances[x];
        for (int y = distances[x] - 1; y >= 0; y--) {
            if (map[x][y] != '.') {
                distance = distances[x] - y - 1;
                break;
            }
        }
        if (DEBUG) printf("distance at x=%d is %d\n", x, distance);
        if (closest > distance) closest = distance;
    }
    if (DEBUG) printf("closest distance is %d\n", closest);

    for (int y = closest; y < y_max; y++) {
        for (int x = 0; x < x_max; x++) {
            if (map[x][y] == idx + 'A') {
                map[x][y - closest] = idx + 'A';
                map[x][y] = '.';
            }
        }
    }
}

struct queue* construct_queue(coord first_val) {
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

int push_queue(coord new_val, struct queue* target) {
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

coord pop_queue(struct queue* target) {
    if (target->size == 0) return;
    coord return_val = target->head->data;
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
        printf("(%d, %d), ", cursor->data.x, cursor->data.y);
        cursor = cursor->prev;
    }
    printf("\n");
    return 0;
}