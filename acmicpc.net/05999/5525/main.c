#include <stdio.h>
#define N_MAX 1000001
int N, M;
char IOI[N_MAX];
int main() {
    scanf("%d%d", &N, &M);
    scanf("%s", IOI);

    char expecting[2] = {'I', 'O'};
    int i = 0;
    int counter = 0;

    for (int m = 0; m < M; m++) {
        if (IOI[m] == expecting[0]) {
            int j;
            for (j = m; j < M; j++) {
                if (IOI[j] != expecting[i]) {
                    break;
                }
                i = i ^ 1;
            }
            // printf("%d to %d\n", m, j);
            if (j - m > 1) counter += (j - m + 1 - 2 * N) / 2;
            m = j - 1;
            i = 0;
        }
    }
    printf("%d\n", counter);
    return 0;
}