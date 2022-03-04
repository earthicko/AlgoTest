#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

typedef unsigned long long int ull;
typedef struct matrix {
    int** data;
    int num_rows;
    int num_cols;
} matrix;

matrix* construct_matrix(int num_rows, int num_cols);
int free_matrix(matrix* target);
matrix* copy_matrix(matrix* base);
matrix* multiply_matrix(matrix* a, matrix* b);
matrix* power_matrix(matrix* base, int power);
int print_matrix(matrix* target);

matrix* construct_matrix(int num_rows, int num_cols) {
    // matrix[row][col]
    matrix* output = (matrix*)malloc(sizeof(matrix));
    output->num_rows = num_rows;
    output->num_cols = num_cols;
    output->data = (int**)malloc(sizeof(int*) * num_rows);
    for (int row_idx = 0; row_idx < num_rows; row_idx++) {
        int* row = (int*)malloc(sizeof(int) * num_cols);
        memset(row, 0, sizeof(int) * num_cols);
        output->data[row_idx] = row;
    }

    if (DEBUG) {
        printf("constructed matrix:\n");
        print_matrix(output);
    }
    return output;
}
int free_matrix(matrix* target) {
    for (int i = 0; i < target->num_rows; i++) free(target->data[i]);
    free(target->data);
    free(target);
    return 0;
}
matrix* copy_matrix(matrix* base) {
    matrix* copy = construct_matrix(base->num_rows, base->num_cols);

    for (int i = 0; i < base->num_rows; i++) {
        for (int j = 0; j < base->num_cols; j++)
            copy->data[i][j] = base->data[i][j];
    }
    return copy;
}
matrix* multiply_matrix(matrix* a, matrix* b) {
    if (a->num_cols != b->num_rows) return;
    matrix* output = construct_matrix(a->num_rows, b->num_cols);

    int add_n = a->num_cols;
    for (int row_i = 0; row_i < a->num_rows; row_i++) {
        for (int col_i = 0; col_i < b->num_cols; col_i++) {
            // determines output[i][j]
            // output[i][j] = a[i][0]*b[0][j] + a[i][1]*b[1][j]
            // + a[i][2]*b[2][j] ... + a[i][n]*b[n][j]
            int product = 0;
            for (int add_i = 0; add_i < add_n; add_i++) {
                product += a->data[row_i][add_i] * b->data[add_i][col_i];
            }
            output->data[row_i][col_i] = product;
        }
    }
    return output;
}
matrix* power_matrix(matrix* base, int power) {
    if (base->num_cols != base->num_rows) return;
    matrix* result = construct_matrix(base->num_rows, base->num_rows);

    for (int i = 0; i < result->num_rows; i++) result->data[i][i] = 1;
    while (power > 0) {
        if (power % 2 == 1) {
            matrix* temp = copy_matrix(result);
            result = multiply_matrix(temp, base);
            free_matrix(temp);
        }
        power /= 2;
        matrix* temp = copy_matrix(base);
        base = multiply_matrix(temp, temp);
        free_matrix(temp);
    }
    return result;
}
int print_matrix(matrix* target) {
    printf("Matrix %d x %d\n", target->num_cols, target->num_rows);
    for (int i = 0; i < target->num_rows; i++) {
        printf("| ");
        for (int j = 0; j < target->num_cols; j++)
            printf("%d ", target->data[i][j]);
        printf("|\n");
    }
    return 0;
}