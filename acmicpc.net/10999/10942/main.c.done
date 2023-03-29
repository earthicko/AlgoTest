#include <stdio.h>
#include <string.h>

#ifdef ONLINE_JUDGE
#define NDEBUG
#endif

#define N_MAX 2000

int N, M;
int numbers[N_MAX];
int map_palindrome[N_MAX][N_MAX];

int is_palindrome(int s, int e);

int main() {
    scanf("%d", &N);
    memset(map_palindrome, -1, sizeof map_palindrome);
    for (int i = 0; i < N; i++) {
        scanf("%d", numbers + i);
        map_palindrome[i][i] = 1;
    }
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int s, e;
        scanf("%d %d", &s, &e);
        printf("%d\n", is_palindrome(s - 1, e - 1));
    }
}

int is_palindrome(int s, int e) {
    // 1 2 -> even, center 1 2, sum is odd
    // 1 3 -> odd, center 2, sum is even
    // 2 6 -> odd, center 4, sum is even
    // 1 4 -> even, center 2 3, sum is odd
    if (map_palindrome[s][e] > -1) return map_palindrome[s][e];
#ifndef NDEBUG
    printf("Calculate %d to %d\n", s, e);
#endif
    int l, r;
    if ((s + e) % 2 == 1) {
        // even
        l = (s + e) / 2;
        r = l + 1;
#ifndef NDEBUG
        printf("Even, start from %d %d\n", l, r);
#endif
    } else {
        // odd
        l = (s + e) / 2 - 1;
        r = l + 2;
#ifndef NDEBUG
        printf("Odd, start from %d %d\n", l, r);
#endif
    }
    while (s <= l && r <= e) {
        if (numbers[l] == numbers[r]) {
            map_palindrome[l][r] = 1;
#ifndef NDEBUG
            printf("%d to %d is palindrome\n", l, r);
#endif
            l--;
            r++;
        } else {
            map_palindrome[l][r] = 0;
            map_palindrome[s][e] = 0;
#ifndef NDEBUG
            printf("%d to %d is not palindrome\n", l, r);
            printf("%d to %d is not palindrome\n", s, e);
#endif
            return 0;
        }
    }
    return 1;
}