#include <assert.h>
#include <stdio.h>

#define SIZE_MAX 25

typedef struct Coord {
    int r, c;
} Coord;

int R, C;
char MAP[SIZE_MAX][SIZE_MAX];
int PASSINGS[SIZE_MAX][SIZE_MAX];
int PASSINGS_BAK[SIZE_MAX][SIZE_MAX];
Coord M, Z;
char PIPES[7] = {'|', '-', '+', '1', '2', '3', '4'};
Coord END, V_END;
int CONNECTED;

int is_passable(Coord v, char pipe);
int get_connectivity(Coord start, Coord v_start);

int main() {
    scanf("%d %d", &R, &C);
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            scanf(" %c", &(MAP[r][c]));
            if (MAP[r][c] == 'M') {
                M.r = r;
                M.c = c;
            } else if (MAP[r][c] == 'Z') {
                Z.r = r;
                Z.c = c;
            } else if (MAP[r][c] != '.') {
                if (MAP[r][c] == '+') {
                    PASSINGS[r][c] = 2;
                } else {
                    PASSINGS[r][c] = 1;
                }
            }
        }
    }
    Coord dir[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    // +r: down, -r: up, +c: right, -c: left
    Coord initial_vector = {0, 0};
    for (int i = 0; i < 4; i++) {
        Coord there = {M.r + dir[i].r, M.c + dir[i].c};
        if (there.r < 0 || there.r >= R || there.c < 0 || there.c >= C)
            continue;
        if (MAP[there.r][there.c] != '.') {
            if (is_passable(dir[i], MAP[there.r][there.c])) {
                initial_vector.r = dir[i].r;
                initial_vector.c = dir[i].c;
            }
        }
    }

    get_connectivity(M, initial_vector);
    Coord empty = {END.r, END.c};
    Coord v_empty = {V_END.r, V_END.c};
    // up(-1, 0) down(1, 0) right(0, 1) left(0, -1)

    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) PASSINGS_BAK[r][c] = PASSINGS[r][c];
    }

    char new_blocks[4];
    if (v_empty.r == -1 && v_empty.c == 0) {  // up
        // | + 1 4
        new_blocks[0] = '|';
        new_blocks[1] = '+';
        new_blocks[2] = '1';
        new_blocks[3] = '4';
    } else if (v_empty.r == 1 && v_empty.c == 0) {  // down
        // | + 2 3
        new_blocks[0] = '|';
        new_blocks[1] = '+';
        new_blocks[2] = '2';
        new_blocks[3] = '3';
    } else if (v_empty.r == 0 && v_empty.c == 1) {  // right
        // - + 3 4
        new_blocks[0] = '-';
        new_blocks[1] = '+';
        new_blocks[2] = '3';
        new_blocks[3] = '4';
    } else if (v_empty.r == 0 && v_empty.c == -1) {  // left
        // - + 1 2
        new_blocks[0] = '-';
        new_blocks[1] = '+';
        new_blocks[2] = '1';
        new_blocks[3] = '2';
    }
    char new_block;
    for (int idx = 0; idx < 4; idx++) {
        Coord v_altered = {v_empty.r, v_empty.c};
        new_block = new_blocks[idx];
        MAP[empty.r][empty.c] = new_block;
        // if (new_block == '|') {
        // } else if (new_block == '-') {
        // } else
        if (new_block == '+') {
            PASSINGS[empty.r][empty.c]++;
        } else if (new_block == '1') {  // up left
            if (v_empty.r == -1 && v_empty.c == 0) {
                // up to right
                v_altered.r = 0;
                v_altered.c = 1;
            } else if (v_empty.r == 0 && v_empty.c == -1) {
                // left to down
                v_altered.r = 1;
                v_altered.c = 0;
            }
        } else if (new_block == '2') {  // down left
            if (v_empty.r == 1 && v_empty.c == 0) {
                // down to right
                v_altered.r = 0;
                v_altered.c = 1;
            } else if (v_empty.r == 0 && v_empty.c == -1) {
                // left to up
                v_altered.r = -1;
                v_altered.c = 0;
            }
        } else if (new_block == '3') {  // down right
            if (v_empty.r == 1 && v_empty.c == 0) {
                // down to left
                v_altered.r = 0;
                v_altered.c = -1;
            } else if (v_empty.r == 0 && v_empty.c == 1) {
                // right to up
                v_altered.r = -1;
                v_altered.c = 0;
            }
        } else if (new_block == '4') {  // up right
            if (v_empty.r == -1 && v_empty.c == 0) {
                // up to left
                v_altered.r = 0;
                v_altered.c = -1;
            } else if (v_empty.r == 0 && v_empty.c == 1) {
                // right to down
                v_altered.r = 1;
                v_altered.c = 0;
            }
        }
        if (get_connectivity(empty, v_altered)) {
            // check PASSINGS
            // if good break
            int all_pass = 1;
            for (int r = 0; r < R; r++) {
                for (int c = 0; c < C; c++) {
                    if (PASSINGS[r][c] != 0) {
                        all_pass = 0;
                        break;
                    }
                }
            }
            if (all_pass) {
                printf("%d %d %c\n", empty.r + 1, empty.c + 1, new_block);
                return 0;
            }
        }
        MAP[empty.r][empty.c] = '.';
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) PASSINGS[r][c] = PASSINGS_BAK[r][c];
        }
    }

    return -1;
}

