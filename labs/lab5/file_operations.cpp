#include <cstdlib>
#include "file_operations.h"
#include <stdio.h>

// Объявление структуры FILE для использования в cpp-файле
struct _iobuf;
typedef struct _iobuf FILE;

int readMatrixSize(FILE* file, int* rows, int* cols) {
    if (fscanf(file, "%d %d", rows, cols) != 2) {
        return 0;
    }
    return 1;
}

// Остальные функции должны быть реализованы аналогично

double** readMatrix(FILE* file, int rows, int cols) {
    double** matrix = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (double*)malloc(cols * sizeof(double));
        for (int j = 0; j < cols; j++) {
            fscanf(file, "%lf", &matrix[i][j]);
        }
    }
    return matrix;
}

void writeResults(FILE* file, double* X, int size, double** matrix, int rows, int cols) {
    fprintf(file, "Исходная матрица:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%8.2f ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }
    
    fprintf(file, "\nРезультат (вектор X):\n");
    for (int i = 0; i < size; i++) {
        fprintf(file, "X%d = %.2f\n", i + 1, X[i]);
    }
}

void freeMatrix(double** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}