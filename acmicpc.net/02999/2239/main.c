#include <stdio.h>

typedef struct map {
    int n[9][9];
    int row_mask[9], col_mask[9];
    int sec_mask[3][3];
} map;

int do_dfs(map m);

int main() {
    map init;
    for (int i = 0; i < 9; i++) {
        init.row_mask[i] = 0;
        init.col_mask[i] = 0;
        for (int j = 0; j < 9; j++) {
            scanf("%1d", &(init.n[i][j]));
            init.sec_mask[i / 3][j / 3] = 0;
        }
    }

    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            init.row_mask[r] |= (1 << init.n[r][c]);
            init.col_mask[c] |= (1 << init.n[r][c]);
            init.sec_mask[r / 3][c / 3] |= (1 << init.n[r][c]);
        }
    }
    do_dfs(init);
    return 0;
}

int do_dfs(map m) {
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (m.n[r][c] == 0) {
                for (int new_num = 1; new_num <= 9; new_num++) {
                    if (m.row_mask[r] & (1 << new_num)) continue;
                    if (m.col_mask[c] & (1 << new_num)) continue;
                    if (m.sec_mask[r / 3][c / 3] & (1 << new_num)) continue;

                    m.n[r][c] = new_num;
                    m.row_mask[r] |= (1 << new_num);
                    m.col_mask[c] |= (1 << new_num);
                    m.sec_mask[r / 3][c / 3] |= (1 << new_num);

                    int result = do_dfs(m);
                    if (result == 0) {
                        return 0;
                    } else {
                        m.n[r][c] = 0;
                        m.row_mask[r] &= ~(1 << new_num);
                        m.col_mask[c] &= ~(1 << new_num);
                        m.sec_mask[r / 3][c / 3] &= ~(1 << new_num);
                    }
                }
                return -1;
            }
        }
    }
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) printf("%d", m.n[r][c]);
        printf("\n");
    }
    return 0;
}