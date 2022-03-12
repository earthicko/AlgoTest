/*
수열 길이 1 <= N <= 2,000
수 크기 1 <= Ai <= 100,000
질문 개수 ~ 1,000,000개

An부터 Am이 팰린드롬인지 저장하는 배열 char[2000][2000] = 1B * 4,000,000 = 4MB
*/

#include <stdio.h>

#ifdef ONLINE_JUDGE
#define NDEBUG
#endif

#define N_MAX 2000

int N, M;
int numbers[N_MAX];
char is_palindrome[N_MAX][N_MAX];

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) scanf("%d", numbers + i);

    for (int i = 0; i < N; i++) {
#ifndef NDEBUG
        printf("Check from i %d\n", i);
        printf("%d to %d is palindrome\n", i, i);
#endif
        is_palindrome[i][i] = 1;
        if (i >= 1 && numbers[i - 1] == numbers[i]) {
            // if even palindrome detected
            // mark is_palindrome
            int l = i - 1;
            int r = i;
            while (1) {
#ifndef NDEBUG
                printf("%d to %d is palindrome\n", l, r);
#endif
                is_palindrome[l--][r++] = 1;
                if (!(l >= 0 && r < N)) break;
                if (numbers[l] != numbers[r]) break;
            }
        }
        if (i >= 2 && numbers[i - 2] == numbers[i]) {
            // if odd palindrome detected
            // mark is_palindrome
            int l = i - 2;
            int r = i;
            while (1) {
#ifndef NDEBUG
                printf("%d to %d is palindrome\n", l, r);
#endif
                is_palindrome[l--][r++] = 1;
                if (!(l >= 0 && r < N)) break;
                if (numbers[l] != numbers[r]) break;
            }
        }
    }
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int s, e;
        scanf("%d %d", &s, &e);
        printf("%d\n", is_palindrome[s - 1][e - 1]);
    }
}