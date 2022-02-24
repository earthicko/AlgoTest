#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    time_t t;
    /* Intializes random number generator */
    srand((unsigned)time(&t));

    /* Print 5 random numbers from 0 to 49 */
    for (int i = 0; i < n; i++) {
        printf("%d ", rand() % 10000000);
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", rand() % 100);
    }
    printf("\n");

    return (0);
}