#define N 69420

typedef struct heap {
    int (*bottom_sorter)(int, struct heap*);
    int (*top_sorter)(int, struct heap*);
    int last_index;  // index where last element is (0 when empty)
    short data[N];   // 1: root / 2~3: level 1 / 4~7: level 2...
} heap;

int sort_min_heap_from_bottom(int start_index, struct heap* target);
int sort_min_heap_from_top(int start_index, struct heap* target);
int sort_max_heap_from_bottom(int start_index, struct heap* target);
int sort_max_heap_from_top(int start_index, struct heap* target);
int put_heap(short new_val, struct heap* target);
short get_heap(struct heap* target);
int print_heap(struct heap* target);

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

int sort_min_heap_from_top(int s_idx, struct heap* target) {
    int l_idx = s_idx * 2;
    int r_idx = s_idx * 2 + 1;

    short parent, l, r, temp;

    char swap = 0;
    if (l_idx <= target->last_index) {
        // left child exists
        parent = target->data[s_idx];
        l = target->data[l_idx];
        if (r_idx <= target->last_index) {  // right child exists
            r = target->data[r_idx];
            if (l < parent && r < parent) {  // both children are smaller
                if (l <= r)
                    swap = 1;  // swap with left child
                else
                    swap = 2;         // swap with right child
            } else if (l < parent) {  // only left child is smaller
                swap = 1;             // swap with left child
            } else if (r < parent) {  // only right child is smaller
                swap = 2;             // swap with right child
            }
        } else {
            if (l < parent) swap = 1;  // swap with left child
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

int sort_max_heap_from_top(int s_idx, struct heap* target) {
    int l_idx = s_idx * 2;
    int r_idx = s_idx * 2 + 1;

    short parent, l, r, temp;

    char swap = 0;
    if (l_idx <= target->last_index) {  // left child exists
        parent = target->data[s_idx];
        l = target->data[l_idx];
        if (r_idx <= target->last_index) {  // right child exists
            r = target->data[r_idx];
            if (l > parent && r > parent) {  // both children are bigger
                if (l >= r)                  // swap with left child
                    swap = 1;
                else  // swap with right child
                    swap = 2;
            } else if (l > parent) {  // only left child is bigger
                swap = 1;             // swap with left child
            } else if (r > parent) {  // only right child is bigger
                swap = 2;             // swap with right child
            }
        } else {
            if (l > parent) swap = 1;  // swap with left child
        }
    }
    switch (swap) {
        case 0:  // do nothing
            break;
        case 1:  // swap with left child
            target->data[l_idx] = parent;
            target->data[s_idx] = l;
            sort_max_heap_from_top(l_idx, target);
            break;
        case 2:  // swap with right child
            target->data[r_idx] = parent;
            target->data[s_idx] = r;
            sort_max_heap_from_top(r_idx, target);
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