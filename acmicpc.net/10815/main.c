#include <stdio.h>

int HAS_CARD[20000001];
// -10,000,000 -> 0, 0 -> 10,000,000, 10,000,000 -> 20,000,000
int N, M;
int card_idx;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &card_idx);
        HAS_CARD[card_idx + 10000000] = 1;
    }
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        scanf("%d", &card_idx);
        printf("%d ", HAS_CARD[card_idx + 10000000]);
    }
    return 0;
}