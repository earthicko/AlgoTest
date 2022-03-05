#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MAX 500000
#define STRLEN_MAX 21

int N, M;
char deuddo[N_MAX][STRLEN_MAX];
char deuddobodo[N_MAX][STRLEN_MAX];

int cmp(const void *a, const void *b);

int main() {
    scanf("%d %d", &N, &M);
    for (int n = 0; n < N; n++) scanf("%s", deuddo[n]);

    qsort(deuddo, N, sizeof(deuddo[0]), cmp);

    int deudbo_n = 0;
    for (int m = 0; m < M; m++) {
        char bodo[STRLEN_MAX];
        scanf("%s", bodo);
        void *idx = bsearch(bodo, deuddo, N, sizeof(deuddo[0]), cmp);
        if (idx != NULL) {
            strcpy(deuddobodo[deudbo_n], bodo);
            deudbo_n++;
        }
    }
    qsort(deuddobodo, deudbo_n, sizeof(deuddobodo[0]), cmp);

    printf("%d\n", deudbo_n);
    for (int i = 0; i < deudbo_n; i++) printf("%s\n", deuddobodo[i]);
    return 0;
}

int cmp(const void *a, const void *b) { return (strcmp((char *)a, (char *)b)); }