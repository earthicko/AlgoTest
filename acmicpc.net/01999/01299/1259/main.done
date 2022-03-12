#include <stdio.h>

int main() {
    char input[6];
    while (1) {
        scanf("%s", input);
        if (input[0] == '0') break;
        int last;
        for (int i = 0; i < 6; i++) {
            if (input[i] == '\0') {
                last = i - 1;
                break;
            }
        }
        // last = 2 => (0, 2) => (1, 1)
        // last = 3 => (0, 3), (1, 2) => (2, 1)
        // last = 4 => (0, 4), (1, 3) => (2, 2)
        // last = 5 => (0, 5), (1, 4), (2, 3) => (3, 2)
        int first = 0;
        int palindrome = 1;
        while (first < last) {
            if (input[first] != input[last]) {
                palindrome = 0;
                break;
            }
            first++;
            last--;
        }
        if (palindrome)
            printf("yes\n");
        else
            printf("no\n");
    }
    return 0;
}