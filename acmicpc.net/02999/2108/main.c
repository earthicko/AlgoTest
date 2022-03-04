#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N_MAX 500000
#define NUM_MAX 4001
#define SCOPE_MAX 8001
// |sum| max = 2,000,000,000 < INT_MAX
typedef struct number {
    int val, count;
} number;
number occur[8001];
int numbers[N_MAX];
int n, sum;
int max = -NUM_MAX, min = NUM_MAX;

int cmp(const void *a, const void *b);
int cmp_y(const void *a, const void *b);

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
        sum += numbers[i];

        if (numbers[i] > max) max = numbers[i];
        if (numbers[i] < min) min = numbers[i];

        // -4000 -> 0, 4000 -> 8000
        occur[numbers[i] + 4000].val = numbers[i];
        occur[numbers[i] + 4000].count++;
    }

    float avg = (float)sum / (float)n;
    int int_avg = sum / n;
    if (avg >= 0 && avg - int_avg >= 0.5) int_avg++;
    if (avg < 0 && -avg + int_avg >= 0.5) int_avg--;

    qsort((void *)numbers, n, sizeof(int), cmp);
    int middle = numbers[n / 2];

    int nmemb = max - min + 1;
    int i_offset = min + 4000;
    qsort((void *)(occur + i_offset), nmemb, sizeof(number), cmp_y);

    int max_occur_count = 1;
    int max_occur = occur[i_offset].count;
    int max_occured_val = occur[i_offset].val;
    for (int i = i_offset + 1; i < i_offset + nmemb; i++) {
        if (occur[i].count != max_occur) break;
        max_occur_count++;
    }

    if (max_occur_count > 1) {
        int *max_occured_vals = (int *)malloc(sizeof(int) * max_occur_count);
        for (int i = 0; i < max_occur_count; i++)
            max_occured_vals[i] = occur[i + i_offset].val;
        qsort((void *)max_occured_vals, max_occur_count, sizeof(int), cmp);
        max_occured_val = max_occured_vals[max_occur_count - 2];
        free(max_occured_vals);
    }

    int scope = max - min;

    printf("%d\n%d\n%d\n%d\n", int_avg, middle, max_occured_val, scope);

    return 0;
}

int cmp(const void *a, const void *b) {
    if (*(int *)a > *(int *)b) return -1;
    if (*(int *)a < *(int *)b) return 1;
    return 0;
}

int cmp_y(const void *a, const void *b) {
    if (((number *)a)->count > ((number *)b)->count) return -1;
    if (((number *)a)->count < ((number *)b)->count) return 1;
    return 0;
}