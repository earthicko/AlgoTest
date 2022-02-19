#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW 1500
#define MAX_COL 1500

int num_row, num_col;
char map[MAX_ROW][MAX_COL];

int main() {
    char buffer;
    scanf("%d %d", &num_row, &num_col);

    int i, j;
    for (i = 0; i < num_row; i++) {
        for (j = 0; j < num_col; j++) {
            scanf("%c", &buffer);
            if (buffer == '\n') {
                scanf("%c", &buffer);
            }
            map[i][j] = buffer;
        }
    }

    printf("\nGiven map:\n");
    for (i = 0; i < num_row; i++) {
        for (j = 0; j < num_col; j++) printf("%c ", map[i][j]);
        printf("\n");
    }
    printf("End of map\n");
}