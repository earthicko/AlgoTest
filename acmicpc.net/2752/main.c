#include <stdio.h>
#include <stdlib.h>

int compare_num(const void* a, const void* b);

int main() {
    int nums[3];
    scanf("%d %d %d", nums, nums + 1, nums + 2);
    qsort(nums, sizeof(nums) / sizeof(int), sizeof(int), compare_num);
    int i;
    printf("%d %d %d\n", nums[0], nums[1], nums[2]);
    return 0;
}

int compare_num(const void* a, const void* b) {
    int a_content = *(int*)a;
    int b_content = *(int*)b;

    if (a_content < b_content) return -1;
    if (a_content > b_content) return 1;
    return 0;
}