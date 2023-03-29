/*
맵을 입력받음
죄수($)로부터 탐색 실시
    1. 상하좌우 중 갈 수 있는 칸 판별
        벽(*)이 아니고 가보지 않은 칸
    2. 갈 수 있는 칸이 2개 이상일 시 분기 (재귀?)
    3. 경로상에서 만나는 문을 연결 리스트에 저장
    4. out of bound시 탐색 종료
    5. 만난 문 정보를 반환
0번 죄수의 경로 n개와 1번 죄수의 경로 m개를 획득
n * m번 경로를 조합하여 지나야 하는 문 개수가 가장 적은 경우를 계산

필요 자료
맵: char[102][102]
좌표: struct
만난 문 정보: struct의 연결 리스트
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEBUG 0
#define INFO 1
#define JUDGE 100

#define LOG_LEVEL 100

#define MAP_SIZE 100

typedef struct coord {
    int x, y;
} coord;

typedef struct array {
    int n_items;
    int cap;
    coord* items;
} array;

const coord dir[4] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

array* routes[MAP_SIZE];
char success[MAP_SIZE];
int num_success;
int id_max = 0;

array* construct_array(int size);
int free_array(array* arr);
array* copy_array(array* arr);
coord* append_array(array* arr, coord item);
int print_array(array* arr);
int print_map(char map[][MAP_SIZE], int x_size, int y_size);
int find_way_from(char map[][MAP_SIZE], int* x_max, int* y_max, coord from,
                  int id);
int count_doors(array* route0, array* route1, int* x_max, int* y_max);

int main() {
    int num_cases;
    scanf("%d", &num_cases);
    for (int i = 0; i < num_cases; i++) {
        int y_max, x_max;
        scanf("%d %d", &y_max, &x_max);

        char map[MAP_SIZE][MAP_SIZE];
        coord dest[2];
        int num_dest = 0;
        for (int y = y_max - 1; y >= 0; y--) {
            for (int x = 0; x < x_max; x++) {
                scanf(" %c", &(map[x][y]));
                if (map[x][y] == '$') {
                    dest[num_dest].x = x;
                    dest[num_dest].y = y;
                    num_dest++;
                }
            }
        }

        if (INFO >= LOG_LEVEL) {
            printf("Case %d\n", i);
            print_map(map, x_max, y_max);
            printf("Dest at (%d, %d), (%d, %d)\n", dest[0].x, dest[0].y,
                   dest[1].x, dest[1].y);
        }

        // find way from dest 0
        char new_map[MAP_SIZE][MAP_SIZE];
        for (int x = 0; x < x_max; x++) {
            for (int y = 0; y < y_max; y++) new_map[x][y] = map[x][y];
        }
        for (int j = 0; j < MAP_SIZE; j++) success[j] = 0;
        id_max = 0;
        num_success = 0;
        routes[id_max] = construct_array(MAP_SIZE);
        find_way_from(new_map, &x_max, &y_max, dest[0], 0);

        // collect success routes
        array** routes_0 = (array**)malloc(sizeof(array*) * num_success);
        int num_success_0 = num_success;
        int temp = 0;
        for (int j = 0; j <= id_max; j++) {
            if (success[j]) routes_0[temp++] = routes[j];
        }
        if (INFO >= LOG_LEVEL) {
            printf("Dest %d: %d routes, collected %d routes\n", 0,
                   num_success_0, temp);
            for (int j = 0; j < num_success_0; j++) print_array(routes_0[j]);
        }

        // find way from dest 1
        new_map[MAP_SIZE][MAP_SIZE];
        for (int x = 0; x < x_max; x++) {
            for (int y = 0; y < y_max; y++) new_map[x][y] = map[x][y];
        }
        for (int j = 0; j < MAP_SIZE; j++) success[j] = 0;
        id_max = 0;
        num_success = 0;
        routes[id_max] = construct_array(MAP_SIZE);
        find_way_from(new_map, &x_max, &y_max, dest[1], 0);

        // collect success routes
        array** routes_1 = (array**)malloc(sizeof(array*) * num_success);
        int num_success_1 = num_success;
        temp = 0;
        for (int j = 0; j <= id_max; j++) {
            if (success[j]) routes_1[temp++] = routes[j];
        }
        if (INFO >= LOG_LEVEL) {
            printf("Dest %d: %d routes, collected %d routes\n", 1,
                   num_success_1, temp);
            for (int j = 0; j < num_success_1; j++) print_array(routes_1[j]);
        }

        // route combination
        int min = INT_MAX;
        for (int n = 0; n < num_success_0; n++) {
            for (int m = 0; m < num_success_1; m++) {
                int n_doors =
                    count_doors(routes_0[n], routes_1[m], &x_max, &y_max);
                if (n_doors < min) min = n_doors;
                if (INFO >= LOG_LEVEL)
                    printf("Counting from %d : %d = %d doors\n", n, m, n_doors);
            }
        }
        if (INFO >= LOG_LEVEL) printf("Minimum %d doors\n", min);
        // free all routes
        for (int j = 0; j < num_success_0; j++) free_array(routes_0[j]);
        for (int j = 0; j < num_success_1; j++) free_array(routes_1[j]);
        printf("%d", min);
    }

    return 0;
}

int find_way_from(char map[][MAP_SIZE], int* x_max, int* y_max, coord from,
                  int id) {
    if (DEBUG >= LOG_LEVEL) printf("Solver %d start\n", id);
    while (1) {
        if (DEBUG >= LOG_LEVEL) printf("Solver %d: Frame start\n", id);
        if (map[from.x][from.y] == '#') {
            // append coord to array
            if (DEBUG >= LOG_LEVEL)
                printf("Solver %d: door found at (%d, %d)\n", id, from.x,
                       from.y);
            coord door_coord = {from.x, from.y};
            append_array(routes[id], door_coord);
        }
        map[from.x][from.y] = '*';
        char possible[4] = {0, 0, 0, 0};
        int num_possible = 0;
        for (int i = 0; i < 4; i++) {
            coord next = {from.x + dir[i].x, from.y + dir[i].y};
            if (next.x < 0 || next.x >= *x_max || next.y < 0 ||
                next.y >= *y_max) {
                // success, end
                success[id] = 1;
                num_success++;
                if (DEBUG >= LOG_LEVEL) {
                    printf("Solver %d: exit found at (%d, %d)\n", id, next.x,
                           next.y);
                    printf("Solver %d: %d success cases\n", id, num_success);
                }
                return 0;
            }
            if (map[next.x][next.y] != '*') {
                possible[i] = 1;
                num_possible++;
            }
        }
        if (num_possible == 0) break;
        if (num_possible == 1) {
            // move, change, repeat
            for (int i = 0; i < 4; i++) {
                if (possible[i]) {
                    from.x += dir[i].x;
                    from.y += dir[i].y;
                    if (DEBUG >= LOG_LEVEL)
                        printf("Solver %d: moved to (%d, %d)\n", id, from.x,
                               from.y);
                    break;
                }
            }
        } else {
            // recursive branch
            for (int i = 0; i < 4; i++) {
                if (possible[i]) {
                    // copy map
                    char new_map[MAP_SIZE][MAP_SIZE];
                    for (int x = 0; x < *x_max; x++) {
                        for (int y = 0; y < *y_max; y++)
                            new_map[x][y] = map[x][y];
                    }
                    coord next = {from.x + dir[i].x, from.y + dir[i].y};
                    id_max++;
                    routes[id_max] = copy_array(routes[id]);
                    if (DEBUG >= LOG_LEVEL)
                        printf("Solver %d: branch from (%d, %d), id %d\n", id,
                               next.x, next.y, id_max);
                    find_way_from(new_map, x_max, y_max, next, id_max);
                }
            }
            // finish job
            free_array(routes[id]);
            if (DEBUG >= LOG_LEVEL) printf("Solver %d: branch complete\n", id);
            return 0;
        }
        if (DEBUG >= LOG_LEVEL) print_map(map, *x_max, *y_max);
        if (DEBUG >= LOG_LEVEL) printf("Solver %d: Frame end\n", id);
    }
    // finish without success
    free_array(routes[id]);
    if (DEBUG >= LOG_LEVEL) printf("Solver %d: fail\n", id);
    return 0;
}

int print_map(char map[][MAP_SIZE], int x_size, int y_size) {
    for (int y = y_size - 1; y >= 0; y--) {
        printf("%d | ", y);
        for (int x = 0; x < x_size; x++) {
            printf("%c ", map[x][y]);
        }
        printf("\n");
    }
    printf("    ");
    for (int x = 0; x < x_size; x++) printf("%d ", x);
    printf("\n");
    return 0;
}

int count_doors(array* route0, array* route1, int* x_max, int* y_max) {
    char door_map[MAP_SIZE][MAP_SIZE];
    memset(door_map, 0, sizeof(char) * MAP_SIZE * MAP_SIZE);
    int n_doors = route0->n_items;
    for (int i = 0; i < route0->n_items; i++)
        door_map[route0->items[i].x][route0->items[i].y] = 1;
    for (int i = 0; i < route0->n_items; i++) {
        if (door_map[route1->items[i].x][route1->items[i].y] == 0) n_doors++;
    }
    return n_doors;
}

array* construct_array(int size) {
    array* new = (array*)malloc(sizeof(array));
    new->n_items = 0;
    new->cap = size;
    new->items = (coord*)malloc(sizeof(coord) * size);
    return new;
}

int free_array(array* arr) {
    free(arr->items);
    free(arr);
}

array* copy_array(array* arr) {
    array* new = (array*)malloc(sizeof(array));
    new->n_items = arr->n_items;
    new->cap = arr->cap;
    new->items = (coord*)malloc(sizeof(coord) * new->cap);
    for (int i = 0; i < new->n_items; i++) new->items[i] = arr->items[i];
    return new;
}

coord* append_array(array* arr, coord item) {
    if (arr->cap == arr->n_items) {
        arr->cap *= 2;
        coord* temp = arr->items;
        arr->items = (coord*)malloc(sizeof(coord) * arr->cap);
        for (int i = 0; i < arr->n_items; i++) arr->items[i] = temp[i];
        free(temp);
    }
    arr->items[arr->n_items++] = item;
    return arr->items + arr->n_items - 1;
}

int print_array(array* arr) {
    printf("%d items: ", arr->n_items);
    for (int i = 0; i < arr->n_items; i++)
        printf("(%d, %d), ", arr->items[i].x, arr->items[i].y);
    printf("\n");
    return 0;
}