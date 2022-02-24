/*
F(i, cost): 인덱스 i까지 cost를 써서 확보할 수 있는 최대 메모리

F(i, cost) = i번째 앱을 닫았을 때 vs 열어놨을 때 확보하는 메모리 중 큰 것
            F(i - 1, cost - c[i]) + m[i] (0 <= cost - c[i]일 때 가능)
                i - 1: i - 1번째 앱까지
                cost - c[i] : 원래 c[i]만큼 비용을 덜 썼었는데
                이참에 c[i]를 써서 비용은 cost로 맞음 + m[i]만큼 메모리 추가확보
            F(i - 1, cost) : 안닫음


N: 앱 개수 M: 확보할 메모리 크기
1 <= N <= 100, 1 <= M <= 10,000,000
각 메모리 <= 10,000,000 ) 합 최대 = 10,000,000
각 코스트 <= 100 ) 합 최대 = 10,000
*/

#include <stdio.h>
#include <stdlib.h>

int* m;
short* c;
int** max_mem;
int N_APPS = 0, MEM = 0;
short SUM_COST = 0;

int main() {
    scanf("%d %d", &N_APPS, &MEM);
    m = (int*)malloc(sizeof(int) * N_APPS);
    c = (short*)malloc(sizeof(short) * N_APPS);
    for (int i = 0; i < N_APPS; i++) scanf("%d", m + i);
    for (int i = 0; i < N_APPS; i++) {
        scanf("%hd", c + i);
        SUM_COST += c[i];
    }

    max_mem = (int**)malloc(sizeof(int*) * N_APPS);
    for (int i = 0; i < N_APPS; i++) {
        max_mem[i] = (int*)malloc(sizeof(int) * (SUM_COST + 1));
    }
    for (short i = 0; i < N_APPS; i++) {
        for (short cost = 0; cost <= SUM_COST; cost++) {
            if (cost - c[i] >= 0) {
                int previous = m[i];
                if (i > 0) previous += max_mem[i - 1][cost - c[i]];
                if (max_mem[i][cost] < previous) {
                    max_mem[i][cost] = previous;
                }
            }
            int previous = 0;
            if (i > 0) previous = max_mem[i - 1][cost];
            if (max_mem[i][cost] < previous) {
                max_mem[i][cost] = previous;
            }
        }
    }
    for (short cost = 0; cost <= SUM_COST; cost++) {
        if (max_mem[N_APPS - 1][cost] >= MEM) {
            printf("%d\n", cost);
            break;
        }
    }
    return 0;
}
