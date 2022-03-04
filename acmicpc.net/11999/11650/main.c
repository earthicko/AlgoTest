#include <stdio.h>
#include <stdlib.h>

typedef struct coord {
    int x, y;
} coord;
int cmp(const void *a, const void *b);
int main() {
    int n;
    scanf("%d", &n);
    coord coords[100000];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &(coords[i].x), &(coords[i].y));
    }
    qsort(coords, n, sizeof(coord), cmp);
    for (int i = 0; i < n; i++) printf("%d %d\n", coords[i].x, coords[i].y);
    return 0;
}
int cmp(const void *a, const void *b) {
    if (((coord *)a)->x < ((coord *)b)->x) return -1;
    if (((coord *)a)->x > ((coord *)b)->x) return 1;
    if (((coord *)a)->y < ((coord *)b)->y) return -1;
    return 1;
}