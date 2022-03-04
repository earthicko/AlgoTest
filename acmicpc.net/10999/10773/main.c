#include <stdio.h>

int K;
int stack[100000];
int main() {
    scanf("%d", &K);
    int cur = 0;
    for (int k = 0; k < K; k++) {
        int input;
        scanf("%d", &input);
        if (input == 0)
            cur--;
        else
            stack[cur++] = input;
    }
    int sum = 0;
    for (int i = 0; i < cur; i++) sum += stack[i];
    printf("%d\n", sum);
    return 0;
}