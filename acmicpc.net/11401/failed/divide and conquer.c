/*
문제
자연수 N과 정수 K가 주어졌을 때 이항 계수 ({N}{K})를 1,000,000,007로 나눈
나머지를 구하는 프로그램을 작성하시오.

입력
첫째 줄에 N과 K가 주어진다. (1 ≤ N ≤ 4,000,000, 0 ≤ K ≤ N)

출력
({N}{K})를 1,000,000,007로 나눈 나머지를 출력한다.

    1
   1 1
  1 2 1
 1 3 3 1
1 4 6 4 1
*/

#include <stdio.h>
#include <stdlib.h>

#define DENOM 1000000007
#define N_MAX 4000000

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    if (k > n / 2) k = n - k;

    int* first_row = (int*)malloc(sizeof(int) * (k + 1));
    int* last_row = (int*)malloc(sizeof(int) * (k + 1));
    first_row[0] = 1;
    last_row[0] = 1;

    int* rows[2] = {first_row, last_row};
    char shifter = 0;

    int i, j;

    for (i = 0; i < k; i++) {
        // triangle section; gets wider
        for (j = 1; j <= i / 2; j++) {
            // first half
            rows[shifter][j] = rows[shifter ^ 1][j - 1] + rows[shifter ^ 1][j];
            rows[shifter][j] %= DENOM;
        }
        for (j = i / 2 + 1; j <= i; j++) {
            // last half
            rows[shifter][j] = rows[shifter][i - j];
        }

        // for (j = 0; j <= i; j++) printf("%d ", rows[shifter][j]);
        // printf("\n");

        shifter = shifter ^ 1;
    }

    for (i = k; i <= n - k; i++) {
        // trapezoid section
        for (j = 1; j <= i / 2; j++) {
            rows[shifter][j] = rows[shifter ^ 1][j - 1] + rows[shifter ^ 1][j];
            rows[shifter][j] %= DENOM;
        }
        for (j = i / 2 + 1; j <= k; j++) {
            rows[shifter][j] = rows[shifter][i - j];
        }

        // for (j = 0; j <= k; j++) printf("%d ", rows[shifter][j]);
        // printf("\n");

        shifter = shifter ^ 1;
    }

    for (i = n - k + 1; i <= n; i++) {
        // reversed triangle section; gets narrower
        for (j = i - (n - k); j <= i / 2; j++) {
            rows[shifter][j] = rows[shifter ^ 1][j - 1] + rows[shifter ^ 1][j];
            rows[shifter][j] %= DENOM;
        }
        for (j = i / 2 + 1; j <= k; j++) {
            rows[shifter][j] = rows[shifter][i - j];
        }

        // for (j = i - (n - k); j <= k; j++) printf("%d ", rows[shifter][j]);
        // printf("\n");

        shifter = shifter ^ 1;
    }

    shifter = shifter ^ 1;

    printf("%d", rows[shifter][k]);

    return 0;
}