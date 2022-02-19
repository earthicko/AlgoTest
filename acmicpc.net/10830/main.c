/*
문제
크기가 N*N인 행렬 A가 주어진다. 이때, A의 B제곱을 구하는 프로그램을 작성하시오.
수가 매우 커질 수 있으니, A^B의 각 원소를 1,000으로 나눈 나머지를 출력한다.

입력
첫째 줄에 행렬의 크기 N과 B가 주어진다. (2 ≤ N ≤  5, 1 ≤ B ≤ 100,000,000,000)

둘째 줄부터 N개의 줄에 행렬의 각 원소가 주어진다. 행렬의 각 원소는 1,000보다
작거나 같은 자연수 또는 0이다.

출력
첫째 줄부터 N개의 줄에 걸쳐 행렬 A를 B제곱한 결과를 출력한다.
================================================================================
B <= 100,000,000,000 < 137,438,953,472 = 2^37 b < 5B
최악의 경우 37번 계산

할 일
1. 행렬 자료형 구현
2. 행렬 제곱 구현 (mod 하면서)
3. 행렬 거듭제곱 분할정복으로 구현

자료형
원소: 0 <= < 1000 int
B: long long
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define P 1000
#define DEBUG 0

int n;
long long b;

int** construct_matrix();
int free_matrix(int** matrix);
int** copy_matrix(int** matrix);
int** multiply_matrix(int** a, int** b);
int** power_matrix(int** base, long long power);
int print_matrix(int** matrix);

int main() {
    scanf("%d %lld", &n, &b);

    int** matrix = construct_matrix();
    // matrix[row][col]

    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) scanf("%d", matrix[i] + j);
    }

    if (DEBUG) {
        printf("Given matrix:\n");
        print_matrix(matrix);
    }

    int** result = power_matrix(matrix, b);

    print_matrix(result);

    return 0;
}

int** construct_matrix() {
    int** matrix = (int**)malloc(sizeof(int*) * n);
    int i, j;
    for (i = 0; i < n; i++) {
        int* row = (int*)malloc(sizeof(int) * n);
        memset(row, 0, sizeof(int) * n);
        matrix[i] = row;
    }

    if (DEBUG) {
        printf("constructed matrix:\n");
        print_matrix(matrix);
    }
    return matrix;
}

int free_matrix(int** matrix) {
    int i;
    for (int i = 0; i < n; i++) free(matrix[i]);
    free(matrix);
    return 0;
}

int** copy_matrix(int** matrix) {
    int** output = (int**)malloc(sizeof(int*) * n);
    int i, j;
    for (i = 0; i < n; i++) {
        int* row = (int*)malloc(sizeof(int) * n);
        output[i] = row;
        for (j = 0; j < n; j++) output[i][j] = matrix[i][j];
    }
    return output;
}

int** multiply_matrix(int** a, int** b) {
    int** output = construct_matrix();
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            // determines output[i][j]
            // output[i][j] = a[i][0]*b[0][j] + a[i][1]*b[1][j]
            // + a[i][2]*b[2][j] ... + a[i][n]*b[n][j]
            int k;
            int product = 0;
            for (k = 0; k < n; k++) {
                product += a[i][k] * b[k][j];
            }
            output[i][j] = product % P;
        }
    }
    return output;
}

int** power_matrix(int** base, long long power) {
    int** result = construct_matrix();
    int i;
    for (i = 0; i < n; i++) result[i][i] = 1;
    while (power > 0) {
        if (power % 2 == 1) {
            int** temp = result;
            result = multiply_matrix(temp, base);
            free_matrix(temp);
        }
        power /= 2;
        int** temp = base;
        base = multiply_matrix(temp, temp);
        free_matrix(temp);
    }
    return result;
}

int print_matrix(int** matrix) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) printf("%hi ", matrix[i][j]);
        printf("\n");
    }
    return 0;
}