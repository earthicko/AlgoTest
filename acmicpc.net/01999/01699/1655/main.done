#include <stdio.h>
#include <stdlib.h>

#define N 100000

struct heap {
    int (*bottom_sorter)(int, struct heap*);
    int (*top_sorter)(int, struct heap*);
    int last_index;  // index where last element is (0 when empty)
    short data[N];   // 1: root / 2~3: level 1 / 4~7: level 2...
};

int sort_min_heap_from_bottom(int start_index, struct heap* target);
int sort_min_heap_from_top(int start_index, struct heap* target);
int sort_max_heap_from_bottom(int start_index, struct heap* target);
int sort_max_heap_from_top(int start_index, struct heap* target);
int put_heap(short new_val, struct heap* target);
short get_heap(struct heap* target);
int print_heap(struct heap* target);

int main() {
    struct heap min_heap;
    min_heap.bottom_sorter = sort_min_heap_from_bottom;
    min_heap.top_sorter = sort_min_heap_from_top;
    min_heap.last_index = 0;

    struct heap max_heap;
    max_heap.bottom_sorter = sort_max_heap_from_bottom;
    max_heap.top_sorter = sort_max_heap_from_top;
    max_heap.last_index = 0;

    int num_numbers;
    scanf("%d", &num_numbers);

    short first_num;
    scanf("%hi", &first_num);
    put_heap(first_num, &max_heap);
    printf("%hi\n", first_num);

    int i;
    for (i = 1; i < num_numbers; i++) {
        // printf("==============================input: ");
        short new_val;
        scanf("%hi", &new_val);

        if (i % 2 == 0) {
            // max heap turn
            put_heap(new_val, &max_heap);
        } else {
            // min heap turn
            put_heap(new_val, &min_heap);
        }
        if (max_heap.data[1] > min_heap.data[1]){
            short top_max = get_heap(&max_heap);
            short top_min = get_heap(&min_heap);
            put_heap(top_max, &min_heap);
            put_heap(top_min, &max_heap);
        }

        // printf("Max heap==============================\n");
        // print_heap(&max_heap);
        // printf("Min heap==============================\n");
        // print_heap(&min_heap);
        printf("%hi\n", max_heap.data[1]);
    }
    return 0;
}

int sort_min_heap_from_bottom(int start_index, struct heap* target) {
    if (start_index == 1) return 0;

    int parent_index = start_index / 2;
    if (target->data[parent_index] > target->data[start_index]) {
        // parent is bigger -> swap
        short temp = target->data[parent_index];
        target->data[parent_index] = target->data[start_index];
        target->data[start_index] = temp;
        sort_min_heap_from_bottom(parent_index, target);
    }
    return 0;
}

int sort_min_heap_from_top(int start_index, struct heap* target) {
    int left_index = start_index * 2;
    int right_index = start_index * 2 + 1;

    short parent, left_child, right_child, temp;

    char swap_with_whom = 0;
    if (left_index <= target->last_index) {
        // left child exists
        parent = target->data[start_index];
        left_child = target->data[left_index];

        if (right_index <= target->last_index) {
            // right child exists
            right_child = target->data[right_index];

            if (left_child < parent && right_child < parent) {
                // both children are smaller
                if (left_child <= right_child) {
                    swap_with_whom = 1;  // swap with left child
                } else {
                    swap_with_whom = 2;  // swap with right child
                }
            } else if (left_child < parent) {
                // only left child is smaller
                swap_with_whom = 1;  // swap with left child
            } else if (right_child < parent) {
                // only right child is smaller
                swap_with_whom = 2;  // swap with right child
            }
        } else {
            if (left_child < parent) {
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

int sort_max_heap_from_bottom(int start_index, struct heap* target) {
    if (start_index == 1) return 0;

    int parent_index = start_index / 2;
    if (target->data[parent_index] < target->data[start_index]) {
        // parent is smaller -> swap
        short temp = target->data[parent_index];
        target->data[parent_index] = target->data[start_index];
        target->data[start_index] = temp;
        sort_max_heap_from_bottom(parent_index, target);
    }
    return 0;
}

int sort_max_heap_from_top(int start_index, struct heap* target) {
    int left_index = start_index * 2;
    int right_index = start_index * 2 + 1;

    short parent, left_child, right_child, temp;

    char swap_with_whom = 0;
    if (left_index <= target->last_index) {
        // left child exists
        parent = target->data[start_index];
        left_child = target->data[left_index];

        if (right_index <= target->last_index) {
            // right child exists
            right_child = target->data[right_index];

            if (left_child > parent && right_child > parent) {
                // both children are bigger
                if (left_child >= right_child) {
                    swap_with_whom = 1;  // swap with left child
                } else {
                    swap_with_whom = 2;  // swap with right child
                }
            } else if (left_child > parent) {
                // only left child is bigger
                swap_with_whom = 1;  // swap with left child
            } else if (right_child > parent) {
                // only right child is bigger
                swap_with_whom = 2;  // swap with right child
            }
        } else {
            if (left_child > parent) {
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
            sort_max_heap_from_top(left_index, target);
            break;
        case 2:
            // swap with right child
            target->data[right_index] = parent;
            target->data[start_index] = right_child;
            sort_max_heap_from_top(right_index, target);
            break;
        default:
            break;
    }

    return 0;
}

int put_heap(short new_val, struct heap* target) {
    target->last_index++;
    target->data[target->last_index] = new_val;

    if (target->last_index == 1) return 0;

    target->bottom_sorter(target->last_index, target);

    return 0;
}

short get_heap(struct heap* target) {
    short top_val = target->data[1];
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
        printf("%d ", target->data[i]);

        if (i == level_max) {
            printf(") lv %d\n", cur_level);
            cur_level++;
            level_max = (level_max + 1) * 2 - 1;
        }
    }
    printf("\n-- total %d items\n", target->last_index);
}