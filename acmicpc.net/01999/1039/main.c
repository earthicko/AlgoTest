#include <stdio.h>
#include <stdlib.h>

#ifdef ONLINE_JUDGE
#define NDEBUG
#endif

int N, N_DIGITS, K;
int SWAPPED[11][5040];
int N_SWAPPED[11];
int MAX_PERMUTATIONS = 1;

int swap_digit(int source, int i, int j);
int swap_permutate(int source, int k);

int main() {
    scanf("%d %d", &N, &K);
    N_DIGITS = 0;
    int temp = N;
    while (temp > 0) {
        N_DIGITS++;
        temp = temp / 10;
        MAX_PERMUTATIONS *= N_DIGITS;
    }
#ifndef NDEBUG
    printf("%d digits, %d permutations\n", N_DIGITS, MAX_PERMUTATIONS);
#endif
    N_SWAPPED[0] = 1;
    SWAPPED[0][0] = N;
    int k;
    for (k = 1; k <= K; k++) {
        for (int idx = 0; idx < N_SWAPPED[k - 1]; idx++) {
            swap_permutate(SWAPPED[k - 1][idx], k);
            if (N_SWAPPED[k] == 0) {
                printf("-1\n");
                return 0;
            }
        }
#ifndef NDEBUG
        printf("%d results: ", N_SWAPPED[k]);
        for (int i = 0; i < N_SWAPPED[k]; i++) printf("%d ", SWAPPED[k][i]);
        printf("\n");
#endif
        if (N_SWAPPED[k] == MAX_PERMUTATIONS) {
#ifndef NDEBUG
            printf("Reached max permutations of %d\n", MAX_PERMUTATIONS);
#endif
            k++;
            break;
        }
    }
    k--;
    int max = 0;
    for (int i = 0; i < N_SWAPPED[k]; i++) {
        if (max < SWAPPED[k][i]) max = SWAPPED[k][i];
    }
    printf("%d\n", max);
    return 0;
}

int swap_digit(int source, int i, int j) {
    int i_power_10 = 1;
    int j_power_10 = 1;
    for (int k = 0; k < i; k++) i_power_10 *= 10;
    for (int k = 0; k < j; k++) j_power_10 *= 10;
    int i_digit = (source / i_power_10) % 10;
    int j_digit = (source / j_power_10) % 10;
    source = source - i_digit * i_power_10 - j_digit * j_power_10;
    source = source + i_digit * j_power_10 + j_digit * i_power_10;
    return source;
}

int swap_permutate(int source, int k) {
#ifndef NDEBUG
    printf("Step %d\n", k);
#endif
    for (int i = 0; i <= N_DIGITS - 2; i++) {
        for (int j = i + 1; j <= N_DIGITS - 1; j++) {
            if (j == N_DIGITS - 1) {
                // check if i'th digit is not 0
                int i_power_10 = 1;
                for (int k = 0; k < i; k++) i_power_10 *= 10;
                int i_digit = (source / i_power_10) % 10;
                if (i_digit == 0) continue;
            }
            int new_combination = swap_digit(source, i, j);
#ifndef NDEBUG
            printf("swap %d => %d <-> %d => %d\n", source, i, j,
                   new_combination);
#endif

            int duplicate = 0;
            for (int idx = 0; idx < N_SWAPPED[k]; idx++) {
                if (SWAPPED[k][idx] == new_combination) {
#ifndef NDEBUG
                    printf("%d is duplicate\n", new_combination);
#endif
                    duplicate = 1;
                    break;
                }
            }

            if (duplicate == 0) {
                SWAPPED[k][N_SWAPPED[k]] = new_combination;
                N_SWAPPED[k]++;
            }
        }
    }
}
