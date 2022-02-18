#include <stdio.h>

struct item {
    int weight;
    int value;
};

struct item items[100];
int i_to_weight_table[101][100000];
int num_items;
int max_weight;

int get_value(int index, int weight) {
    if (index <= 0 || weight <= 0) return 0;

    if (items[index - 1].weight > weight) {
        // cant put item into backpack, skip
        // result will be the same without current item
        if (i_to_weight_table[index - 1][weight] == 0) {
            // if calculation is never made
            i_to_weight_table[index - 1][weight] = get_value(index - 1, weight);
        }
        // copy value to current cell
        i_to_weight_table[index][weight] = i_to_weight_table[index - 1][weight];
    } else {
        // can put item into backpack
        int weight_deducted = weight - items[index - 1].weight;
        if (i_to_weight_table[index - 1][weight_deducted] == 0) {
            i_to_weight_table[index - 1][weight_deducted] =
                get_value(index - 1, weight_deducted);
        }
        int result_if_item_put = i_to_weight_table[index - 1][weight_deducted] +
                                 items[index - 1].value;

        if (i_to_weight_table[index - 1][weight] == 0) {
            i_to_weight_table[index - 1][weight] = get_value(index - 1, weight);
        }
        int result_if_skipped = i_to_weight_table[index - 1][weight];

        if (result_if_item_put > result_if_skipped)
            i_to_weight_table[index][weight] = result_if_item_put;
        else
            i_to_weight_table[index][weight] = result_if_skipped;
    }
    return i_to_weight_table[index][weight];
}

int main() {
    scanf("%d %d", &num_items, &max_weight);
    int i;
    for (i = 0; i < num_items; i++) {
        scanf("%d %d", &items[i].weight, &items[i].value);
    }

    int result = get_value(num_items, max_weight);
    printf("%d", result);
    return 0;
}