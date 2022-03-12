#include <stdio.h>
#include <stdlib.h>

struct num {
    int data;
    struct num* left;
    struct num* right;
};

struct cursor {
    struct num* pos;
    char offset;
};

struct num* construct_node(int val) {
    struct num* constructed = (struct num*)malloc(sizeof(struct num));
    constructed->data = val;
    constructed->left = NULL;
    constructed->right = NULL;
    return constructed;
}

struct num* insert_node(struct num* reference, int val, char direction) {
    // direction) 0: left / 1: right

    struct num* inserted = (struct num*)malloc(sizeof(struct num));
    struct num* temp;
    inserted->data = val;

    if (direction) {
        // right
        temp = reference->right;
        reference->right = inserted;
        inserted->left = reference;
        inserted->right = temp;
        if (temp != NULL) temp->left = inserted;
    } else {
        // left
        temp = reference->left;
        reference->left = inserted;
        inserted->right = reference;
        inserted->left = temp;
        if (temp != NULL) temp->right = inserted;
    }

    return inserted;
}

int move_cursor(struct cursor* cursor, char direction) {
    // no NULL exception

    // direction) 0: left / 1: right
    if (direction) {  // right
        if (cursor->offset) {
            cursor->pos = cursor->pos->right;
            cursor->offset = 0;
        } else {
            cursor->offset = 1;
        }
    } else {
        if (cursor->offset) {
            cursor->offset = 0;
        } else {
            cursor->pos = cursor->pos->left;
            cursor->offset = 1;
        }
    }
    return 0;
}

// int scan_nodes(struct num* start) {
//     printf("All nodes: ");
//     while (start->left != NULL) start = start->left;
//     while (start != NULL) {
//         printf("%d ", start->data);
//         start = start->right;
//     }
//     printf("\n");
//     return 0;
// }

int main() {
    int num_vals;
    scanf("%d", &num_vals);

    int first_val;
    scanf("%d", &first_val);
    printf("%d\n", first_val);
    struct num* first_node = construct_node(first_val);

    struct cursor cursor = {first_node, 0};

    int i;
    for (i = 1; i < num_vals; i++) {
        int cur_middle = cursor.pos->data;
        // printf("Current middle value is %d", cur_middle);
        // if (cursor.offset)
        //     printf(", with offset\n");
        // else
        //     printf("\n");

        int new_val;
        scanf("%d", &new_val);

        struct num* insert_target = cursor.pos;
        int left_side, right_side;

        if (new_val >= cur_middle) {
            // printf("scan from middle to far right\n");
            // scan from middle to far right
            while (insert_target->right != NULL) {
                left_side = insert_target->data;
                right_side = insert_target->right->data;
                // printf("left %d new %d right %d\n", left_side, new_val,
                //        right_side);
                if (left_side <= new_val && new_val < right_side) break;
                insert_target = insert_target->right;
            }
            // append / insert node
            // printf("insert target is %d\n", insert_target->data);
            insert_node(insert_target, new_val, 1);
            // move cursor to the right, half step
            move_cursor(&cursor, 1);
        } else {
            // printf("scan from middle to far left\n");
            // scan from middle to far left
            while (insert_target->left != NULL) {
                right_side = insert_target->data;
                left_side = insert_target->left->data;
                // printf("left %d new %d right %d\n", left_side, new_val,
                //        right_side);
                if (left_side < new_val && new_val <= right_side) break;
                insert_target = insert_target->left;
            }
            // append / insert node
            // printf("insert target is %d\n", insert_target->data);
            insert_node(insert_target, new_val, 0);
            // move cursor to the left, half step
            move_cursor(&cursor, 0);
        }

        printf("%d\n", cursor.pos->data);

        // scan_nodes(cursor.pos);
    }
    return 0;
}