int is_passable(Coord v, char pipe) {
    switch (pipe) {  // +r: down, -r: up, +c: right, -c: left
        case '|':
            if ((v.r == -1 || v.r == 1) && v.c == 0)
                return 1;
            else
                return 0;
        case '-':
            if ((v.c == -1 || v.c == 1) && v.r == 0)
                return 1;
            else
                return 0;
        case '1':  // ┌
            if ((v.r == 0 && v.c == -1) || (v.r == -1 && v.c == 0))
                return 1;
            else
                return 0;
        case '2':  // └
            if ((v.r == 0 && v.c == -1) || (v.r == 1 && v.c == 0))
                return 1;
            else
                return 0;
        case '3':  // ┘
            if ((v.r == 0 && v.c == 1) || (v.r == 1 && v.c == 0))
                return 1;
            else
                return 0;
        case '4':  // ┐
            if ((v.r == 0 && v.c == 1) || (v.r == -1 && v.c == 0))
                return 1;
            else
                return 0;
    }
}

int get_connectivity(Coord start, Coord v_start) {
    CONNECTED = 0;
    Coord here = {start.r, start.c};
    Coord vector = {v_start.r, v_start.c};

    while (1) {
        Coord next = {here.r + vector.r, here.c + vector.c};
        if (next.r < 0 || next.r >= R || next.c < 0 || next.c >= C) {
            return 0;
        }
        if (next.r == Z.r && next.c == Z.c) {  // found Zaglev
            return 1;
        }
        char pipe = MAP[next.r][next.c];

        int passible = 1;

        switch (pipe) {
            case '.':
                // pipe disconnected
                passible = 0;
            case '|':
                if (!is_passable(vector, pipe)) {
                    passible = 0;
                    break;
                }
                break;
            case '-':
                if (!is_passable(vector, pipe)) {
                    passible = 0;
                    break;
                }
                break;
            case '+':
                break;
            case '1':  // ┌
                if (!is_passable(vector, pipe)) {
                    passible = 0;
                    break;
                }
                if (vector.r == 0 && vector.c == -1) {  // left to down
                    vector.r = 1;
                    vector.c = 0;
                } else if (vector.r == -1 && vector.c == 0) {  // up to right
                    vector.r = 0;
                    vector.c = 1;
                }
                break;
            case '2':  // └
                if (!is_passable(vector, pipe)) {
                    passible = 0;
                    break;
                }
                if (vector.r == 0 && vector.c == -1) {  // left to up
                    vector.r = -1;
                    vector.c = 0;
                } else if (vector.r == 1 && vector.c == 0) {  // down to right
                    vector.r = 0;
                    vector.c = 1;
                }
                break;
            case '3':  // ┘
                if (!is_passable(vector, pipe)) {
                    passible = 0;
                    break;
                }
                if (vector.r == 0 && vector.c == 1) {  // right to up
                    vector.r = -1;
                    vector.c = 0;
                } else if (vector.r == 1 && vector.c == 0) {  // down to left
                    vector.r = 0;
                    vector.c = -1;
                }
                break;
            case '4':  // ┐ up(-1, 0) down(1, 0) right(0, 1) left(0, -1)
                if (!is_passable(vector, pipe)) {
                    passible = 0;
                    break;
                }
                if (vector.r == 0 && vector.c == 1) {  // right to down
                    vector.r = 1;
                    vector.c = 0;
                } else if (vector.r == -1 && vector.c == 0) {  // up to left
                    vector.r = 0;
                    vector.c = -1;
                }
                break;

            default:
                break;
        }
        if (!passible) {
            END.r = next.r;
            END.c = next.c;
            V_END.r = vector.r;
            V_END.c = vector.c;
            return 0;
        } else {
            PASSINGS[next.r][next.c]--;
            here.r = next.r;
            here.c = next.c;
        }
    }
    return 0;
}