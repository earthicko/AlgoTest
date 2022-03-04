#include <stdio.h>

typedef struct thicc {
    int w, h;
} thicc;

int bigger(thicc a, thicc b);

int main() {
    int n;
    scanf("%d", &n);
    thicc people[50];
    for (int i = 0; i < n; i++) scanf("%d %d", &(people[i].w), &(people[i].h));
    for (int i = 0; i < n; i++) {
        int order = 1;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (bigger(people[j], people[i]) == 1) order++;
        }
        printf("%d ", order);
    }
    return 0;
}

int bigger(thicc a, thicc b) {
    if (a.w > b.w && a.h > b.h) return 1;
    if (a.w < b.w && a.h < b.h) return -1;
    return 0;
}