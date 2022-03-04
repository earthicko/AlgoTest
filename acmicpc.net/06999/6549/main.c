#include <stdio.h>
#define N_MAX 100000

typedef unsigned long long int ull;
int h[N_MAX];
ull recursive_solve(int idx_l, int idx_r);

int main() {
    while (1) {
        int n;
        scanf("%d", &n);
        if (n == 0) break;
        for (int i = 0; i < n; i++) scanf(" %d", h + i);
        printf("%lld\n", recursive_solve(0, n - 1));
    }
    return 0;
}

ull recursive_solve(int lim_l, int lim_r) {
    if (lim_l == lim_r) return h[lim_l];

    ull idx_l = (lim_l + lim_r) / 2;
    ull idx_r = idx_l + 1;
    ull result_l = recursive_solve(lim_l, idx_l);
    ull result_r = recursive_solve(idx_r, lim_r);

    ull min_h = (h[idx_l] < h[idx_r]) ? h[idx_l] : h[idx_r];
    ull max_a = min_h * (idx_r - idx_l + 1);

    while (1) {
        char left_limit = 0, right_limit = 0;  // can we expand to L or R?
        if (idx_l == lim_l || h[idx_l] == 0) left_limit = 1;
        if (idx_r == lim_r || h[idx_r] == 0) right_limit = 1;

        if (left_limit && right_limit) break;  // can't expand anymore
        int dir = -1;
        if (left_limit)  // can't expand to left
            dir = 1;
        else if (!right_limit &&
                 h[idx_l - 1] < h[idx_r + 1])  // right height is bigger
            dir = 1;
        if (dir == 1) {
            idx_r++;
            min_h = (h[idx_r] < min_h) ? h[idx_r] : min_h;
        } else {
            idx_l--;
            min_h = (h[idx_l] < min_h) ? h[idx_l] : min_h;
        }
        ull new_a = min_h * (idx_r - idx_l + 1);
        max_a = (new_a > max_a) ? new_a : max_a;
    }

    ull output = (result_l > result_r) ? result_l : result_r;
    output = (output > max_a) ? output : max_a;
    return output;
}