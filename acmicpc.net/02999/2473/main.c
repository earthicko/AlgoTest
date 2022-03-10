#include <stdio.h>
#include <stdlib.h>
#define N_MAX 5000
#define abs(X) (X > 0) ? X : -X
typedef long long ll;
int N;
ll numbers[N_MAX];

int cmp(const void* a, const void* b);
int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) scanf("%lld", &numbers[i]);
    qsort(numbers, N, sizeof(ll), cmp);

    int pivot, s, e;
    ll min_div = 3000000001, abs_min_div = 3000000001;
    int fit_pivot, fit_s, fit_e;

    for (pivot = 0; pivot < N - 2; pivot++) {
        s = pivot + 1;
        e = N - 1;
        while (s < N && e > pivot && s < e) {
            ll div = numbers[pivot] + numbers[s] + numbers[e];
            ll abs_div = (div > 0) ? div : -div;
            if (abs_div < abs_min_div) {
                abs_min_div = abs_div;
                min_div = div;
                fit_pivot = pivot;
                fit_s = s;
                fit_e = e;
            }
            if (div < 0)
                s++;
            else
                e--;
        }
    }

    printf("%lld %lld %lld", numbers[fit_pivot], numbers[fit_s],
           numbers[fit_e]);
    return 0;
}
int cmp(const void* a, const void* b) {
    if (*(ll*)a > *(ll*)b) return 1;
    if (*(ll*)a < *(ll*)b) return -1;
    return 0;
}