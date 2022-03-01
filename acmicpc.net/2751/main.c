#include <stdio.h>
#include <stdlib.h>

#define N_MAX 1000000

int N;
int numbers[N_MAX];

int static compare(const void* first, const void* second) {
    if (*(int*)first > *(int*)second)
        return 1;
    else if (*(int*)first < *(int*)second)
        return -1;
    else
        return 0;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) scanf("%d", numbers + i);
    qsort(numbers, N, sizeof(int), compare);
    for (int i = 0; i < N; i++) printf("%d\n", numbers[i]);
    return 0;
}