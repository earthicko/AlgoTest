/*
행렬 k개 받음
i번째 행렬의 행: N(i), 열: M(i) (M(i) == N(i + 1))

F(n, m): n번째~m번째의 행렬 곱했을때 최소 곱셈 횟수
이때 F(n, n) = 0 (안 곱했으니까)

F(n, n+1) = F(n, n) + F(n+1, n+1) + n번째 m번째 행렬 곱할때 곱셈 횟수
          = 0 + 0 + N(n) * M(n) * M(n+1)
F(l, r) = (l <= mid < r 인 mid에 대하여)
            F(l, mid) + F(mid + 1, r) + N(l) * M(mid) * M(r) 의 값 중 최솟값
            F(l, mid) + F(mid + 1, r) + N(l) * N(mid + 1) * N(r + 1)
*/

#include <limits.h>
#include <stdio.h>
#define MAX_SIZE 501

typedef unsigned int uint;

uint min_cost[MAX_SIZE][MAX_SIZE];
int div[MAX_SIZE][MAX_SIZE];
uint n_rows[MAX_SIZE];

int main() {
    int k;
    scanf("%d", &k);
    uint temp;
    for (int i = 0; i < k; i++) {
        scanf("%d %d", n_rows + i, &temp);
    }
    n_rows[k] = temp;

    for (int i = 0; i < k; i++) min_cost[i][i] = 0;
    for (int range = 1; range <= k - 1; range++) {
        for (int l = 0; l <= k - range - 1; l++) {
            int r = l + range;
            min_cost[l][r] = UINT_MAX;
            int div_s, div_e;
            if (range == 1) {
                div_s = l;
                div_e = r - 1;
            } else {
                div_s = div[l][r - 1];
                div_e = div[l + 1][r];
            }

            for (int mid = div_s; mid <= div_e; mid++) {
                uint added = n_rows[l] * n_rows[mid + 1] * n_rows[r + 1];
                uint new_cost = min_cost[l][mid] + min_cost[mid + 1][r] + added;
                if (new_cost < min_cost[l][r]) {
                    min_cost[l][r] = new_cost;
                    div[l][r] = mid;
                }
            }
        }
    }
    printf("%d\n", min_cost[0][k - 1]);

    return 0;
}
