#include <stdio.h>

#define NUM_MAX 1001
#define N_MAX 100

int IS_COMPOSITE[NUM_MAX];
int NUMBERS[N_MAX];

int main() {
    int n, max_num = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &NUMBERS[i]);
        if (NUMBERS[i] > max_num) max_num = NUMBERS[i];
    }

    IS_COMPOSITE[1] = 1;
    for (int i = 4; i <= max_num; i += 2) IS_COMPOSITE[i] = 1;
    for (int i = 3; i < max_num; i += 2)
        if (!IS_COMPOSITE[i])
            for (int j = i * 2; j <= max_num; j += i) IS_COMPOSITE[j] = 1;
    int counter = 0;
    for (int i = 0; i < n; i++)
        if (IS_COMPOSITE[NUMBERS[i]] == 0) counter++;
    printf("%d\n", counter);
    return 0;
}