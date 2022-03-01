#include <stdio.h>

int N;
int counter[10001]; // 40KB

int main() {
    scanf("%d", &N);
    int max = 0;
    for (int i = 0; i < N; i++) {
        int number;
        scanf("%d", &number);
        if (max < number) max = number;
        counter[number]++;
    }
    for (int i = 0; i <= max; i++) {
        for (int j = 0; j < counter[i]; j++) printf("%d\n", i);
    }
    return 0;
}