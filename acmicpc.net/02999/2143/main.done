#include <stdio.h>
#include <stdlib.h>
#define N_MAX 1001
#define SUM_N_MAX 500500
int A[N_MAX], B[N_MAX];
int SUM_A_[N_MAX], SUM_B_[N_MAX];
int SUM_A[SUM_N_MAX], SUM_B[SUM_N_MAX];  // 4MB
int T, N, M;
int cmp(const void* a, const void* b);
int lower_bound(int arr[], int NMEMB, int X);
int upper_bound(int arr[], int NMEMB, int X);
int main() {
    scanf("%d", &T);
    scanf("%d", &N);
    for (int n = 1; n <= N; n++) scanf("%d", &A[n]);
    for (int n = 1; n <= N; n++) SUM_A_[n] = SUM_A_[n - 1] + A[n];
    scanf("%d", &M);
    for (int m = 1; m <= M; m++) scanf("%d", &B[m]);
    for (int m = 1; m <= M; m++) SUM_B_[m] = SUM_B_[m - 1] + B[m];

    int n_sum_a = 0;
    for (int s_a = 0; s_a <= N; s_a++) {
        for (int e_a = s_a + 1; e_a <= N; e_a++) {
            SUM_A[n_sum_a] = SUM_A_[e_a] - SUM_A_[s_a];
            n_sum_a++;
        }
    }
    int n_sum_b = 0;
    for (int s_b = 0; s_b <= M; s_b++) {
        for (int e_b = s_b + 1; e_b <= M; e_b++) {
            SUM_B[n_sum_b] = SUM_B_[e_b] - SUM_B_[s_b];
            n_sum_b++;
        }
    }
    qsort(SUM_B, n_sum_b, sizeof(int), cmp);

    long long num = 0;
    for (int i_a = 0; i_a < n_sum_a; i_a++) {
        int div = T - SUM_A[i_a];
        long long upper_i = upper_bound(SUM_B, n_sum_b, div);
        long long lower_i = lower_bound(SUM_B, n_sum_b, div);
        num += upper_i - lower_i;
    }
    printf("%lld", num);

    return 0;
}
int cmp(const void* a, const void* b) {
    if (*(int*)a > *(int*)b) return 1;
    if (*(int*)a < *(int*)b) return -1;
    return 0;
}
int lower_bound(int arr[], int NMEMB, int X) {
    int mid;
    int low = 0;
    int high = NMEMB;
    while (low < high) {
        mid = low + (high - low) / 2;
        if (X <= arr[mid])
            high = mid;

        else
            low = mid + 1;
    }
    if (low < NMEMB && arr[low] < X) low++;
    return low;
}
int upper_bound(int arr[], int NMEMB, int X) {
    int mid;
    int low = 0;
    int high = NMEMB;
    while (low < high) {
        mid = low + (high - low) / 2;
        if (X >= arr[mid])
            low = mid + 1;
        else
            high = mid;
    }
    if (low < NMEMB && arr[low] <= X) low++;
    return low;
}