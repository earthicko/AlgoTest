#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW 1500
#define MAX_COL 1500

typedef struct coord {
    short row;
    short col;
} coord;

typedef struct queue_node {
    coord data;
    struct queue_node* prev;
} queue_node;

typedef struct queue {
    queue_node* head;
    queue_node* tail;
    int size;
} queue;

queue* construct_queue();
int push_queue(coord new_val, queue* target);
coord pop_queue(queue* target);
int print_queue(queue* target);

short num_row, num_col;
char map[MAX_ROW][MAX_COL];
short melting_date[MAX_ROW][MAX_COL];
short max_melting_date = 0;
char visited[MAX_ROW][MAX_COL];
coord swan_coords[2];

short directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int calculate_melting_date();
char check_swan_meeting_possibility(int max_days);

int main() {
    scanf("%hi %hi", &num_row, &num_col);

    int i, j;
    for (i = 0; i < num_row; i++) {
        scanf("%s", map[i]);
    }

    // printf("\nGiven map:\n");
    // for (i = 0; i < num_row; i++) {
    //     for (j = 0; j < num_col; j++) printf("%c ", map[i][j]);
    //     printf("\n");
    // }
    // printf("End of map\n");

    calculate_melting_date();

    // printf("\nCalculated melting dates:\n");
    // for (i = 0; i < num_row; i++) {
    //     for (j = 0; j < num_col; j++) printf("%d ", melting_date[i][j]);
    //     printf("\n");
    // }
    // printf("End of calculated melting dates\n");
    // printf("Max day is %d\n", max_melting_date);
    // printf("Swan is on (%d, %d), (%d, %d)\n", swan_coords[0].row,
    //        swan_coords[0].col, swan_coords[1].row, swan_coords[1].col);

    short min = 0;
    short max = max_melting_date;

    while (min <= max) {
        short mid = (min + max) / 2;
        // printf("Checking %d days\n", mid);
        if (check_swan_meeting_possibility(mid)) {
            max = mid - 1;
            // printf("Swan COULD meet at %d days, max to %d\n", mid, max);
        } else {
            min = mid + 1;
            // printf("Swan COULDN'T meet at %d days, min to %d\n", mid, min);
        }
    }

    // printf("Result: %d days\n", min);
    printf("%d", min);

    return 0;
}

int calculate_melting_date() {
    memset(melting_date, -1, sizeof(melting_date));

    queue* visiting_queue = construct_queue();

    char swan_count = 0;
    int i, j;
    for (i = 0; i < num_row; i++) {
        for (j = 0; j < num_col; j++) {
            if (map[i][j] == '.' || map[i][j] == 'L') {
                // is water or swan => set to 0 and push to queue
                melting_date[i][j] = 0;
                coord c = {i, j};
                push_queue(c, visiting_queue);

                if (map[i][j] == 'L') {
                    // found swan
                    swan_coords[swan_count++] = c;
                }
            }
        }
    }

    while (visiting_queue->size != 0) {
        coord base = pop_queue(visiting_queue);

        for (i = 0; i < 4; i++) {
            // in possible 4 directions add (dx, dy)
            coord target = {base.row + directions[i][0],
                            base.col + directions[i][1]};

            if (0 > target.row || target.row >= num_row || 0 > target.col ||
                target.col >= num_col) {
                // if out of bounds
                continue;
            }
            if (melting_date[target.row][target.col] != -1) {
                // already visited
                continue;
            }

            // add 1 from base and promise to visit the target
            melting_date[target.row][target.col] =
                melting_date[base.row][base.col] + 1;
            push_queue(target, visiting_queue);
            if (melting_date[target.row][target.col] > max_melting_date)
                max_melting_date = melting_date[target.row][target.col];
        }
    }

    free(visiting_queue);
    return 0;
}

char check_swan_meeting_possibility(int max_days) {
    memset(visited, 0, sizeof(visited));

    queue* visiting_queue = construct_queue();

    push_queue(swan_coords[0], visiting_queue);
    visited[swan_coords[0].row][swan_coords[0].col] = 1;

    // printf("Visited map\n");
    // for (int i = 0; i < num_row; i++) {
    //     for (int j = 0; j < num_col; j++) {
    //         if (visited[i][j] == 0)
    //             printf("0 ");
    //         else
    //             printf("1 ");
    //     }
    //     printf("\n");
    // }
    // printf("Visited map\n");

    while (visiting_queue->size != 0) {
        coord base = pop_queue(visiting_queue);
        if (base.row == swan_coords[1].row && base.col == swan_coords[1].col)
            return 1;

        int i;
        for (i = 0; i < 4; i++) {
            // in possible 4 directions add (dx, dy)
            // ↑ ↓ ← →
            coord target = {base.row + directions[i][0],
                            base.col + directions[i][1]};

            if (0 > target.row || target.row >= num_row || 0 > target.col ||
                target.col >= num_col) {
                continue;
            }

            if (visited[target.row][target.col] == 1 ||
                melting_date[target.row][target.col] > max_days) {
                continue;
            }

            push_queue(target, visiting_queue);
            visited[target.row][target.col] = 1;
        }
    }
    free(visiting_queue);
    return 0;
}

queue* construct_queue() {
    queue* new_queue = (queue*)malloc(sizeof(queue));
    new_queue->head = NULL;
    new_queue->tail = NULL;
    new_queue->size = 0;
    return new_queue;
}

int push_queue(coord new_val, queue* target) {
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

coord pop_queue(queue* target) {
    if (target->size == 0) {
        coord error = {420, 420};
        return error;
    }
    coord return_val = target->head->data;
    queue_node* deleted = target->head;
    target->head = target->head->prev;
    free(deleted);
    target->size--;
    return return_val;
}

// int print_queue(queue* target) {
//     printf("Queue size: %d\n", target->size);
//     queue_node* cursor = target->head;
//     while (cursor) {
//         printf("(%d, %d), ", cursor->data.row, cursor->data.col);
//         cursor = cursor->prev;
//     }
//     printf("\n");
//     return 0;
// }