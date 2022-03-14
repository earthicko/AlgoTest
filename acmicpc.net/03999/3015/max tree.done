/*
큐에 길이 l을 추가
(조건) 첫 수 >= (모든 중간 수) <= 마지막 수 를 충족할때까지:
    첫 수와 2번째 수에 대해 (조건)을 확인 -> 만족하면 다음 수로
    첫 수와 3번째 수에 대해 (조건)을 확인 -> 만족하면 다음 수로
    ...
    첫 수와 n번째 수에 대해 (조건)을 확인 -> 만족하지 않을 시
    n-2를 카운터에 더하고 첫 수 큐에서 제거
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define get_max(a, b)           \
    ({                          \
        __typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        _a > _b ? _a : _b;      \
    })
#define N_MAX 500001
typedef struct node {
    int s, e;
    int max;
} node;
int fill_tree(int node_i, int s, int e);
int update_tree(int node_i, int new_val);
int query_max(int node_i, int scope_s, int scope_e);

int height[N_MAX], queue[N_MAX];
int N, head, tail;
node *max_tree;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) scanf("%d", &height[i]);
    int h_tree = ceil(log2(N));
    max_tree = malloc(sizeof(node) * (1 << (h_tree + 1)));
    fill_tree(1, 0, N);
    long long counter = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int local_max = query_max(1, i + 1, j);
#ifndef ONLINE_JUDGE
            printf("%d = %d, (%d, %d) = %d, %d = %d\n", i, height[i], i + 1,
                   j - 1, local_max, j, height[j]);
#endif
            if (local_max <= height[i] && local_max <= height[j])
                counter++;
            else
                break;
        }
    }
    printf("%lld\n", counter);

    return 0;
}
int fill_tree(int node_i, int s, int e) {
    max_tree[node_i].s = s;
    max_tree[node_i].e = e;
    if (s + 1 == e) {
        max_tree[node_i].max = height[s];
        return 0;
    }
    int mid = (s + e) / 2;
    fill_tree(2 * node_i, s, mid);
    fill_tree(2 * node_i + 1, mid, e);
    max_tree[node_i].max =
        get_max(max_tree[node_i * 2].max, max_tree[node_i * 2 + 1].max);
    return 0;
}

int update_tree_(int node_i, int num_i, int new_val) {
    if (!(num_i >= max_tree[node_i].s && num_i < max_tree[node_i].e)) return -1;
    max_tree[node_i].max = get_max(max_tree[node_i].max, new_val);
    if (max_tree[node_i].s + 1 == max_tree[node_i].e) return 0;
    update_tree_(node_i * 2, num_i, new_val);
    update_tree_(node_i * 2 + 1, num_i, new_val);
    return 0;
}

int update_tree(int node_i, int new_val) {
    height[node_i] = new_val;
    update_tree_(1, node_i, new_val);
    return 0;
}

int query_max(int node_i, int scope_s, int scope_e) {
    if (scope_s >= scope_e) return 0;
    if (max_tree[node_i].e <= scope_s || scope_e <= max_tree[node_i].s) {
        return 0;
    }
    if (scope_s <= max_tree[node_i].s && max_tree[node_i].e <= scope_e)
        return max_tree[node_i].max;
    int left_result = query_max(node_i * 2, scope_s, scope_e);
    int right_result = query_max(node_i * 2 + 1, scope_s, scope_e);
    int local_result = get_max(left_result, right_result);
    return local_result;
}