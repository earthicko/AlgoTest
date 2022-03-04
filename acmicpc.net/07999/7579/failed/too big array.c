/*
코스트를 계산하는 함수 F(index, memory) i: index, mem: memory
메모리 할당량을 저장하는 배열 m[n]
재실행 시 비용을 저장하는 배열 c[n]
F(i, mem) = F(i - 1, mem)                     if mem <= 0
            min(F(i - 1, mem)
                F(i - 1, mem - m[i]) + c[i])  else
F(0, mem) = INF  if mem > m[0]
            c[0] else

결과는 cost[mem] 배열에 저장 (short * 10,000,000 = 20MB)
교대로 저장 -> 40MB 필요
i = n-1 ... 0까지 재귀함수로 어떤 mem에 대해 계산이 필요한지 map[i] 배열에
비트마스크로 저장
    이때 int (32비트)는 비트 개수가 모자라 312,501개 사용 -> 10,000,032비트
= 1.25MB (교대로 저장, 2.5MB)

    0 <= i < 32         -> 0번 원소
    32 <= i < 64         -> 1번 원소
    64 <= i < 96         -> 2번 원소
    96 <= i < 128        -> 3번 원소
    ...
    9,999,968 <= i < 10,000,000 -> 312,499번 원소
    10,000,000 <= i < 10,000,032 -> 312,500번 원소

    즉 i / 32 = 들어갈 원소 번호, i % 32는 시프트할 양

N: 앱 개수 M: 확보할 메모리 크기
1 <= N <= 100, 1 <= M <= 10,000,000
각 메모리 <= 10,000,000 ) 합 최대 = 10,000,000
각 코스트 <= 100 ) 합 최대 = 10,000
*/
#include <limits.h>
#include <stdio.h>
#define MAX_APPS 100
#define MAX_MEM 10000001
#define MAP_SIZE 312501

int m[MAX_APPS];
int c[MAX_APPS];
int map[2][MAP_SIZE];
short cost[2][MAX_MEM];
int shift = sizeof(int) * 8;
int alt = 0;
int N_APPS, MEM;

int build_map(int level);

int main() {
    scanf("%d %d", &N_APPS, &MEM);
    for (int i = 0; i < N_APPS; i++) scanf("%d", m + i);
    for (int i = 0; i < N_APPS; i++) scanf("%d", c + i);

    map[alt][MEM / shift] |= (1 << (MEM % shift));
    build_map(N_APPS - 1);

    return 0;
}

int build_map(int level) {
    // map[level]의 val번째 비트를 켠다
    printf("At level %d\n", level);
    printf("Using alt %d\n", alt);

    if (level == 0) {
        for (int val = 0; val <= MEM; val++) {
            if (map[alt][val / shift] & (1 << (val % shift))) {
                printf("F(%d, %d) = ?\n", level, val);
                if (val == 0) {
                    cost[alt][val] = 0;
                } else if (val > m[level]) {
                    cost[alt][val] = SHRT_MAX;
                } else {
                    cost[alt][val] = c[level];
                }
            }
        }
        return 0;
    }
    for (int val = 0; val <= MEM; val++) {
        if (map[alt][val / shift] & (1 << (val % shift))) {
            printf("F(%d, %d) = ?\n", level, val);
            int next_val = val - m[level];
            if (next_val < 0) next_val = 0;
            map[alt ^ 1][val / shift] |= (1 << (val % shift));
            map[alt ^ 1][next_val / shift] |= (1 << (next_val % shift));
        }
    }
    alt ^= 1;
    build_map(level - 1);
    alt ^= 1;
    for (int val = 0; val <= MEM; val++) {
        if (map[alt][val / shift] & (1 << (val % shift))) {
            // F(level, val) = ?
            // 1. F(level - 1, val - m[level]) + c[level]
            int next_val = val - m[level];
            if (next_val < 0) next_val = 0;
            short subtract = cost[alt ^ 1][next_val] + c[level];
            // 2. F(level - 1, val)
            short pass = cost[alt ^ 1][val];
            cost[alt][val] = (subtract < pass) ? subtract : pass;
        }
    }
    return 0;
}