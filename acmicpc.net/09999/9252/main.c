#include <stdio.h>
#include <string.h>
#define L_MAX 1001
char a[L_MAX], b[L_MAX];    // 2KB
int l_lcs[L_MAX][L_MAX];    // 4MB
int prev[L_MAX][L_MAX][3];  // 8MB
int get_lcs_len(int l_a, int l_b);
int main() {
    scanf("%s", a);
    scanf("%s", b);

    int l_a = strlen(a);
    int l_b = strlen(b);
    for (int i = 1; i <= l_a; i++)
        for (int j = 1; j <= l_b; j++) l_lcs[i][j] = -1;
    printf("%d\n", get_lcs_len(l_a, l_b));

    char lcs[L_MAX];
    int n_chars = 0;
    int cursor_a = l_a, cursor_b = l_b;
    while (cursor_a > 0 && cursor_b > 0) {
        if (prev[cursor_a][cursor_b][2]) lcs[n_chars++] = a[cursor_a - 1];
        int new_cursor_a = prev[cursor_a][cursor_b][0];
        int new_cursor_b = prev[cursor_a][cursor_b][1];
        cursor_a = new_cursor_a;
        cursor_b = new_cursor_b;
    }
    for (int i = n_chars - 1; i >= 0; i--) printf("%c", lcs[i]);

    return 0;
}
int get_lcs_len(int l_a, int l_b) {
    if (l_lcs[l_a][l_b] != -1) return l_lcs[l_a][l_b];
    if (a[l_a - 1] == b[l_b - 1]) {
        l_lcs[l_a][l_b] = get_lcs_len(l_a - 1, l_b - 1) + 1;
        prev[l_a][l_b][0] = l_a - 1;
        prev[l_a][l_b][1] = l_b - 1;
        prev[l_a][l_b][2] = 1;
    } else {
        if (get_lcs_len(l_a - 1, l_b) > get_lcs_len(l_a, l_b - 1)) {
            l_lcs[l_a][l_b] = l_lcs[l_a - 1][l_b];
            prev[l_a][l_b][0] = l_a - 1;
            prev[l_a][l_b][1] = l_b;
        } else {
            l_lcs[l_a][l_b] = l_lcs[l_a][l_b - 1];
            prev[l_a][l_b][0] = l_a;
            prev[l_a][l_b][1] = l_b - 1;
        }
    }
    return l_lcs[l_a][l_b];
}