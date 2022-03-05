#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char expr[51];
    scanf("%s", expr);
    int sum = atoi(expr);
    int start = 0;
    int len = strlen(expr);
    while (expr[start] != '-' && expr[start] != '+') start++;

    for (int i = start; i < len; i++) {
        if (expr[i] == '-') {
            while (1) {
                int subtracted = atoi(expr + ++i);
                sum -= subtracted;
                while (expr[i] != '-' && expr[i] != '+' && i < len) i++;
                if (i == len) break;
                if (expr[i] == '-') {
                    i--;
                    break;
                }
            }
        } else if (expr[i] == '+') {
            int added = atoi(expr + ++i);
            sum += added;
            while (expr[i] != '-' && expr[i] != '+' && i < len) i++;
            i--;
        } else {
            assert(!"Unhandled Exception");
        }
    }

    printf("%d", sum);
    return 0;
}