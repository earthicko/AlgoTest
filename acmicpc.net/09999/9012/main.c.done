#include <stdio.h>

int main() {
    int N;
    scanf("%d\n", &N);
    for (int n = 0; n < N; n++) {
        char stack[50];
        int cur = 0;

        char string[50];
        int size = 0;
        while (1) {
            char c;
            scanf("%c", &c);
            if (c == '\n') break;
            string[size] = c;
            size++;
        }

        int balanced = 1;
        for (int i = 0; i < size; i++) {
            switch (string[i]) {
                case '(':
                    stack[cur++] = string[i];
                    break;
                case ')':
                    if (cur > 0) {
                        char c = stack[--cur];
                        if (!(c == '(' && string[i] == ')')) {
                            balanced = 0;
                        }
                    } else {
                        balanced = 0;
                    }
                    break;
                default:
                    break;
            }

            if (!balanced) break;
        }
        if (cur > 0) balanced = 0;
        if (balanced)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
