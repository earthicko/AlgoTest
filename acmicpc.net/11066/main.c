/*
0 ~ n-1 번의 숫자가 주어짐

최소 비용을 구하는 함수 F(start, end)
F(start, end)는 F(start, mid) + F(mid + 1, end) + Sum(start, end)를 만족하는
mid (start <= mid < end)를 가지고 있다

F(start, mid) => 여태까지 합해온 좌측 뭉탱이
F(mid + 1, end) => 여태까지 합해온 우측 뭉탱이

여기서 비용은 합해온 과정에 따라 변하지만 (F를 찾는 이유) 합한 결과 (파일
크기)는 합해온 과정에 무관하다 즉 F값이 뭐가 되었건 두 F값을 합치는 데 들어가는
비용은 Sum(start, mid) + Sum(mid + 1, end) = Sum(start, end)로 일정하다

즉 Sum(start, end) 값은 계산해 놓고 mid를 스윕해가며 최소값을 찾아 저장한다

이때 F(n, n) = 0 이므로 임의의 mid에 대해 F(n, n+1) = 0 + 0 + Sum(n, n+1)
*/

#include <limits.h>
#include <stdio.h>
#define MAX_SIZE 500

int min_cost[MAX_SIZE][MAX_SIZE];
int div[MAX_SIZE][MAX_SIZE];
int size[MAX_SIZE];
int sum[MAX_SIZE];

int main() {
    int n_cases;
    scanf("%d", &n_cases);

    for (int case_n = 0; case_n < n_cases; case_n++) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", size + i);
            if (i == 0)
                sum[i] = size[i];
            else
                sum[i] = size[i] + sum[i - 1];
        }

        // F(n, n) = 0
        for (int i = 0; i < n; i++) {
            min_cost[i][i] = 0;
            div[i][i] = i;
        }

        for (int range = 1; range < n; range++) {
            for (int l = 0; l < n - range; l++) {
                int r = l + range;
                int div_s, div_e;
                if (range == 1) {
                    div_s = l;
                    div_e = r - 1;
                } else {
                    div_s = div[l][r - 1];
                    div_e = div[l + 1][r];
                }
                div[l][r] = div_e + 1;
                min_cost[l][r] = INT_MAX;
                for (int mid = div_s; mid <= div_e; mid++) {
                    int sum_left;
                    if (l - 1 < 0)
                        sum_left = 0;
                    else
                        sum_left = sum[l - 1];

                    int part_sum = sum[r] - sum_left;

                    int new_cost =
                        min_cost[l][mid] + min_cost[mid + 1][r] + part_sum;

                    if (new_cost < min_cost[l][r]) {
                        min_cost[l][r] = new_cost;
                        div[l][r] = mid;
                    }
                }
            }
        }
        printf("%d\n", min_cost[0][n - 1]);
    }

    return 0;
}