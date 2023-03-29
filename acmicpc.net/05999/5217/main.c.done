#include <stdio.h>

int main() {
    int num_cases;
    int sum;

    scanf("%d", &num_cases);
    int i;
    for (i = 0; i < num_cases; i++) {
        scanf("%d", &sum);
        printf("Pairs for %d: ", sum);

        int num_pairs = (sum + 1) / 2 - 1;
        int start;
        for (start = 1; start <= num_pairs; start++) {
            printf("%d %d", start, sum - start);
            if (start != num_pairs) printf(", ");
        }
        printf("\n");
    }

    return 0;
}